#include "User.h"

User::User(const string& username, const string& password) : username(username), password(password), points(0), level(0), settings("OFF") {}

User::~User() {}

string User::getusername() const { return username; }
string User::getPassword() const { return password; }
string User::getSettings() const { return settings; }
int User::getPoints() const { return points; }
int User::getLevel() const { return level; }

void User::setusername(const string& username) { this->username = username; }
void User::setPassword(const string& password) { this->password = password; }
void User::setPoints(const int& points) { this->points = points; }
void User::setLevel(const int& level) { this->level = level; }
void User::setSettings(const string& settings) { this->settings = settings; }