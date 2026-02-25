#ifndef USER_H
#define USER_H
#include <iostream> 
#include <string>
#include "database.h"
using namespace std;

class User {
private: 
    int id ; 
    string username;
    string password_hash;
    string created_at;
public:

    User(string username ,string password_hash);
    User(int id , string username ,string password_hash, string created_at);



    int getid()const;
    string getusername()const;
    string getpassword_hash()const;
    string getcreated_at()const;


    


};

















#endif 