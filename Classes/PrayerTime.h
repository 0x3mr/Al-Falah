#ifndef PRAYERTIME_H
#define PRAYERTIME_H

#include "../includes.h"

class PrayerTime {
private:
    string url;
    int bufferSize;
    int salahFajr, salahSunrise, salahDuhr, salahAsr, salahMaghrib, salahIsha;
    void scrapWebsite();
    void extractTime(int salahLine, string& timeStr);

public:
    PrayerTime(const string& url, int bufferSize, int salahFajr, int salahSunrise, int salahDuhr, int salahAsr, int salahMaghrib, int salahIsha);

    string getFajrTime();
    string getSunriseTime();
    string getDuhrTime();
    string getAsrTime();
    string getMaghribTime();
    string getIshaTime();
};

#endif