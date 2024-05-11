#include "../includes.h"

void clear() {
    #ifdef _WIN32
    system("cls"); // For Windows
    #else
    system("clear"); // For Linux
    #endif
}