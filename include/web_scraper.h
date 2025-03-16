#ifndef WEB_SCRAPER_H
#define WEB_SCRAPER_H

#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
//Add includes go here


// Enum to represent if an error occured
enum CURL_CODE {
    SUCCESS,
    WEBSITE_NOT_FOUND,
    ERROR
    //ADD MORE CODES FOR MORE ERRORS
};


/*
Desc: The basic single threaded web_scraper. This function
takes a website and checks and sees if the website is active
or exists. If an error occurs, it returns a code representing
the error. If success, then it prints out the HTML file to the
./output/"filename paramter".html

Input:
    filename: Name of file for output file
    website: website to be scraped and see HTML contents
Ret: An error code or success code

*/
enum CURL_CODE web_scraper(const char* filename, const char* website);



#endif
