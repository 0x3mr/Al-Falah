#include "PrayerTime.h"

// Scrap the website and save the data to a file
void PrayerTime::scrapWebsite()
{
    // Open a file stream to write to a file called "data.txt"
    ofstream outfile("../data.txt");

    // Check if the file was opened successfully
    if (!outfile.is_open())
    {
        // If not, print an error message and return
        cerr << "Error opening file for writing." << endl;
        return; /* it stops reading the rest of the code */
    }

    // Initialize WinINet, a Windows API for internet connections
    HINTERNET hInternet = InternetOpenA("WinINet", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL)
    {
        // If initialization fails, print an error message and return
        cerr << "Failed to initialize WinINet." << endl;
        return;
    }

    // Open the URL using InternetOpenUrlA
    HINTERNET hUrl = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hUrl == NULL)
    {
        // If the URL cannot be opened, print an error message and close the internet handle
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

    // Close the URL and internet handles
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    // Close the file stream
    outfile.close();
}

// Extract a prayer time from the data file
void PrayerTime::extractTime(int salahLine, string& timeStr)
{
    // Open the data.txt file for reading
    ifstream infile("../data.txt");

    if (!infile.is_open())
    {
        // If the file cannot be opened, print an error message
        cerr << "Error opening file." << endl;
    }

    string line, time;
    int i, lineNumber = 0;

    // Read the file line by line
    while (getline(infile, line))
    {
        lineNumber++;

        // If the current line is the one we're looking for (based on salahLine)
        if (lineNumber == salahLine)
        {
            // Extract the time from the line (assuming it's in a <span> tag)
            for (i = 0; line[i] != '/'; i++)
            {
                if (isdigit(line[i]) || line[i] == ':')
                    time += line[i];
            }
        }
    }
    // Set the timeStr parameter to the extracted time
    timeStr = time;

    // Close the file stream
    infile.close();
}

// Constructor for PrayerTime objects
PrayerTime::PrayerTime(const string& url, int bufferSize, int salahFajr, int salahSunrise, int salahDuhr, int salahAsr, int salahMaghrib, int salahIsha)
    : url(url), bufferSize(bufferSize), salahFajr(salahFajr), salahSunrise(salahSunrise), salahDuhr(salahDuhr), salahAsr(salahAsr), salahMaghrib(salahMaghrib), salahIsha(salahIsha) {}

// Getter functions for each prayer time
string PrayerTime::getFajrTime() { string time; extractTime(salahFajr, time); return time; }
string PrayerTime::getSunriseTime() { string time; extractTime(salahSunrise, time); return time; }
string PrayerTime::getDuhrTime() { string time; extractTime(salahDuhr, time); return time; }
string PrayerTime::getAsrTime() { string time; extractTime(salahAsr, time); return time; }
string PrayerTime::getMaghribTime() { string time; extractTime(salahMaghrib, time); return time; }
string PrayerTime::getIshaTime() { string time; extractTime(salahIsha, time); return time; }