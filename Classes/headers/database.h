#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>


class Database {
private:
    sqlite3* db;

public:
    Database();
    ~Database();

    bool connect(const std::string& dbName);
    void initialize();
    void close();

    sqlite3* getDB();  
};




#endif  // DATABASE_H
