/*
Purpose: Create a simple web scraper that takes a URL
and outputs a file with the HTML Data

TODO: Remove need to specify file extension in filename parameter
*/

#include "../include/web_scraper.h"


// Function Declarations for Private Functions
size_t write_to_file(char *data, size_t size, size_t bytes, char *filename);


/*
	This function uses libcurl's easy interface to fetch
	raw HTML data from a specified website URL and writes
	that output to a .html file with a specified filename.
    In case the fetching fails, it returns that code for
    error handling. It's single threaded and to be used for
    the multithreaded solution.

	@param filename : The name of the output file
	@param website: The website URL to fetch from
	@return : SUCCESS or ERROR code
*/
enum CURL_CODE web_scraper(const char *filename, const char *website) {
	CURL *curl;
	CURLcode result;

	// Initialize the curl handle used as the input for other curl functions.
	curl = curl_easy_init();

	// Error handling when curl is equal to NULL.
	if (!curl) {
		fprintf(stderr, "Error: HTTP request failed.\n");
		return ERROR;
	}

	// Sets the URL used to perform the fetch request.
	curl_easy_setopt(curl, CURLOPT_URL, website);

	// Calls write_to_file each time a chunk of data is received.
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_file);

	// Passes the filename as the fourth argument to write_to_file.
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, filename);

	// Perform the fetch request with the specified CURLOPT options.
	result = curl_easy_perform(curl);
	// Error handling when the fetch request is unsuccessful.
	if (result != CURLE_OK) {
		fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
		return ERROR;
	}

	// Closes and frees up resources associated with this handle.
	curl_easy_cleanup(curl);

	return SUCCESS;
}

/*
	This is the callback function passed to CURLOPT_WRITEFUNCTION.
	Since CURLOPT_WRITEFUNCTION fetches data in chunks,
	this function is called each time a new chunk of data is received.
	It appends the received data to a new file named after the specified filename.

	@param *data : A pointer to the chunk of data delivered
	@param size : The value of size is always 1
	@param bytes : The number of bytes that the chunk of data contains
	@param *filename : Name of the file that the data is being written to
	@return : ERROR code or the number of bytes
*/
size_t write_to_file(char *data, size_t size, size_t bytes, char *filename) {
	// File pointer to the file that the data is being written to
	FILE *file;

	// TODO: Prevent appending to existing file, e.g. create a new file each time
	// Open the file in append mode
	file = fopen(filename, "a");
	// Error handling when the file cannot be opened.
	if (file == NULL) {
		printf("Error: Error opening file!\n");
		return ERROR;
	}

	// Loops through each byte of the data and appends it to the file
	for (size_t i = 0; i < bytes; i++) {
		fprintf(file, "%c", data[i]);
	}

	// Close the file after writing to it
	fclose(file);

	/*
		Required to return the number of bytes or else
		the function will error if the amount differs from
		the amount passed to the callback function.
	*/
	return bytes;
}
