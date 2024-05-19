#include "RegisteredUser.h"

RegisteredUser::RegisteredUser(const string& username, const string& password) : User(username, password) {}

RegisteredUser::~RegisteredUser() {}

bool RegisteredUser::login(const string& username, const string& password) {
    ifstream file("userData.txt");
    string line;
    bool userFound = false;

    while (getline(file, line)) {
        string usernameFromFile, passwordFromFile, pointsStr, levelStr, settings;
        size_t pos = line.find('*');

        usernameFromFile = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('*');
        passwordFromFile = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('*');
        pointsStr = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('*');
        levelStr = line.substr(0, pos);
        line.erase(0, pos + 1);

        settings = line;

        if (usernameFromFile == username) {
            userFound = true;
            if (passwordFromFile == password) {
                setusername(usernameFromFile);
                setPassword(passwordFromFile);
                setPoints(stoi(pointsStr));
                setLevel(stoi(levelStr));
                setSettings(settings);
                file.close();
                return true;
            } else {
                error("invalidPassword");
                file.close();
                return false;
            }
        }
    }

    if (!userFound)
    {
        error("invalidUser");
    }

    file.close();
    return false;
}

void RegisteredUser::signUp() {
    ifstream file("userData.txt");
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

    if (userExists)
    {
        error("existingUser");
    }
    else
    {
        ofstream file("userData.txt", ios::app);
        file << username << "*" << password << "*0*0*OFF" << endl;
        file.close();
    }
}

void RegisteredUser::forgotPassword(const string& username)
{
    ifstream file("userData.txt");
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

void RegisteredUser::updateUserData(const RegisteredUser& user)
{
    ifstream file("userData.txt");
    ofstream tempFile("temp.txt");

    string line;
    while (getline(file, line)) {
        string usernameFromFile, passwordFromFile, pointsStr, levelStr, settings;
        size_t pos = line.find('*');

        usernameFromFile = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('*');
        passwordFromFile = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('*');
        pointsStr = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('*');
        levelStr = line.substr(0, pos);
        line.erase(0, pos + 1);

        settings = line;

        if (usernameFromFile == user.getusername()) {
            tempFile << user.getusername() << "*" << user.getPassword() << "*" << user.getPoints() << "*" << user.getLevel() << "*" << user.getSettings() << endl;
        } else {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

    remove("userData.txt");
    rename("temp.txt", "userData.txt");
}

void RegisteredUser::addPoints(int pointsToAdd)
{
    setPoints(getPoints() + pointsToAdd);
    updateUserData(*this);
}

void RegisteredUser::loadUserData(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        string usernameFromFile, passwordFromFile, pointsStr, levelStr, settings;
        size_t pos = line.find('*');
        usernameFromFile = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find('*');
        passwordFromFile = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find('*');
        pointsStr = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find('*');
        levelStr = line.substr(0, pos);
        line.erase(0, pos + 1);
        settings = line;

        if (usernameFromFile == username) {
            setPassword(passwordFromFile);
            setPoints(stoi(pointsStr));
            setLevel(stoi(levelStr));
            setSettings(settings);
            break;
        }
    }
    file.close();
}

void RegisteredUser::saveUserData(const string& filename)
{
    vector<string> lines;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    for (auto& l : lines) {
        size_t pos = l.find('*');
        string usernameFromFile = l.substr(0, pos);
        if (usernameFromFile == username)
        {
            l = username + "*" + password + "*" + to_string(points) + "*" + to_string(level) + "*" + settings;
            break;
        }
    }

    ofstream fileOut(filename);
    for (const auto& l : lines) {
        fileOut << l << endl;
    }
    fileOut.close();
}