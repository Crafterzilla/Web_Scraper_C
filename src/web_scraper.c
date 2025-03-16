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
size_t write_callback(char *data, size_t size, size_t bytes, void *ignore);

int main() {
	web_scraper("output.html", "https://en.wikipedia.org/wiki/Dog");
	return 0;
}

/*
	This function uses libcurl's easy interface to fetch
	raw HTML data from a specified website URL and writes
	that output to a .html file with a specified filename.

	@param filename : The name of the output file
	@param website: The website URL to fetch from
*/
enum CURL_CODE web_scraper(const char *filename, const char *website) {
	CURL *curl;
	CURLcode result;

	curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "Error: HTTP request failed.\n");
		return ERROR;
	}

	curl_easy_setopt(curl, CURLOPT_URL, website);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

	result = curl_easy_perform(curl);
	if (result != CURLE_OK) {
		fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
		return ERROR;
	}

	curl_easy_cleanup(curl);

	return SUCCESS;
}

/*
	The callback function passed to CURLOPT_WRITEFUNCTION.
	Since CURLOPT_WRITEFUNCTION fetches data in chunks,
	this function is called each time a new chunk of data is received.

	@param *data : A pointer to the chunk of data delivered
	@param size : The value of size is always 1
	@param bytes : The number of bytes that the chunk of data contains
	@param *ignore : Ignore this.
*/
size_t write_callback(char *data, size_t size, size_t bytes, void *ignore) {
	// Loops through each byte of the data and sends it to stdout.
	for (size_t i = 0; i < bytes; i++) {
		printf("%c", data[i]);
	}

	/*
		Required to return the number of bytes or else
		the function will error if the amount differs from
		the amount passed to the callback function.
	*/
	return bytes;
}
