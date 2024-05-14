#include "../includes.h"

void error(string errorType)
{
    if (errorType == "space")
        cout << "   (!) Error: You cannot use space in username or password.\n";
    else if (errorType == "invalidPassword")
        cout << "   (!) Your password is incorrect.\n";
    else if (errorType == "invalidUser")
        cout << "   (!) Account does not exist!\n";
    else if (errorType == "existingUser")
        cout << "   (!) User does not exist.\n";
    else if (errorType == "signedOut")
        cout << "   (!) Please sign-in first to use this command.\n";
}