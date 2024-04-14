#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <string>
#include <fstream>
#include "C:/Curl/include/curl/curl.h"

using namespace std;

class duhr {
    public:
        void webScrapper();
        void callTime();
};

constexpr const char* const DATA_FILE = "data.txt";
constexpr const char* const LINKED_WEBSITE = "https://salah.com";

#endif
