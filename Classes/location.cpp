#include "headers/location.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Location::Location(double latitude, double longitude, const string& city, const string& country)
    : latitude(latitude), longitude(longitude), city(city), country(country) {}

Location::Location() : latitude(0.0), longitude(0.0), city(""), country("") {}


Location Location::getCurrentLocation() const {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://ip-api.com/json/");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res == CURLE_OK) {
            auto data = json::parse(readBuffer);

            double lat = data["lat"];
            double lon = data["lon"];
            string city = data["city"];
            string country = data["country"];

            return Location(lat, lon, city, country);
        }
    }

    // fallback
    return Location(0, 0, "Unknown", "Unknown");
}



Location Location::manuallySetLocation() {
    double lat, lon;
    string cityName, countryName;

    cout << "Enter latitude: ";
    cin >> lat;
    cout << "Enter longitude: ";
    cin >> lon;
    cout << "Enter city name: ";
    cin >> cityName;
    cout << "Enter country name: ";
    cin >> countryName;

    return Location(lat, lon, cityName, countryName);
   

}

double Location::getLatitude() const {
    return latitude;
}

double Location::getLongitude() const {
    return longitude;
}

void Location::displayLocation() const {
    cout << "Current Location: " << city << ", " << country 
         << " (Latitude: " << latitude << ", Longitude: " << longitude << ")" << endl;
}

string Location::getLocation() const {
  
    
    return city + ", " + country + " (" +
           to_string(latitude) + "," +
           to_string(longitude) + ")";
}
void Location::saveLocation(Database& db, const string& location, int user_id) {
    sqlite3* conn = db.getDB();

    const char* sql = "UPDATE users SET last_location = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    // Prepare statement
    if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "[ERROR] Failed to prepare statement\n";
        return;
    }

    // Bind values
    sqlite3_bind_text(stmt, 1, location.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, user_id);

    // Execute
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "[ERROR] Failed to save location\n";
    } else {
        std::cout << "[INFO] Location saved successfully!\n";
    }

    // Cleanup
    sqlite3_finalize(stmt);
}


