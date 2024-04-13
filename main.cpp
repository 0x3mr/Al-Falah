#include <iostream>
#include <string>
using namespace std;

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
        ;
    }

    // GUI CODE
    if (interface[0] == '2')
    {
        cout << " *** NOT OPERATIONAL AT THE MOMENT *** " << endl;
    }

    return (0);
}