#include "headers/prayer_time.h"
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

PrayerTime::PrayerTime(Database& database) : db(database) {}

size_t PrayerTime::WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string PrayerTime::fetchFromAPI(double lat, double lon) {
    string response;

    string url = "https://api.aladhan.com/v1/timings?latitude=" 
               + to_string(lat) + "&longitude=" 
               + to_string(lon) + "&method=5";

    CURL* curl = curl_easy_init();

    if (!curl) {
        cerr << "[ERROR] Curl init failed\n";
        return "";
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    CURLcode res = curl_easy_perform(curl);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (res != CURLE_OK || http_code != 200) {
        cerr << "[ERROR] Curl failed: " << curl_easy_strerror(res)
             << " | HTTP: " << http_code << endl;
        response.clear();
    }

    curl_easy_cleanup(curl);

    return response;
}

void PrayerTime::parseAndStore(const string& response) {
    try {
        auto j = json::parse(response);

        // 🔥 Check API success
        if (!j.contains("code") || j["code"] != 200) {
            cerr << "[ERROR] API returned error\n";
            return;
        }

        auto timings = j["data"]["timings"];

        prayers["Fajr"]    = timings.value("Fajr", "");
        prayers["Dhuhr"]   = timings.value("Dhuhr", "");
        prayers["Asr"]     = timings.value("Asr", "");
        prayers["Maghrib"] = timings.value("Maghrib", "");
        prayers["Isha"]    = timings.value("Isha", "");

    } catch (exception& e) {
        cerr << "[ERROR] JSON parse failed: " << e.what() << endl;
    }
}

void PrayerTime::calculatePrayerTimes(double lat, double lon) {
    prayers.clear();  // 🔥 VERY IMPORTANT

    string response = fetchFromAPI(lat, lon);

    if (response.empty()) {
        cout << "[ERROR] Failed to fetch prayer times\n";
        return;
    }

    parseAndStore(response);

    // 🔍 Validate result
    if (prayers["Fajr"].empty()) {
        cout << "[ERROR] Invalid prayer data received\n";
        prayers.clear();  // prevent using bad data
    }
}

string PrayerTime::getPrayerTime(const string& name) {
    return prayers[name];
}

void PrayerTime::saveToDB(int user_id) {
    string sql = "INSERT OR REPLACE INTO prayer_times "
                 "(user_id, prayer_name, adhan_time, date) "
                 "VALUES (?, ?, ?, DATE('now'));";

    for (auto& p : prayers) {
        sqlite3_stmt* stmt;

        sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_int(stmt, 1, user_id);
        sqlite3_bind_text(stmt, 2, p.first.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, p.second.c_str(), -1, SQLITE_STATIC);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void PrayerTime::display() {
    if (prayers.empty()) {
        cout << "[ERROR] No prayer times to display\n";
        return;
    }

    for (auto& p : prayers) {
        cout << p.first << ": " << (p.second.empty() ? "N/A" : p.second) << endl;
    }
}

int timeToMinutes(const string& timeStr) {
    if (timeStr.empty() || timeStr.size() < 5) {
        return -1;
    }

    try {
        int hours = stoi(timeStr.substr(0, 2));
        int minutes = stoi(timeStr.substr(3, 2));
        return hours * 60 + minutes;
    } catch (...) {
        return -1;
    }
}
int getCurrentMinutes() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    return ltm->tm_hour * 60 + ltm->tm_min;
}
pair<string, int> PrayerTime::getNextPrayer() {
    int now = getCurrentMinutes();

    vector<pair<string, int>> prayerList = {
        {"Fajr", timeToMinutes(prayers["Fajr"])},
        {"Dhuhr", timeToMinutes(prayers["Dhuhr"])},
        {"Asr", timeToMinutes(prayers["Asr"])},
        {"Maghrib", timeToMinutes(prayers["Maghrib"])},
        {"Isha", timeToMinutes(prayers["Isha"])}
    };

    for (auto& p : prayerList) {
        if (p.second != -1 && p.second > now) {
            return {p.first, p.second - now};
        }
    }

    // next day Fajr
    int fajrTime = prayerList[0].second;
    if (fajrTime == -1) return {"", -1};

    return {"Fajr", (24 * 60 - now) + fajrTime};
}
#include <thread>
#include <chrono>

void PrayerTime::showCountdown() {
    while (true) {
        auto result = getNextPrayer();

        if (result.second <= 0) {
            break;
        }

        int totalSec = result.second * 60; // minutes → seconds

        while (totalSec > 0) {
            int h = totalSec / 3600;
            int m = (totalSec % 3600) / 60;
            int s = totalSec % 60;

            cout << "\rNext: " << result.first
                 << " in " << h << "h "
                 << m << "m "
                 << s << "s   " << flush;

            this_thread::sleep_for(chrono::seconds(1));
            totalSec--;
        }

        break;
    }

    cout << endl;
}