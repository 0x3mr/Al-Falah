#include "../includes.h"

void welcome(string message)
{
    if (message == "startup")
    {
        cout << "\nAssalamu Alaikum wa Rahmatullahi wa Barakatuh\n\n";
        cout << "       Welcome to Al-Falah Prayer App.";
        cout << "\n  Please Log-in or Sign-up to use the app.\n";
        cout << "\n                | login <username>";
        cout << "\n   Continue >   | register <username>";
        cout << "\n                | reset <username>\n\n\n";
    }
    else if (message == "login")
    {
        cout << "\n   (*) Sign-in\n";
    }
    else if (message == "register")
    {
        cout << "\n   (*) Sign-up\n";
    }
    else if (message == "successfulRegister")
    {
        cout << "\n            You have signed up successfully!\n\n";
        cout << "             Welcome to Al-Falah Prayer App.";
        cout << "\n  You may use the app using the following commands:\n";
        cout << "\n                | fetch";
        cout << "\n     Commands   |";
        cout << "\n                |\n\n\n";
    }
    else if (message == "successfulLogin")
    {
        cout << "\n                  Successful Login!\n\n";
        cout << "             Welcome to Al-Falah Prayer App.";
        cout << "\n  You may use the app using the following commands:\n";
        cout << "\n                | fetch";
        cout << "\n     Commands   |";
        cout << "\n                |\n\n\n";
    }
}