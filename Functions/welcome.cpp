#include "../includes.h"

void welcome(string message)
{
    if (message == "startup")
    {
        cout << "\n Assalamu Alaikum wa Rahmatullahi wa Barakatuh\n\n";
        cout << "        Welcome to Al-Falah Prayer App.";
        cout << "\n   Please Log-in or Sign-up to use the app.\n";
        cout << "\n         Commands   |  login <username>";
        cout << "\n                    |  register <username>\n\n\n";
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
        cout << "\n         You have signed up successfully!\n\n";
        cout << "          Welcome to Al-Falah Prayer App.";
        cout << "\n   Please Log-in or Sign-up to use the app.\n";
        cout << "\n                    |  fetch";
        cout << "\n         Commands   |  quiz";
        cout << "\n                    |  cmds\n\n\n";
    }
    else if (message == "successfulLogout")
    {
        cout << "\n          You have signed out successfully!\n\n";
        cout << "            Welcome to Al-Falah Prayer App.";
        cout << "\n  You may use the app using the following commands:\n";
        cout << "\n         Commands   |  login <username>";
        cout << "\n                    |  register <username>\n\n\n";
    }
    else if (message == "successfulLogin")
    {
        cout << "\n                  Successful Login!\n\n";
        cout << "             Welcome to Al-Falah Prayer App.";
        cout << "\n  You may use the app using the following commands:\n";
        cout << "\n                    |  fetch";
        cout << "\n         Commands   |  quiz";
        cout << "\n                    |\n\n\n";
    }
    else if (message == "successfulLogin_Special")
    {
        cout << "\n                  Welcome to Al-Falah Prayer App.\n\n";
    }
    else if (message == "quiz")
    {
        cout << "\n       -*- QUIZ GAME -*-\n\n";
        cout << "     Are you ready to begin?\n\n";
        cout << "         [1] Continue\n";
    }
}