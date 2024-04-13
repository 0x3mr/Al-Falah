#include "includes.h"

//int main(int ac, char **av)
int main()
{
    string interface;
    // (void)ac;
    // (void)av;

    while (1)
    {
        cout << "\nWhat interface would you like to use?\nType 1 for CLI and 2 for GUI: ";
        getline(cin, interface);

        if (interface.length() == 1)
        {
            if (interface[0] == '0' || interface[0] == '1' || interface[0] == '2')
                break;
        }
    }

    // EXITING PROGRAM CODE
    if (interface[0] == '0')
    {
        cout << "\nExiting program..\n" << endl;
        return (0);
    }

    // CLI CODE
    if (interface[0] == '1')
    {
        string input;

        while (1)
        {
            cout << "$ ";
            getline(cin, input);
            
            if (input.substr(0, 10) == "fetch duhr" && input.length() == 10)
            {
                cout << "Calling class: CLI" << endl;

                CLI duhr;

                duhr.printMsg();
            }
            else if ((input.substr(0, 4) == "quit" && input.length() == 4) || (input[0] == '0' && input.length() == 1) || (input[0] == 'q' && input.length() == 1))
            {
                cout << "Exiting CLI mode." << endl;
                break;
            }
        }
    }

    // GUI CODE
    if (interface[0] == '2')
    {
        // Enter GUI mode.
        cout << " *** NOT OPERATIONAL AT THE MOMENT *** " << endl;
    }

    return (0);
}
