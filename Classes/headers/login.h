#ifndef LOGIN_H
#define LOGIN_H
#include "database.h"

#include <iostream>
class login {
private: 
    Database& db;  // Reference to the database for user authentication
public:
    login(Database& database) : db(database) {}

    void DisplayLoginScreen() {}

    bool authenticate(const std::string& username, const std::string& password) {}

    
    void Dispaly_message(bool authenticate){}

    void Registery() {}
    







};













#endif 