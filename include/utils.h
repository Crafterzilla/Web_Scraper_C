#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* typedef struct url_array { */
/*     char** urls; */
/*     int size; */
/* } url_array; */

typedef struct str_array {
    char** strings;
    int size;
} str_array;

/*
Desc: Read file from user like urls.txt. With such file,
read each line and return an array of strings.

Input:
    const char* filename: Name of file to be read
Ret: Returns a struct url_array that contain ptr to array of strings and its size
*/
str_array read_str_file(const char* filename);


/*
Desc: This function is to be used to write the amount of times a word has been counted
for an html file to a file.

Input:
    char* filename: Name of the file that the output will be written to
    char** words: array of words that were counted from the html file
    int* count: the number of times those words were counted from the html file
    const int size: number of words counted
*/
void write_count_results_to_file(char* filename, char* url, char** words, int* count, const int size);

/*
Desc: Takes in a url_array and frees the memory back to the OS

Input:
    url_array* arr: Name of file to be read
*/
void free_str_array(str_array arr);


/*
Desc: Reads the html files that were created by web_scraper.c and then creates
an array of FILE* to then be used for multicount

Input:
    int size: Number of html files created
*/
FILE** create_file_array(int size);


#endif
