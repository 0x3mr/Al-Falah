#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <WinINet.h>
#include <cctype>

using namespace std;

extern int bufferSize;
extern int salahFajr;
extern int salahSunrise;
extern int salahDuhr;
extern int salahAsr;
extern int salahMaghrib;
extern int salahIsha;
extern string url;

void extractTime(int Salah);
void scrapWebsite();

#endif
