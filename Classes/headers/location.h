#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <iostream>
#include "database.h"
using namespace std;
class Location {
private:
    double latitude;
    double longitude;
    string city;
    string country;
    Database* db;
public:
    Location(double latitude, double longitude, const string& city, const string& country);
    Location();
    Location getCurrentLocation() const; // This would normally use an API to get the current location
    Location manuallySetLocation();
    void displayLocation() const ;
    string getLocation() const;
    double getLatitude() const ;
    double getLongitude() const ;
    void saveLocation(Database& db, const string& location,int user_id);
    
};









#endif