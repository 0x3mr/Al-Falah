#include "../includes.h"

string decapitalize(string input)
{
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}