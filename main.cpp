#include "includes.h"

void scrapWebsite()
{
    // Open the file to write the website contents
    std::ofstream outfile("data.txt");

    // Check if the file is opened successfully
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    // Website URL
    std::string url = "https://salah.com/";

    // Initialize WinINet
    HINTERNET hInternet = InternetOpenA("WinINet", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "Failed to initialize WinINet." << std::endl;
        return;
    }

    // Open the URL
    HINTERNET hUrl = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hUrl == NULL) {
        std::cerr << "Error opening URL: " << url << std::endl;
        InternetCloseHandle(hInternet);
        return;
    }

    // Read from the website and write to the file
    constexpr DWORD bufferSize = 1024;
    char buffer[bufferSize];
    DWORD bytesRead;
    while (InternetReadFile(hUrl, buffer, bufferSize, &bytesRead) && bytesRead > 0) {
        outfile.write(buffer, bytesRead);
    }

    // Close handles
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    // Close the file stream
    outfile.close();

    std::cout << "Website contents have been saved to data.txt" << std::endl;
}

class fajr {
    public:
        void extractTime()
        {
            // Open the data.txt file
            ifstream infile("data.txt");

            if (!infile.is_open())
            {
                cerr << "Error opening file." << endl;
            }

            // Read the file line by line
            string line;
            int i;
            int lineNumber = 0;
            string time;
            while (getline(infile, line))
            {
                lineNumber++;
                // Check if it's line 31
                if (lineNumber == 25)
                {
                    // Check if the line contains <span>
                    for (i = 0; line[i] != '/'; i++)
                    {
                        if (isdigit(line[i]) || line[i] == ':')
                        {
                            time += line[i];
                        }
                    }
                }
            }
            cout << time << endl;

            infile.close();
        }
};

class duhr {
    public:
        void extractTime()
        {
            // Open the data.txt file
            ifstream infile("data.txt");

            if (!infile.is_open())
            {
                cerr << "Error opening file." << endl;
            }

            // Read the file line by line
            string line;
            int i;
            int lineNumber = 0;
            string time;
            while (getline(infile, line))
            {
                lineNumber++;
                // Check if it's line 31
                if (lineNumber == 31)
                {
                    // Check if the line contains <span>
                    for (i = 0; line[i] != '/'; i++)
                    {
                        if (isdigit(line[i]) || line[i] == ':')
                        {
                            time += line[i];
                        }
                    }
                }
            }
            cout << time << endl;

            infile.close();
        }
};

class asr {
    public:
        void extractTime()
        {
            // Open the data.txt file
            ifstream infile("data.txt");

            if (!infile.is_open())
            {
                cerr << "Error opening file." << endl;
            }

            // Read the file line by line
            string line;
            int i;
            int lineNumber = 0;
            string time;
            while (getline(infile, line))
            {
                lineNumber++;
                // Check if it's line 31
                if (lineNumber == 34)
                {
                    // Check if the line contains <span>
                    for (i = 0; line[i] != '/'; i++)
                    {
                        if (isdigit(line[i]) || line[i] == ':')
                        {
                            time += line[i];
                        }
                    }
                }
            }
            cout << time << endl;

            infile.close();
        }
};

class maghrib {
    public:
        void extractTime()
        {
            // Open the data.txt file
            ifstream infile("data.txt");

            if (!infile.is_open())
            {
                cerr << "Error opening file." << endl;
            }

            // Read the file line by line
            string line;
            int i;
            int lineNumber = 0;
            string time;
            while (getline(infile, line))
            {
                lineNumber++;
                // Check if it's line 31
                if (lineNumber == 37)
                {
                    // Check if the line contains <span>
                    for (i = 0; line[i] != '/'; i++)
                    {
                        if (isdigit(line[i]) || line[i] == ':')
                        {
                            time += line[i];
                        }
                    }
                }
            }
            cout << time << endl;

            infile.close();
        }
};

class isha {
    public:
        void extractTime()
        {
            // Open the data.txt file
            ifstream infile("data.txt");

            if (!infile.is_open())
            {
                cerr << "Error opening file." << endl;
            }

            // Read the file line by line
            string line;
            int i;
            int lineNumber = 0;
            string time;
            while (getline(infile, line))
            {
                lineNumber++;
                // Check if it's line 31
                if (lineNumber == 40)
                {
                    // Check if the line contains <span>
                    for (i = 0; line[i] != '/'; i++)
                    {
                        if (isdigit(line[i]) || line[i] == ':')
                        {
                            time += line[i];
                        }
                    }
                }
            }
            cout << time << endl;

            infile.close();
        }
};

//int main(int ac, char **av)
int main()
{
    string interfacer;
    // (void)ac;
    // (void)av;

    while (1)
    {
        cout << "\nWhat interface would you like to use?\nType [1] for CLI [2] for GUI [0] to exit: ";
        getline(cin, interfacer);

        if (interfacer.length() == 1)
        {
            if (interfacer[0] == '0' || interfacer[0] == '1' || interfacer[0] == '2')
                break;
        }
    }

    // EXITING PROGRAM CODE
    if (interfacer[0] == '0')
    {
        cout << "\nExiting program..\n" << endl;
        return (0);
    }

    // CLI CODE
    if (interfacer[0] == '1')
    {
        string input;

        cout << "\n";

        while (1)
        {
            cout << "$ ";
            getline(cin, input);
            
            if (input.substr(0, 5) == "fetch" && input.length() == 5)
            {
                cout << "\n  List of prayers you can fetch:\n";
                cout << "   - fajr\n   - sunrise\n   - duhr\n   - asr\n   - maghrib\n   - isha\n \n";

            }
            else if (input.substr(0, 10) == "fetch fajr" && input.length() == 10)
            {
                fajr instance;

                scrapWebsite();
                fajr().extractTime();
            }
            else if (input.substr(0, 10) == "fetch duhr" && input.length() == 10)
            {
                duhr instance;

                scrapWebsite();
                duhr().extractTime();
            }
            else if (input.substr(0, 9) == "fetch asr" && input.length() == 9)
            {
                asr instance;

                scrapWebsite();
                asr().extractTime();
            }
            else if (input.substr(0, 13) == "fetch maghrib" && input.length() == 13)
            {
                maghrib instance;

                scrapWebsite();
                maghrib().extractTime();
            }
            else if (input.substr(0, 10) == "fetch isha" && input.length() == 10)
            {
                isha instance;

                scrapWebsite();
                isha().extractTime();
            }
            else if ((input.substr(0, 4) == "quit" && input.length() == 4) || (input[0] == '0' && input.length() == 1) || (input[0] == 'q' && input.length() == 1))
            {
                cout << "Exiting CLI mode." << endl;
                break;
            }
        }
    }

    // GUI CODE
    if (interfacer[0] == '2')
    {
        // Enter GUI mode.
        cout << "\n *** NOT OPERATIONAL AT THE MOMENT *** \n" << endl;
    }

    return (0);
}
