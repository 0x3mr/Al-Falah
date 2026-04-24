#ifndef LOGIN_H
#define LOGIN_H
#include "database.h"

#include <iostream>
class Login {
private: 
    Database& db;  // Reference to the database for user authentication
public:
    Login(Database& database) ;

   

    bool authenticate(const std::string& username, const std::string& password) ;

    
    void Dispaly_message(bool authenticate);

    void Registery() ;

    int DisplayLoginScreen();
    
};













#endif 