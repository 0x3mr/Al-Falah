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
        int points, level;
    public:
        User(const string &username, const string &password) : username(username), password(password), points(0), level(0) {}

        virtual ~User() {}

        string getusername() const { return username; }
        string getPassword() const { return password; }
        int getPoints() const { return points; }
        int getLevel() const { return level; }

        void setusername(const string &username) { this->username = username; }
        void setPassword(const string &password) { this->password = password; }
        void setPoints(const int &points) { this->points = points; }
        void setLevel(const int &level) { this->level = level; }
};

class RegisteredUser : public User
{
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

            if (userFound == false)
            {
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

class PrayerTime
{
    private:
        string url;
        int bufferSize;
        int salahFajr, salahSunrise, salahDuhr, salahAsr, salahMaghrib, salahIsha;
        void scrapWebsite();
        void extractTime(int salahLine, string& timeStr);

    public:
        //                                                   CALLING OF THE CONSTRUCTOR STRUCTURE
        //
        //                                    The line of where you will find each prayer in the data.txt file
        //                                    25            28         31          34           37          40
        //                                     ↓             ↓          ↓           ↓            ↓           ↓
        //   PrayerTime( url , bufferSize , Fajr line , Sunrise line , Duhr line , Asr line , Maghrib line, Isha line )
        //
        PrayerTime(const string& url, int bufferSize, int salahFajr, int salahSunrise, int salahDuhr, int salahAsr, int salahMaghrib, int salahIsha)
            : url(url), bufferSize(bufferSize), salahFajr(salahFajr), salahSunrise(salahSunrise), salahDuhr(salahDuhr), salahAsr(salahAsr), salahMaghrib(salahMaghrib), salahIsha(salahIsha) {}

        string getFajrTime() { string time; extractTime(salahFajr, time); return time; }
        string getSunriseTime() { string time; extractTime(salahSunrise, time); return time; }
        string getDuhrTime() { string time; extractTime(salahDuhr, time); return time; }
        string getAsrTime() { string time; extractTime(salahAsr, time); return time; }
        string getMaghribTime() { string time; extractTime(salahMaghrib, time); return time; }
        string getIshaTime() { string time; extractTime(salahIsha, time); return time; }
};

void PrayerTime::scrapWebsite()
{
    ofstream outfile("../data.txt");

    if (!outfile.is_open())
    {
        cerr << "Error opening file for writing." << endl;
        return; /* it stops reading the rest of the code */
    }

    // Initialize WinINet
    HINTERNET hInternet = InternetOpenA("WinINet", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL)
    {
        cerr << "Failed to initialize WinINet." << endl;
        return;
    }

    // Open the URL
    HINTERNET hUrl = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hUrl == NULL)
    {
        //cerr << "Error opening URL: " << url << endl;
        cerr << "Unable to connect to the internet." << endl;
        InternetCloseHandle(hInternet);
        return;
    }

    // Read from the website and write to the file
    char buffer[bufferSize];
    DWORD bytesRead;
    while (InternetReadFile(hUrl, buffer, bufferSize, &bytesRead) && bytesRead > 0)
    {
        outfile.write(buffer, bytesRead);
    }

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    outfile.close();
}

void PrayerTime::extractTime(int salahLine, string& timeStr)
{
    // Open the data.txt file
    ifstream infile("../data.txt");

    if (!infile.is_open())
    {
        cerr << "Error opening file." << endl;
    }

    string line, time;
    int i, lineNumber = 0;

    while (getline(infile, line))
    {
        lineNumber++;

        if (lineNumber == salahLine)
        {
            // Check if the line contains <span>
            for (i = 0; line[i] != '/'; i++)
            {
                if (isdigit(line[i]) || line[i] == ':')
                    time += line[i];
            }
        }
    }
    timeStr = time;

    infile.close();
}

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
        string username = "-", password = "-";
        string prefix = "";
        string loggedin = "no";

        RegisteredUser* user = nullptr;

        clear();
        welcome("startup");

        while (1)
        {
            input = "";
            cout << prefix << " $ ";
            getline(cin, input);
            
            if (input.substr(0, 5) == "login")
            {
                if (input.substr(0, 5) == "login" && input.length() == 5)
                {
                    welcome("login");
                    do
                    {
                        cout << "    * Enter username: ";
                        getline(cin, username);

                        cout << "    * Enter password: ";
                        getline(cin, password);

                        if (username.find(' ') != string::npos || password.find(' ') != string::npos)
                        {
                            error("space");
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

                if (username != "-" && username != "-")
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
                        welcome("successfulLogin");
                    }
                    else
                    {
                        error("invalidLogin");
                    }
                    delete user;
                }
            }

            if (input.substr(0, 8) == "register")
            {           
                if (input.substr(0, 8) == "register" && input.length() == 8)
                {
                    welcome("register");
                    do
                    {
                        cout << "    * Enter username: ";
                        getline(cin, username);

                        cout << "    * Enter password: ";
                        getline(cin, password);

                        if (username.find(' ') != string::npos || password.find(' ') != string::npos)
                        {
                            error("space");
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
                delete user;
                cout << "\n";
                prefix = username;
                loggedin = "yes";
                clear();
                welcome("successfulRegister");
            }

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
                    }
                }
                else { error("signedOut"); }
            }
            
            if (loggedin == "yes")
            {
                PrayerTime prayerTimes(url, bufferSize, salahFajr, salahSunrise, salahDuhr, salahAsr, salahMaghrib, salahIsha);

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
                    error("signedOut");
            }
            
            if (input.substr(0, 6) == "logout" && input.length() == 6)
            {
                if (loggedin == "yes")
                {
                    prefix = "";
                    loggedin = "no";
                    clear();
                    welcome("successfulLogout");
                }
                else
                {
                    error("signedOut");
                }
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
