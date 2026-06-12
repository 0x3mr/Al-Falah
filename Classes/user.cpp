#include "headers/user.h"

// New user (before DB insert)
User::User(const std::string& username, const std::string& password_hash) {
    this->username = username;
    this->password_hash = password_hash;
    this->id = 0;
    this->created_at = "";
    this->last_location = "";
}

// Existing user (from DB)
User::User(int id,
           const std::string& username,
           const std::string& password_hash,
           const std::string& created_at,
           const std::string& last_location)
    : id(id),
      username(username),
      password_hash(password_hash),
      created_at(created_at),
      last_location(last_location) {}

// Getters
const std::string& User::getCreatedAt() const {
    return created_at;
}

const std::string& User::getPasswordHash() const {
    return password_hash;
}

const std::string& User::getUsername() const {
    return username;
}

int User::getId() const {
    return id;
}

const std::string& User::getLastLocation() const {
    return last_location;
}

// Setters
void User::setLastLocation(const std::string& location) {
    this->last_location = location;
}

void User::setId(int id) {
    this->id = id;
}




// void User::saveLocation(Database& db, const std::string& location) {
//     sqlite3* conn = db.getDB();

//     const char* sql = "UPDATE users SET last_location = ? WHERE id = ?;";
//     sqlite3_stmt* stmt;

//     if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) {
//         std::cerr << "[ERROR] Failed to prepare statement\n";
//         return;
//     }

//     sqlite3_bind_text(stmt, 1, location.c_str(), -1, SQLITE_STATIC);
//     sqlite3_bind_int(stmt, 2, this->id);

//     if (sqlite3_step(stmt) != SQLITE_DONE) {
//         std::cerr << "[ERROR] Failed to save location\n";
//     } else {
//         std::cout << "[INFO] Location saved successfully\n";
//         this->last_location = location; 
//     }

//     sqlite3_finalize(stmt);
// }