#include <iostream>
#include <string>
using namespace std;

class CLI {
    private:
        string input;

    public:
        void printName()
        {
            cout << "This is a test." << endl;
        }
};

int main()
{
    string interface;

    while (1)
    {
        cout << "What interface would you like to use?\nType 1 for CLI and 2 for GUI: ";
        getline(cin, interface);
        cout << "\n" << endl;

        if (interface.length() == 1)
        {
            if (interface[0] == '0' || interface[0] == '1' || interface[0] == '2')
                break;
        }
    }

    // EXITING PROGRAM CODE
    if (interface[0] == '0')
    {
        cout << "Exiting program..\n" << endl;
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
                cout << "working" << endl;
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