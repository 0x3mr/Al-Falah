#include "headers/user.h"





User::User(string username ,string password_hash){
    this->username = username;
    this->password_hash = password_hash;
    this ->id =0 ; 
    this->created_at= "";
}


User::User(int id , string username ,string password_hash, string created_at): id(id),username(username),password_hash(password_hash),created_at(created_at){}


string User::getcreated_at()  const{
    return created_at;
}

string User::getpassword_hash() const {
    return password_hash;
}


string User::getusername() const {
    return username;
}





int User::getid() const {
    return id;
}