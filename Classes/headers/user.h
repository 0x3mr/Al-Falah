#ifndef USER_H
#define USER_H
#include <iostream> 
#include <string>
using namespace std;

class User {
private: 
    int id ; 
    string username;
    string password_hash;
    string created_at;
    string last_location;
public:

    User(const std::string& username, const std::string& password_hash);
    User(int id,
         const std::string& username,
         const std::string& password_hash,
         const std::string& created_at,
         const std::string& last_location);



    int getId() const;
    void setId(int id);
    const std::string& getUsername() const;
    const std::string& getPasswordHash() const;
    const std::string& getCreatedAt() const;
    const std::string& getLastLocation() const;
    void setLastLocation(const std::string& location);
    // void saveLocation(Database& db, const std::string& location);



};

















#endif 