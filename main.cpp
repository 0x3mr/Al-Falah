#include "Classes/headers/database.h"
#include "Classes/headers/login.h"
#include "Classes/headers/user.h"
#include <iostream>
using namespace std;

int main() {
    Database db;
    if (db.connect("db/Alfalah.db")) {
        db.initialize();
        cout << "Database initialized successfully." << endl;
    } else {
        cerr << "Failed to connect to the database." << endl;
        return 1;
    }
    std::cout << "Welcome to Alflalah Prayer App!" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Register" << std::endl;
    int choice;
    std::cin >> choice;
    if(choice == 1){
         Login loginScreen(db);
        loginScreen.DisplayLoginScreen();
    } else if (choice == 2) {
        Login loginScreen(db);
        loginScreen.Registery();
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
    }
    

    return 0;
}