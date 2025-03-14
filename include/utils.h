#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct url_array {
    char** urls;
    int size;
} url_array;

/*
Desc: Read file from user like urls.txt. With such file,
read each line and return an array of strings.

Input:
    const char* filename: Name of file to be read
Ret: Returns a struct url_array that contain ptr to array of strings and its size
*/
url_array read_urls_file(const char* filename);

/*
Desc: Takes in a file object and reads until it reaches EOF or newline
Then it creates a char* in the heap and returns that ptr

Input:
    file: File ptr to be read from
Ret: Returns the string read from the file's one line
*/
char* readline_from_file(FILE* file);

#endif
