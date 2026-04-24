#include "headers/prayer_records.h"
#include <iostream>
#include <sqlite3.h>

PrayerRecord::PrayerRecord(int user_id, const string& prayer_name, const string& prayer_date)
    : user_id(user_id), prayer_name(prayer_name), prayer_date(prayer_date),
      completed(false), completed_at("") {}

bool PrayerRecord::save(Database& db) {
    const char* sql = R"(
        INSERT INTO prayer_records (user_id, prayer_name, prayer_date)
        VALUES (?, ?, ?);
    )";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed\n";
        return false;
    }

    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, prayer_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, prayer_date.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Insert failed (maybe duplicate)\n";
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool PrayerRecord::markCompleted(Database& db) {
    const char* sql = R"(
        UPDATE prayer_records
        SET completed = 1,
            completed_at = datetime('now')
        WHERE user_id = ? AND prayer_name = ? AND prayer_date = ?;
    )";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed\n";
        return false;
    }

    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, prayer_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, prayer_date.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Update failed\n";
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

void PrayerRecord::getUserRecords(Database& db, int user_id) {
    const char* sql = R"(
        SELECT prayer_name, prayer_date, completed
        FROM prayer_records
        WHERE user_id = ?;
    )";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed\n";
        return;
    }

    sqlite3_bind_int(stmt, 1, user_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string prayer = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string date   = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int completed = sqlite3_column_int(stmt, 2);

        cout << prayer << " | " << date << " | "
             << (completed ? "Done" : "Missed") << endl;
    }

    sqlite3_finalize(stmt);
}

