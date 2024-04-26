#include "../includes.h"

void extractTime(int Salah)
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

        if (lineNumber == Salah)
        {
            // Check if the line contains <span>
            for (i = 0; line[i] != '/'; i++)
            {
                if (isdigit(line[i]) || line[i] == ':')
                    time += line[i];
            }
        }
    }
    cout << time << endl;

    infile.close();
}