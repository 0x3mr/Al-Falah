#include "includes.h"

int bufferSize = 1024;
int salahFajr = 25;
int salahSunrise = 28;
int salahDuhr = 31;
int salahAsr = 34;
int salahMaghrib = 37;
int salahIsha = 40;
string url = "https://salah.com";

//int main(int ac, char **av)
int main()
{
    string mode;

    while (1)
    {
        cout << "\nWhat interface would you like to use?\nType [1] for CLI [2] for GUI [0] to exit: ";
        getline(cin, mode);

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

        cout << "\n";

        scrapWebsite();

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
            else if ((input.substr(0, 4) == "quit" && input.length() == 4) || (input[0] == '0' && input.length() == 1) || (input[0] == 'q' && input.length() == 1))
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
