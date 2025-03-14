/*
Purpose: Create a simple web scraper that takes a URL
and outputs a file with the HTML Data
*/

#include "../include/web_scraper.h"

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
enum CURL_CODE web_scraper(const char* filename, const char* website) {
    //Type code here
}
