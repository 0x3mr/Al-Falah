// Include the User.h header file
#include "User.h"

// Constructor for the User class, initializes username, password, points, level, and settings
User::User(const string& username, const string& password) : username(username), password(password), points(0), level(0), settings("OFF") {}

// Destructor for the User class, does nothing
User::~User() {}

// Getter method for the username
string User::getusername() const { return username; }

// Getter method for the password
string User::getPassword() const { return password; }

// Getter method for the settings
string User::getSettings() const { return settings; }

// Getter method for the points
int User::getPoints() const { return points; }

// Getter method for the level
int User::getLevel() const { return level; }

// Setter method for the username
void User::setusername(const string& username) { this->username = username; }

// Setter method for the password
void User::setPassword(const string& password) { this->password = password; }

// Setter method for the points
void User::setPoints(const int& points) { this->points = points; }

// Setter method for the level
void User::setLevel(const int& level) { this->level = level; }

// Setter method for the settings
void User::setSettings(const string& settings) { this->settings = settings; }