#include "Classes/headers/database.h"
#include "Classes/headers/login.h"
#include "Classes/headers/location.h"
#include "Classes/headers/prayer_time.h"
#include "Classes/headers/prayer_records.h"

#include <iostream>

using namespace std;
#include <chrono>
#include <thread>
#include <sqlite3.h>
#include <iostream>

void debugDatabase(Database& db) {
    sqlite3* conn = db.getDB();

    const char* sql = "SELECT id, username, created_at FROM users;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch users\n";
        return;
    }

    std::cout << "\n===== USERS TABLE =====\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* username = sqlite3_column_text(stmt, 1);
        const unsigned char* created_at = sqlite3_column_text(stmt, 2);

        std::cout << "ID: " << id
                  << " | Username: " << username
                  << " | Created: " << created_at << std::endl;
    }

    sqlite3_finalize(stmt);
}

void debugPrayerRecords(Database& db) {
    sqlite3* conn = db.getDB();

    const char* sql = "SELECT user_id, prayer_name, prayer_date, completed FROM prayer_records;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch prayer records\n";
        return;
    }

    std::cout << "\n===== PRAYER RECORDS =====\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int user_id = sqlite3_column_int(stmt, 0);
        const unsigned char* prayer = sqlite3_column_text(stmt, 1);
        const unsigned char* date = sqlite3_column_text(stmt, 2);
        int completed = sqlite3_column_int(stmt, 3);

        std::cout << "User: " << user_id
                  << " | Prayer: " << prayer
                  << " | Date: " << date
                  << " | Completed: " << completed << std::endl;
    }

    sqlite3_finalize(stmt);
}
void debugSingleUser(Database& db, int user_id) {
    sqlite3* conn = db.getDB();

    const char* sql = "SELECT username FROM users WHERE id = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, user_id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* username = sqlite3_column_text(stmt, 0);
        std::cout << "\nUser Found: " << username << std::endl;
    } else {
        std::cout << "\nUser NOT found\n";
    }

    sqlite3_finalize(stmt);
}


void getAllUsers(Database& db) {
    sqlite3* conn = db.getDB();

    const char* sql = "SELECT id, username, created_at, last_location FROM users;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query\n";
        return;
    }

    std::cout << "\n===== ALL USERS =====\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* username = sqlite3_column_text(stmt, 1);
        const unsigned char* created_at = sqlite3_column_text(stmt, 2);
        const unsigned char* location = sqlite3_column_text(stmt, 3);

        std::cout << "ID: " << id
                  << " | Username: " << username
                  << " | Created: " << created_at
                  << " | Location: " << (location ? (const char*)location : "NULL")
                  << std::endl;
    }

    sqlite3_finalize(stmt);
}


void runPrayerSystem(Database& db, int user_id) {

    Location loc;
    int choice;

    cout << "\nChoose Location Method:\n";
    cout << "1. Automatic\n";
    cout << "2. Manual\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
        loc = loc.getCurrentLocation();
    } else {
        loc = loc.manuallySetLocation();
    }

    cout << "\nLocation set:\n";
    loc.displayLocation();

    double lat = loc.getLatitude();
    double lon = loc.getLongitude();
    string locationStr = loc.getLocation();
    loc.saveLocation(db, locationStr, user_id);
    

    
    
    PrayerTime pt(db);
    pt.calculatePrayerTimes(lat, lon);

    cout << "\nToday's Prayer Times:\n";
    pt.display();

    char adhanChoice;
    cout << "\nDo you want Adhan? (y/n): ";
    cin >> adhanChoice;

    bool enableAdhan = (adhanChoice == 'y' || adhanChoice == 'Y');

   
    while (true) {

    cout << "\n===== Prayer System Menu =====\n";
    cout << "1. Show Next Prayer\n";
    cout << "2. Wait for Next Prayer (Countdown)\n";
    cout << "3. Back to Main Menu\n";
    cout << "Choice: ";

    int option;
    cin >> option;

    if (option == 3) {
        cout << "Returning to main menu...\n";
        break; // 🔥 EXIT LOOP → goes back to main()
    }

    auto next = pt.getNextPrayer();

    if (next.second == -1) {
        cout << "[ERROR] Cannot get next prayer\n";
        break;
    }

    cout << "\nNext Prayer: " << next.first << endl;

    if (option == 2) {
        pt.showCountdown();
        cout << "\n===== " << next.first << " TIME =====\n";

        if (enableAdhan) {
            cout << "🔊 Playing Adhan...\n";
        }

        char prayed;
        cout << "Did you pray " << next.first << "? (y/n): ";
        cin >> prayed;

        PrayerRecord record(user_id, next.first, "today");

        if (prayed == 'y' || prayed == 'Y') {
            record.save(db);
            record.markCompleted(db);
            cout << "Prayer saved as completed.\n";
        } else {
            record.save(db);
            cout << "Prayer saved as NOT completed.\n";
        }
    }
}
}
int main() {
    Database db;

    
    if (!db.connect("db/Alfalah.db")) {
        cerr << "Database connection failed.\n";
        return 1;
    }

    db.initialize();

    Login login(db);

    int choice;

    while (true) {
        cout << "\n========== Alfalah ==========\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Debug (Check DB)\n";
        cout << "4. Exit\n";
        cout << "Choice: ";

        cin >> choice;

        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

       
        if (choice == 1) {

            int user_id = login.DisplayLoginScreen();

            if (user_id == -1) {
                cout << "Login failed.\n";
                continue;
            }

            cout << "Login successful! User ID: " << user_id << endl;

            
            cout << "\n[DEBUG] Verifying user in DB...\n";
            debugSingleUser(db, user_id);

            
            runPrayerSystem(db, user_id);
        }

        
        else if (choice == 2) {
            login.Registery();
        }

        
        else if (choice == 3) {
            cout << "\n===== DEBUG MODE =====\n";
            debugDatabase(db);
            debugPrayerRecords(db);
            getAllUsers(db);
        }

        
        else if (choice == 4) {
            cout << "Exiting application...\n";
            break;
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    db.close();
    return 0;
}