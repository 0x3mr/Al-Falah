#include "RegisteredUser.h"  // Include the header file for the RegisteredUser class

// Constructor for the RegisteredUser class, taking a username and password as parameters
RegisteredUser::RegisteredUser(const string& username, const string& password) : User(username, password) {}

// Destructor for the RegisteredUser class
RegisteredUser::~RegisteredUser() {}

// Login function for a registered user
bool RegisteredUser::login(const string& username, const string& password) {
    ifstream file("userData.txt");  // Open the user data file for reading
    string line;
    bool userFound = false;  // Flag to indicate if the user is found

    while (getline(file, line)) {  // Read the file line by line
        string usernameFromFile, passwordFromFile, pointsStr, levelStr, settings;
        size_t pos = line.find('*');  // Find the position of the first '*' in the line

        usernameFromFile = line.substr(0, pos);  // Extract the username from the line
        line.erase(0, pos + 1);  // Remove the username and '*' from the line

        pos = line.find('*');  // Find the position of the next '*' in the line
        passwordFromFile = line.substr(0, pos);  // Extract the password from the line
        line.erase(0, pos + 1);  // Remove the password and '*' from the line

        pos = line.find('*');  // Find the position of the next '*' in the line
        pointsStr = line.substr(0, pos);  // Extract the points from the line
        line.erase(0, pos + 1);  // Remove the points and '*' from the line

        pos = line.find('*');  // Find the position of the next '*' in the line
        levelStr = line.substr(0, pos);  // Extract the level from the line
        line.erase(0, pos + 1);  // Remove the level and '*' from the line

        settings = line;  // Extract the settings from the line

        if (usernameFromFile == username) {  // Check if the username matches
            userFound = true;
            if (passwordFromFile == password) {  // Check if the password matches
                setusername(usernameFromFile);  // Set the username
                setPassword(passwordFromFile);  // Set the password
                setPoints(stoi(pointsStr));  // Set the points
                setLevel(stoi(levelStr));  // Set the level
                setSettings(settings);  // Set the settings
                file.close();  // Close the file
                return true;  // Return true if the login is successful
            } else {
                error("invalidPassword");  // Display an error message if the password is invalid
                file.close();  // Close the file
                return false;  // Return false if the login is unsuccessful
            }
        }
    }

    if (!userFound)  // Check if the user is not found
    {
        error("invalidUser");  // Display an error message if the user is not found
    }

    file.close();  // Close the file
    return false;  // Return false if the login is unsuccessful
}

// Sign up function for a new user
void RegisteredUser::signUp() {
    ifstream file("userData.txt");  // Open the user data file for reading
    string line;
    bool userExists = false;  // Flag to indicate if the user already exists

    while (getline(file, line)) {  // Read the file line by line
        string usernameFromFile;
        size_t pos = line.find('*');  // Find the position of the first '*' in the line

        usernameFromFile = line.substr(0, pos);  // Extract the username from the line

        if (usernameFromFile == username) {  // Check if the username already exists
            userExists = true;
            break;
        }
    }

    file.close();  // Close the file

    if (userExists)  // Check if the user already exists
    {
        error("existingUser");  // Display an error message if the user already exists
    } else {  // If the user does not exist, create a new user
        ofstream file("userData.txt", ios::app);  // Open the user data file for appending
        file << username << "*" << password << "*0*0*OFF" << endl;  // Write the new user data to the file
        file.close();  // Close the file
    }
}

// Function to retrieve a forgotten password
void RegisteredUser::forgotPassword(const string& username)
{
    ifstream file("userData.txt");  // Open the user data file for reading
    string line;

    while (getline(file, line)) {  // Read the file line by line
        string usernameFromFile, passwordFromFile;
        size_t pos = line.find('*');  // Find the position of the first '*' in the line

        usernameFromFile = line.substr(0, pos);  // Extract the username from the line
        line.erase(0, pos + 1);  // Remove the username and '*' from the line

        passwordFromFile = line;  // Extract the password from the line

        if (usernameFromFile == username) {  // Check if the username matches
            cout << "   [+] Account Found!" << endl;
            cout << "   [!] Your Password: " << passwordFromFile << endl;
            break;
        }
    }
    file.close();  // Close the file
}

// Function to update user data
void RegisteredUser::updateUserData(const RegisteredUser& user) {
    ifstream file("userData.txt");  // Open the user data file for reading
    ofstream tempFile("temp.txt");  // Open a temporary file for writing

    string line;
    while (getline(file, line)) {  // Read the file line by line
        string usernameFromFile, passwordFromFile, pointsStr, levelStr, settings;
        size_t pos = line.find('*');  // Find the position of the first '*' in the line

        usernameFromFile = line.substr(0, pos);  // Extract the username from the line
        line.erase(0, pos + 1);  // Remove the username and '*' from the line

        pos = line.find('*');  // Find the position of the next '*' in the line
        passwordFromFile = line.substr(0, pos);  // Extract the password from the line
        line.erase(0, pos + 1);  // Remove the password and '*' from the line

        pos = line.find('*');  // Find the position of the next '*' in the line
        pointsStr = line.substr(0, pos);  // Extract the points from the line
        line.erase(0, pos + 1);  // Remove the points and '*' from the line

        pos = line.find('*');  // Find the position of the next '*' in the line
        levelStr = line.substr(0, pos);  // Extract the level from the line
        line.erase(0, pos + 1);  // Remove the level and '*' from the line

        settings = line;  // Extract the settings from the line

        if (usernameFromFile == user.getusername()) {  // Check if the username matches
            tempFile << user.getusername() << "*" << user.getPassword() << "*" << user.getPoints() << "*" << user.getLevel() << "*" << user.getSettings() << endl;  // Write the updated user data to the temporary file
        } else {
            tempFile << line << endl;  // Write the unchanged user data to the temporary file
        }
    }

    file.close();  // Close the file
    tempFile.close();  // Close the temporary file

    remove("userData.txt");  // Remove the original file
    rename("temp.txt", "userData.txt");  // Rename the temporary file to the original file name
}

// Function to add points to a user's account
void RegisteredUser::addPoints(int pointsToAdd) {
    setPoints(getPoints() + pointsToAdd);  // Update the points
    updateUserData(*this);  // Update the user data file
}

// Function to load user data from a file
void RegisteredUser::loadUserData(const string& filename) {
    ifstream file(filename);  // Open the user data file for reading
    string line;
    while (getline(file, line)) {  // Read the file line by line
        string usernameFromFile, passwordFromFile, pointsStr, levelStr, settings;
        size_t pos = line.find('*');  // Find the position of the first '*' in the line
        usernameFromFile = line.substr(0, pos);  // Extract the username from the line
        line.erase(0, pos + 1);  // Remove the username and '*' from the line
        pos = line.find('*');  // Find the position of the next '*' in the line
        passwordFromFile = line.substr(0, pos);  // Extract the password from the line
        line.erase(0, pos + 1);  // Remove the password and '*' from the line
        pos = line.find('*');  // Find the position of the next '*' in the line
        pointsStr = line.substr(0, pos);  // Extract the points from the line
        line.erase(0, pos + 1);  // Remove the points and '*' from the line
        pos = line.find('*');  // Find the position of the next '*' in the line
        levelStr = line.substr(0, pos);  // Extract the level from the line
        line.erase(0, pos + 1);  // Remove the level and '*' from the line
        settings = line;  // Extract the settings from the line

        if (usernameFromFile == username) {  // Check if the username matches
            setPassword(passwordFromFile);  // Set the password
            setPoints(stoi(pointsStr));  // Set the points
            setLevel(stoi(levelStr));  // Set the level
            setSettings(settings);  // Set the settings
            break;
        }
    }
    file.close();  // Close the file
}

// Function to save user data to a file
void RegisteredUser::saveUserData(const string& filename)
{
    vector<string> lines;
    ifstream file(filename);  // Open the user data file for reading
    string line;
    while (getline(file, line))  // Read the file line by line
    {
        lines.push_back(line);
    }
    file.close();  // Close the file

    for (auto& l : lines) {  // Iterate over the lines
        size_t pos = l.find('*');  // Find the position of the first '*' in the line
        string usernameFromFile = l.substr(0, pos);  // Extract the username from the line
        if (usernameFromFile == username)  // Check if the username matches
        {
            l = username + "*" + password + "*" + to_string(points) + "*" + to_string(level) + "*" + settings;  // Update the user data
            break;
        }
    }

    ofstream fileOut(filename);  // Open the user data file for writing
    for (const auto& l : lines) {
        fileOut << l << endl;  // Write the updated user data to the file
    }
    fileOut.close();  // Close the file
}