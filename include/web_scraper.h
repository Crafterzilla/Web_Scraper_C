#ifndef WEB_SCRAPER_H
#define WEB_SCRAPER_H

#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>


// Enum to represent if an error occured
enum CURL_CODE {
    SUCCESS,
    ERROR
};


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
enum CURL_CODE web_scraper(const char* filename, const char* website);



#endif
