#include "../includes.h"

// Callback function to write downloaded data to a file
size_t write_data(void *ptr, size_t size, size_t nmemb, ofstream *stream)
{
    size_t written = stream->write(static_cast<const char*>(ptr), size * nmemb).tellp();
    return written;
}

void duhr::webScrapper()
{
    ofstream file(DATA_FILE, ios::trunc);
    if (!file.is_open())
    {
        cerr << "Failed to open file: " << DATA_FILE << endl;
        return;
    }

    CURL *curl = curl_easy_init();
    if (!curl)
    {
        cerr << "Failed to initialize libcurl" << endl;
        file.close();
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, LINKED_WEBSITE);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
    }

    curl_easy_cleanup(curl);
    file.close();
}

void duhr::callTime()
{
    cout << "This is a test." << endl;
    this->webScrapper();
}
