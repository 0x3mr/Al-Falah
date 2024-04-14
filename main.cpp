#include "includes.h"

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
            else if (input.substr(0, 10) == "fetch duhr" && input.length() == 10)
            {
                duhr().callTime();
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
