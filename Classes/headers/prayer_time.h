#ifndef PRAYER_TIME_H
#define PRAYER_TIME_H

#include <string>
#include <map>
#include "database.h"

class PrayerTime {
private:
    std::map<std::string, std::string> prayers;
    Database& db;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);

    std::string fetchFromAPI(double lat, double lon);
    void parseAndStore(const std::string& response);

public:
    PrayerTime(Database& database);

    void calculatePrayerTimes(double lat, double lon);
    std::string getPrayerTime(const std::string& name);
    void saveToDB(int user_id);
    void display();
    std::pair<std::string, int> getNextPrayer();
    void showCountdown();
};

#endif