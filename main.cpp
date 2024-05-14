#include "includes.h"

int bufferSize = 1024;

// Line of where each salah time is included in data.txt
int salahFajr = 25;
int salahSunrise = 28;
int salahDuhr = 31;
int salahAsr = 34;
int salahMaghrib = 37;
int salahIsha = 40;

string url = "https://salah.com";

// CLASSES

class User
{
    protected:
        string username, password;
    public:
        User(const string &username, const string &password) : username(username), password(password) {}

        virtual ~User() {}

        string getusername() const { return username; }
        string getPassword() const { return password; }

        void setusername(const string &username) { this->username = username; }
        void setPassword(const string &password) { this->password = password; }
};

class RegisteredUser : public User {
public:
    RegisteredUser(const string &username, const string &password): User(username, password) {}

    ~RegisteredUser() {}

    bool login(const string &username, const string &password)
    {
        ifstream file("loginData.txt");
        string line;
        bool userFound = false;

        while (getline(file, line))
        {
            string usernameFromFile, passwordFromFile;
            size_t pos = line.find('*');

            usernameFromFile = line.substr(0, pos);
            line.erase(0, pos + 1);

            passwordFromFile = line;

            if (usernameFromFile == username)
            {
                userFound = true;
                if (passwordFromFile == password)
                {
                    file.close();
                    return true;
                }
                else
                {
                    //cout << "Invalid password for user: " << username << endl;
                    error("invalidPassword");
                    file.close();
                    return false;
                }
            }
        }

        if (!userFound) {
            //cout << "User " << username << " does not exist." << endl;
            error("invalidUser");
        }

        file.close();
        return false;
    }

    void signUp() {
        ifstream file("loginData.txt");
        string line;
        bool userExists = false;

        while (getline(file, line)) {
            string usernameFromFile;
            size_t pos = line.find('*');

            usernameFromFile = line.substr(0, pos);

            if (usernameFromFile == username) {
                userExists = true;
                break;
            }
        }

        file.close();

        if (userExists) {
            //cout << "User " << username << " already exists. Cannot register." << endl;
            error("existingUser");
        } else {
            ofstream file("loginData.txt", ios::app);
            file << username << "*" << password << endl;
            file.close();
        }
    }

    void forgotPassword(const string &username)
    {
        ifstream file("loginData.txt");
        string line;

        while (getline(file, line))
        {
            string usernameFromFile, passwordFromFile;
            size_t pos = line.find('*');

            usernameFromFile = line.substr(0, pos);
            line.erase(0, pos + 1);

            passwordFromFile = line;

            if (usernameFromFile == username)
            {
                cout << "   [+] Account Found!" << endl;
                cout << "   [!] Your Password: " << passwordFromFile << endl;
                break;
            }
        }
        file.close();
    }
};

//int main(int ac, char **av)
int main()
{
    string mode;
    
    clear();

    while (1)
    {
        cout << "\nWhat interface would you like to use?\nType [1] for CLI [2] for GUI [0] to exit: ";
        //getline(cin, mode);
        mode = '1'; // THIS IS USED FOR DEVELOPMENT ONLY

        if (mode.length() == 1)
        {
            if (mode[0] == '0' || mode[0] == '1' || mode[0] == '2')
                break;
        }
    }

    // EXITING PROGRAM CODE
    if (mode[0] == '0')
    {
        cout << "\nExiting program..\n" << endl;
        return (0);
    }

    // CLI CODE
    if (mode[0] == '1')
    {
        string input;
        string username, password;
        string prefix = "";
        string loggedin = "no";

        RegisteredUser* user = nullptr;

        cout << "\n";

        // scrapWebsite();
        // Add it back if user logins in only

        clear();
        welcome("startup");

        while (1)
        {
            cout << prefix << " $ ";
            getline(cin, input);
            
            if (input.substr(0, 5) == "login" && input.length() == 5)
            {
                welcome("login");
                do {
                    cout << "    * Enter username: ";
                    getline(cin, username);

                    cout << "    * Enter password: ";
                    getline(cin, password);

                    if (username.find(' ') != string::npos || password.find(' ') != string::npos) { error("space"); }
                } while (username.find(' ') != string::npos || password.find(' ') != string::npos);

                // if successful login
                user = new RegisteredUser(username, password);
                if (user->login(username, password))
                {
                    cout << "\n";
                    prefix = username;
                    loggedin = "yes";
                    clear();
                    welcome("successfulLogin");
                }
                else
                {
                    error("invalidLogin");
                }
                delete user;
            }
            else if (input.substr(0, 6) == "login " && count(input.begin(), input.end(), ' ') == 2)
            {
                cout << "SECOND LOGIN OPTION" << endl;
            }
            else if (input.substr(0, 8) == "register" && input.length() == 8)
            {
                welcome("register");
                do {
                    cout << "    * Enter username: ";
                    getline(cin, username);

                    cout << "    * Enter password: ";
                    getline(cin, password);

                    if (username.find(' ') != string::npos || password.find(' ') != string::npos) { error("space"); }
                } while (username.find(' ') != string::npos || password.find(' ') != string::npos);

                // if successful register
                user = new RegisteredUser(username, password);
                user->signUp();
                delete user;
                cout << "\n";
                prefix = username;
                loggedin = "yes";
                clear();
                welcome("successfulRegister");
            }
            else if (input.substr(0, 9) == "register " && count(input.begin(), input.end(), ' ') == 2)
            {
                cout << "SECOND REGISTER OPTION" << endl;
            }
            else if (input.substr(0, 6) == "logout" && input.length() == 6)
            {
                if (loggedin == "yes")
                {
                    cout << "Logged out successfully!" << endl;
                    prefix = "";
                    loggedin = "no";
                    clear();
                    welcome("startup");
                }
                else
                {
                    cout << "You're not logged in!" << endl;
                }
            }
            
            if (loggedin == "yes")
            {
                if (input.substr(0, 5) == "fetch" && input.length() == 5)
                {
                    cout << "\n  List of prayers you can fetch:\n";
                    cout << "   - fajr\n   - sunrise\n   - duhr\n   - asr\n   - maghrib\n   - isha\n \n";

                }
                else if (input.substr(0, 10) == "fetch fajr" && input.length() == 10)
                {
                    extractTime(salahFajr);
                }
                else if (input.substr(0, 13) == "fetch sunrise" && input.length() == 13)
                {
                    extractTime(salahSunrise);
                }
                else if (input.substr(0, 10) == "fetch duhr" && input.length() == 10)
                {
                    extractTime(salahDuhr);
                }
                else if (input.substr(0, 9) == "fetch asr" && input.length() == 9)
                {
                    extractTime(salahAsr);
                }
                else if (input.substr(0, 13) == "fetch maghrib" && input.length() == 13)
                {
                    extractTime(salahMaghrib);
                }
                else if (input.substr(0, 10) == "fetch isha" && input.length() == 10)
                {
                    extractTime(salahIsha);
                }
            }
            else
            {
                if (input.substr(0, 5) == "fetch")
                    error("signedOut");
            }
            
            if (input.length() <= 4) { input = decapitalize(input); }
            if ((input.substr(0, 4) == "quit" && input.length() == 4) || (input[0] == '0' && input.length() == 1) || (input[0] == 'q' && input.length() == 1))
            {
                cout << "Exiting CLI mode." << endl;
                break;
            }
        }
    }

    // GUI CODE
    if (mode[0] == '2')
    {
        // Enter GUI mode.
        cout << "\n *** NOT OPERATIONAL AT THE MOMENT *** \n" << endl;
    }

    return (0);
}
