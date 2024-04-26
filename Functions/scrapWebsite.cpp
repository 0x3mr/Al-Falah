#include "../includes.h"

void scrapWebsite()
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