/*
Purpose: Create a simple web scraper that takes a URL
and outputs a file with the HTML Data
*/

#include "../include/web_scraper.h"
#include <curl/curl.h>

/*
Desc: The basic single threaded web_scraper. This function
takes a website and checks and sees if the website is active
or exists. If an error occurs, it returns a code representing
the error. Please write file stating that URL is invalid and which
code was thrown. If success, then it prints out the HTML file to the
./output/"filename paramter".html

Input:
    filename: Name of file for output file
    website: website to be scraped and see HTML contents
Ret: An error code or success code

*/

enum CURL_CODE web_scraper(const char *filename, const char *website);
size_t write_data_to_file(char *data, size_t item_size, size_t num_of_items, void *ignore);

int main() {
	web_scraper("output.html", "https://en.wikipedia.org/wiki/Dog");
	return 0;
}

enum CURL_CODE web_scraper(const char *filename, const char *website) {
	CURL *curl;
	CURLcode result;

	curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "Error: HTTP request failed.\n");
		return ERROR;
	}

	curl_easy_setopt(curl, CURLOPT_URL, website);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_to_file);

	result = curl_easy_perform(curl);
	if (result != CURLE_OK) {
		fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
		return ERROR;
	}

	curl_easy_cleanup(curl);

	return SUCCESS;
}

size_t write_data_to_file(char *data, size_t item_size, size_t num_of_items, void *ignore) {
	size_t bytes = item_size * num_of_items;

	for (size_t i = 0; i < bytes; i++) {
		printf("%c", data[i]);
	}

	return bytes;
}
