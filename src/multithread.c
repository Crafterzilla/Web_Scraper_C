#include "../include/multithread.h"

/* 
Desc: Takes in list of URLS gathered from URL file. Then it calls web_scraper
multiple times for each different URL to put into a thread pool. The thread pool
then executes and runs the scraper on the websites at the same time. This will result
in multiple files in ./output for each URL. Should overall be very fast. Handles invalid
or URLs that are not functional with web_scraper.h implementation. Returns code for error
if anything occurs with the multithreading

Input:
    URL_list: An array of strings that represent potentially valid URLS
    size: Size of the array of strings
Ret: Any thread error code
*/
enum THREAD_CODE multifetch_websites(const char** URL_list, const int size) {
    // Your code here

    //Use web_scraper("filename", "URL_list[i]");
}


/* 
Desc: Takes in an array of file objects that point to the files in ./output. It counts the number of times those
words occur in each file using count's implemenation and does it in paralell. Once it counts all the reoccurances
and puts them into reports (Done by count.h), it counts the total times the words occurred in ALL files.

Input:
    output_HTML_files: An array of file objects to be read from
    file_array_size: size of output_HTML_files
    words: array of words to be counted
    word_size: number of words in array words
Ret: Any thread error code
*/
enum THREAD_CODE multicount(FILE** output_HTML_files, const int file_array_size, const char** words, const int word_size) {
    // Your code here
    // Use count_all_reoccurances()
}
