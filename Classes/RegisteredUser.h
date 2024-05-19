#ifndef REGISTEREDUSER_H
#define REGISTEREDUSER_H

#include "User.h" // Include the base class
#include "../includes.h"

class RegisteredUser : public User {
public:
    RegisteredUser(const string& username, const string& password);
    ~RegisteredUser();

    bool login(const string& username, const string& password);
    void signUp();
    void forgotPassword(const string& username);
    void updateUserData(const RegisteredUser& user);
    void addPoints(int pointsToAdd);
    void loadUserData(const string& filename);
    void saveUserData(const string& filename);
};

#endif