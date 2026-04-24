#include "headers/database.h"
#include "headers/login.h"
#include "headers/user.h"
#include <iostream>
#include <string>
#include <sqlite3.h>

Login::Login(Database& database) : db(database) {}

void Login::Dispaly_message(bool authenticate){
    if (authenticate) {
        std::cout << "Login successful! Welcome to Alflalah Prayer App." << std::endl;
    } else {
        std::cout << "Login failed! Please check your username and password." << std::endl;

    }
}
bool Login::authenticate(const std::string& username, const std::string& password) {
    sqlite3* dbConnection = db.getDB();
    if(!dbConnection){
        std::cout<<"Database is not conected " ; 
        return false;
    }
    std::string Query = "SELECT id FROM users WHERE username = ? AND password_hash =?";
    sqlite3_stmt * stmt =nullptr ; 
    int result = sqlite3_prepare_v2(dbConnection,Query.c_str(),-1,&stmt,nullptr);
    if(result != SQLITE_OK){
        std::cout<<"Failed to prepare statement: "<<sqlite3_errmsg(dbConnection)<<std::endl;
        return false;
    }
    sqlite3_bind_text(stmt,1,username.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,password.c_str(),-1,SQLITE_TRANSIENT);

    int step = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return step == SQLITE_ROW; // If a row is returned, authentication is successful
}
void Login::Registery() {

    std::string username, password;

    std::cout << "Enter a username: ";
    std::cin >> username;

    std::cout << "Enter a password: ";
    std::cin >> password;

    sqlite3* dbConnection = db.getDB();

    if (!dbConnection) {
        std::cout << "Database is not connected\n";
        return;
    }

    std::string query = "INSERT INTO users (username, password_hash) VALUES (?, ?);";
    sqlite3_stmt* stmt = nullptr;

    int rc = sqlite3_prepare_v2(dbConnection, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cout << "Prepare failed: " << sqlite3_errmsg(dbConnection) << std::endl;
        return;
    }


    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_DONE) {

        long long newId = sqlite3_last_insert_rowid(dbConnection);
        std::cout << "Registration successful! Your user ID is: " << newId << std::endl;

    } else if (rc == SQLITE_CONSTRAINT) {

        std::cout << "Username already exists.\n";

    } else {

        std::cout << "Execution failed: " << sqlite3_errmsg(dbConnection) << std::endl;

    }

    sqlite3_finalize(stmt);
}
int Login::DisplayLoginScreen() {
    std::string username, password;

    std::cout << "Welcome to Alflalah Prayer App!" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Please log in to continue." << std::endl;

    std::cout << "Username: ";
    std::cin >> username;

    std::cout << "Password: ";
    std::cin >> password;

    bool isAuthenticated = authenticate(username, password);
    Dispaly_message(isAuthenticated);

    if (!isAuthenticated) {
        return -1;  // ❌ login failed
    }

    // ✅ Fetch user_id from DB
    sqlite3* conn = db.getDB();

    const char* sql = "SELECT id FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to fetch user ID\n";
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    int user_id = -1;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user_id = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return user_id;  
}