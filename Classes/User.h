#ifndef USER_H
#define USER_H

#include "../includes.h"

class User {
protected:
    string username, password, settings;
    int points, level;

public:
    User(const string& username, const string& password);
    virtual ~User();

    string getusername() const;
    string getPassword() const;
    string getSettings() const;
    int getPoints() const;
    int getLevel() const;

    void setusername(const string& username);
    void setPassword(const string& password);
    void setPoints(const int& points);
    void setLevel(const int& level);
    void setSettings(const string& settings);
};

#endif