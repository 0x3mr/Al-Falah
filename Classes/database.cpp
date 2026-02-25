#include "headers/database.h"
#include <iostream>
Database::Database() : db(nullptr) {}

Database::~Database() {
    close();
}

bool Database::connect(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: "
                  << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::cout << "Connected to database successfully.\n";

  
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

    return true;
}

void Database::initialize() {

    const char* sql = R"(

        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE,
            password_hash TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
            );

        CREATE TABLE IF NOT EXISTS prayer_records (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            prayer_name TEXT NOT NULL,
            prayer_date DATE NOT NULL,
            completed BOOLEAN DEFAULT 0,
            completed_at DATETIME,
            FOREIGN KEY (user_id) REFERENCES users(id)
        );

        CREATE TABLE IF NOT EXISTS user_settings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            adhan_enabled BOOLEAN DEFAULT 1,
            adhan_sound TEXT DEFAULT 'default.mp3',
            FOREIGN KEY (user_id) REFERENCES users(id)
        );

        CREATE TABLE IF NOT EXISTS prayer_times (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            prayer_name TEXT NOT NULL,
            adhan_time TIME NOT NULL
        );



    )";

    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Database tables initialized successfully.\n";
    }
}

void Database::close() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
        std::cout << "Database connection closed.\n";
    }
}

sqlite3* Database::getDB() {
    return db;
}