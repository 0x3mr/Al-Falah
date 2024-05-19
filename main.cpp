#include "includes.h" // Include a header file containing other included files
#include "Classes/User.h" // Include the User class header file
#include "Classes/RegisteredUser.h" // Include the RegisteredUser class header file
#include "Classes/PrayerTime.h" // Include the PrayerTime class header file

int bufferSize = 1024; // Set a buffer size for reading data

// Line numbers where each salah time is included in data.txt
int salahFajr = 25; // Line number for Fajr salah time
int salahSunrise = 28; // Line number for Sunrise salah time
int salahDuhr = 31; // Line number for Duhr salah time
int salahAsr = 34; // Line number for Asr salah time
int salahMaghrib = 37; // Line number for Maghrib salah time
int salahIsha = 40; // Line number for Isha salah time

string url = "https://salah.com"; // URL for prayer times data

//int main(int ac, char **av) // Original main function signature, commented out
int main() // Simplified main function signature
{
    string mode; // Variable to store the user's chosen interface mode

    clear(); // Clear the console screen

    /* Choose mode of the application */
    // If 1 it will use CLI
    // If 2 it will use GUI but it's in development atm
    // If 0 it will exit the program
    while (1) // Infinite loop until user chooses a valid mode
    {
        cout << "\nWhat interface would you like to use?\nType [1] for CLI [2] for GUI [0] to exit: "; // Prompt user to choose an interface mode
        getline(cin, mode); // Read user's input into the mode variable

        //mode = '1'; // THIS IS USED FOR DEVELOPMENT ONLY, commented out

        if (mode.length() == 1) // Check if the input is a single character
        {
            if (mode[0] == '0' || mode[0] == '1' || mode[0] == '2') // Check if the input is one of the valid options
                break; // Exit the loop if valid input
        }
    }

    // EXITING PROGRAM CODE
    if (mode[0] == '0') // If user chose to exit
    {
        cout << "\nExiting program..\n" << endl; // Print exit message
        return (0); // Return 0 to indicate successful exit
    }

    // Entering CLI Mode
    if (mode[0] == '1') // If user chose to use CLI
    {
        string input; // Variable to store user's input
        string username = "-", password = "-"; // Initialize username and password to default values
        string prefix = ""; // Initialize prefix string to empty
        string loggedin = "no"; // Initialize login status to "no"

        RegisteredUser* user = nullptr; // Pointer to a RegisteredUser object, initialized to null

        clear(); // Clear the console screen
        welcome("startup"); // Print a welcome message

        PrayerTime prayerTimes(url, bufferSize, salahFajr, salahSunrise, salahDuhr, salahAsr, salahMaghrib, salahIsha); // Create a PrayerTime object

        while (1) // Infinite loop for CLI mode
        {
            input = ""; // Reset input variable
            cout << prefix << " $ "; // Print the command prompt
            getline(cin, input); // Read user's input into the input variable

            // Handle register command
            if (input.substr(0, 8) == "register") 
            {           
                if (input.substr(0, 8) == "register" && input.length() == 8)
                {
                    welcome("register"); // Print a welcome message for registration
                    do
                    {
                        cout << "    * Enter username: "; // Prompt user to enter username
                        getline(cin, username);

                        cout << "    * Enter password: "; // Prompt user to enter password
                        getline(cin, password);

                        if (username.find(' ') != string::npos || password.find(' ') != string::npos)
                        {
                            error("space"); // Handle error if username or password contain spaces
                        }
                    } while (username.find(' ') != string::npos || password.find(' ') != string::npos);
                }

                if (input.substr(0, 9) == "register " && count(input.begin(), input.end(), ' ') == 2 && input.find("  ") == std::string::npos)
                {
                    size_t space_pos;
                    string temp_username, temp_password;

                    space_pos = input.find(' ');
                    temp_username = input.substr(space_pos + 1);
                    space_pos = temp_username.find(' ');

                    temp_password = temp_username.substr(space_pos + 1);
                    temp_username.erase(space_pos);

                    username = temp_username;
                    password = temp_password;
                }

                // if successful register
                user = new RegisteredUser(username, password);
                user->signUp();
                cout << "\n";
                prefix = username;
                loggedin = "yes";
                clear();
                welcome("successfulRegister"); // Print a welcome message for successful registration
            }

            // Handle login command
            if (input.substr(0, 5) == "login")
            {
                if (input.substr(0, 5) == "login" && input.length() == 5)
                {
                    welcome("login"); // Print a welcome message for login
                    do
                    {
                        cout << "    * Enter username: "; // Prompt user to enter username
                        getline(cin, username);

                        cout << "    * Enter password: "; // Prompt user to enter password
                        getline(cin, password);

                        if (username.find(' ') != string::npos || password.find(' ') != string::npos)
                        {
                            error("space"); // Handle error if username or password contain spaces
                        }
                    } while (username.find(' ') != string::npos || password.find(' ') != string::npos);
                }

                if (input.substr(0, 6) == "login " && count(input.begin(), input.end(), ' ') == 2 && input.find("  ") == std::string::npos)
                {
                    size_t space_pos;
                    string temp_username, temp_password;

                    space_pos = input.find(' ');
                    temp_username = input.substr(space_pos + 1);
                    space_pos = temp_username.find(' ');

                    temp_password = temp_username.substr(space_pos + 1);
                    temp_username.erase(space_pos);

                    username = temp_username;
                    password = temp_password;
                }

                if (username != "-" && password != "-")
                {
                    user = new RegisteredUser(username, password);
                    // if successful login
                    if (user->login(username, password))
                    {
                        // THINGS THAT HAPPEN WHEN YOU ARE LOGGED IN
                        cout << "\n";
                        prefix = username;
                        loggedin = "yes";
                        clear();

                        if (user->getSettings() == "ON")
                        {
                            welcome("successfulLogin_Special"); // Print a special welcome message
                            cout << "        Fajr | Sunrise |  Duhr   |  Asr   | Maghrib | Isha\n";
                            cout << "        " << prayerTimes.getFajrTime() << "     " << prayerTimes.getSunriseTime() << "     " << prayerTimes.getDuhrTime() << "     " << prayerTimes.getAsrTime() << "     " << prayerTimes.getMaghribTime() << "     " << prayerTimes.getIshaTime( ) << "\n\n";
                            cout << "             Type 'commands' to use the application..\n\n";
                        }
                        else
                        {
                            welcome("successfulLogin"); // Print a regular welcome message
                        }

                        delete user;
                        user = new RegisteredUser(username, password);
                        user->loadUserData("userData.txt");
                    }
                    else
                    {
                        error("invalidLogin"); // Handle error if login fails
                    }
                    //delete user;
                }
            }

            //  TESTER & DEBUGGING
            //
            // if (user != nullptr && prefix != "")
            // {
                // cout << "GLOBAL - INFO HERE:  " << user->getusername() << endl;
                // cout << "GLOBAL - INFO HERE:  " << user->getPassword() << endl;
                // cout << "GLOBAL - INFO HERE:  " << user->getPoints() << endl;
                // cout << "GLOBAL - INFO HERE:  " << user->getLevel() << endl;
                // cout << "GLOBAL - INFO HERE:  " << user->getSettings() << endl;
            // }

            // Handle settings command
            if (input.substr(0, 8) == "settings" && input.length() == 8)
            {
                if (loggedin == "yes")
                {
                    string mode;
                    cout << "\n";
                    cout << "    | Profile > " << user->getusername() << "  > Settings >\n    |\n";
                    cout << "    | - Special Welcome: " << user->getSettings() << "\n";
                    //cout << "       (when enabled, it showcases prayer times on login)\n";
                    cout << "    | - Reminders: undefined\n\n";
                    //cout << "       (currently unavailable)\n";

                    do {
                        cout << "    | Would you like to toggle on/off special welcome?\n    | (type 1 to toggle, 0 to cancel)\n    | ";
                        getline(cin, mode);

                        if (mode == "1") {
                            if (user->getSettings() == "ON") {
                                user->setSettings("OFF");
                                user->saveUserData("userData.txt");
                                cout << "\n    | Special welcome screen has been turned off.\n\n";
                            } else {
                                user->setSettings("ON");
                                user->saveUserData("userData.txt");
                                cout << "\n    | Special welcome screen has been turned on.\n\n";
                            }
                            break;
                        } else if (mode == "0") {
                            cout << "\n    | No changes made to the settings.\n\n";
                            break;
                        } else {
                            cout << "\n    | Invalid input. Please enter either 1 or 0.\n";
                        }
                    } while (true);
                }
                else
                {
                    error("signedOut"); // Handle error if user is not logged in
                }
            }

            // Handle points command
            if (input.substr(0, 6) == "points" && input.length() == 6)
            {
                if (loggedin == "yes")
                {
                    cout << "\n * You have " << user->getPoints() << " on your account.\n\n";
                }
                else { error("signedOut"); } // Handle error if user is not logged in
            }

            // Handle quiz command
            if (input.substr(0, 4) == "quiz" && input.length() == 4)
            {
                if (loggedin == "yes")
                {
                    int correctAnswers;
                    correctAnswers = quiz();

                    if (correctAnswers == 0)
                    {
                        clear();
                        cout << "\nAll your answers were wrong :(\nNo points received.\n\n";
                    }
                    else if (correctAnswers == 404)
                    {
                        clear();
                    }
                    else
                    {
                        clear();
                        cout << "\nCongratulations!\nYou answered " << correctAnswers << " questions!\nYou received " << correctAnswers * 5 << " points.\n\n";
                        // code for adding the points to the user account
                        user->addPoints(correctAnswers * 5);
                        user->saveUserData("userData.txt");
                    }
                }
                else { error("signedOut"); } // Handle error if user is not logged in
            }

            // Handle commands command
            if ((input.substr(0, 8) == "commands" && input.length() == 8) || (input.substr(0, 4) == "cmds" && input.length() == 4))
            {
                    cout << "\n  List of available commands:\n";
                    cout << "   - fetch\n   - quiz\n   - quit\n   - logout\n   - cmds\n   - settings\n   - points\n \n";
            }

            // Handle fetch command
            if (loggedin == "yes")
            {
                if (input.substr(0, 5) == "fetch" && input.length() == 5)
                {
                    cout << "\n  List of prayers you can fetch:\n";
                    cout << "   - fajr\n   - sunrise\n   - duhr\n   - asr\n   - maghrib\n   - isha\n \n";
                }
                else if (input.substr(0, 10) == "fetch fajr" && input.length() == 10)
                {
                    cout << "Fajr Time: " << prayerTimes.getFajrTime() << endl;
                }
                else if (input.substr(0, 13) == "fetch sunrise" && input.length() == 13)
                {
                    cout << "Sunrise Time: " << prayerTimes.getSunriseTime() << endl;
                }
                else if (input.substr(0, 10) == "fetch duhr" && input.length() == 10)
                {
                    cout << "Duhr Time: " << prayerTimes.getDuhrTime() << endl;
                }
                else if (input.substr(0, 9) == "fetch asr" && input.length() == 9)
                {
                    cout << "Asr Time: " << prayerTimes.getAsrTime() << endl;
                }
                else if (input.substr(0, 13) == "fetch maghrib" && input.length() == 13)
                {
                    cout << "Maghrib Time: " << prayerTimes.getMaghribTime() << endl;
                }
                else if (input.substr(0, 10) == "fetch isha" && input.length() == 10)
                {
                    cout << "Isha Time: " << prayerTimes.getIshaTime() << endl;
                }
            }
            else
            {
                if (input.substr(0, 5) == "fetch")
                    error("signedOut"); // Handle error if user is not logged in
            }

            // Handle logout command
            if ((input.substr(0, 6) == "logout" && input.length() == 6) || (input.substr(0, 7) == "signout" && input.length() == 7))
            {
                if (loggedin == "yes")
                {
                    prefix = "";
                    loggedin = "no";
                    clear();
                    welcome("successfulLogout"); // Print a logout message
                }
                else
                {
                    error("signedOut"); // Handle error if user is not logged in
                }
            }

            // Handle quit command
            if (loggedin == "no")
            {
                delete user;
                user = nullptr;
            }

            // Handle quit command
            if (input.length() <= 4) { input = decapitalize(input); }
            if ((input.substr(0, 4) == "quit" && input.length() == 4) || (input[0] == '0' && input.length() == 1) || (input[0] == 'q' && input.length() == 1))
            {
                cout << "Exiting CLI mode." << endl; // Print a quit message
                prefix = "";
                loggedin = "no";
                delete user;
                user = nullptr;
                break; // Exit the loop
            }
        }
    }

    // GUI CODE
    if (mode[0] == '2')
    {
        // Enter GUI mode.
        cout << "\n *** NOT OPERATIONAL AT THE MOMENT *** \n" << endl; // Print a message indicating GUI mode is not operational
    }

    return (0); // Return 0 to indicate successful execution
}