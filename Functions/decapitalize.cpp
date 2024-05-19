// Include the includes.h header file from the parent directory
#include "../includes.h"

// Function to decapitalize a string (convert to lowercase)
string decapitalize(string input)
{
    // Use the transform algorithm to iterate over the input string
    // and convert each character to lowercase using the tolower function
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    // Return the modified string
    return input;
}