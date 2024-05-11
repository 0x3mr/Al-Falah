#include "../includes.h"

void error(string errorType)
{
    if (errorType == "space")
        cout << "   (!) Error: You cannot use space in username or password.\n";
    else if (errorType == "invalidLogin")
        cout << "   (!) Invalid username or password!";
    else if (errorType == "signedOut")
        cout << "   (!) Please sign-in first to use this command.\n";
}