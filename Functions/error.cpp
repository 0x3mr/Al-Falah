// Include the includes.h header file from the parent directory
#include "../includes.h"

// Function to display error messages based on the error type
void error(string errorType)
{
    // Check the error type and display the corresponding error message
    if (errorType == "space")
        // Display error message for spaces in username or password
        cout << "   (!) Error: You cannot use space in username or password.\n";
    else if (errorType == "invalidPassword")
        // Display error message for incorrect password
        cout << "   (!) Your password is incorrect.\n";
    else if (errorType == "invalidUser")
        // Display error message for non-existent account
        cout << "   (!) Account does not exist!\n";
    else if (errorType == "existingUser")
        // Display error message for existing user (likely a registration error)
        cout << "   (!) User does not exist.\n";
    else if (errorType == "signedOut")
        // Display error message for attempting to use a command without signing in
        cout << "   (!) Please sign-in first to use this command.\n";
}