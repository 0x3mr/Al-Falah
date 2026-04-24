#ifndef PRAYER_RECORD_H
#define PRAYER_RECORD_H

#include <string>
#include "database.h"

using namespace std;

class PrayerRecord {
private:
    int id;
    int user_id;
    string prayer_name;
    string prayer_date;
    bool completed;
    string completed_at;

public:
    PrayerRecord(int user_id, const string& prayer_name, const string& prayer_date);

    // Actions
    bool save(Database& db);              // insert
    bool markCompleted(Database& db);     // update

    // Static helpers
    static void getUserRecords(Database& db, int user_id);
};

#endif