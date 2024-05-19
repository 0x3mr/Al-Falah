#include "PrayerTime.h"

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

PrayerTime::PrayerTime(const string& url, int bufferSize, int salahFajr, int salahSunrise, int salahDuhr, int salahAsr, int salahMaghrib, int salahIsha)
    : url(url), bufferSize(bufferSize), salahFajr(salahFajr), salahSunrise(salahSunrise), salahDuhr(salahDuhr), salahAsr(salahAsr), salahMaghrib(salahMaghrib), salahIsha(salahIsha) {}

string PrayerTime::getFajrTime() { string time; extractTime(salahFajr, time); return time; }
string PrayerTime::getSunriseTime() { string time; extractTime(salahSunrise, time); return time; }
string PrayerTime::getDuhrTime() { string time; extractTime(salahDuhr, time); return time; }
string PrayerTime::getAsrTime() { string time; extractTime(salahAsr, time); return time; }
string PrayerTime::getMaghribTime() { string time; extractTime(salahMaghrib, time); return time; }
string PrayerTime::getIshaTime() { string time; extractTime(salahIsha, time); return time; }