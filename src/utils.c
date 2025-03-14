// Purpose: This file mainly deals with I/O and getting input from the user
// so that data can be used for the rest of the execution of program

#include "../include/utils.h"

/*
Desc: Read file from user like urls.txt. With such file,
read each line and return an array of strings.

Input:
    const char* filename: Name of file to be read
Ret: Returns a struct url_array that contain ptr to array of strings and its size
*/
url_array read_urls_file(const char* filename) {
    // Attempt to open file in read mode
    FILE* file = fopen(filename, "r");

    // If some error occured, inform user and return NULL
    if (!file) {
        perror("Error opening file");
        url_array null = {NULL, 0};
        return null;
    }
    
    //Init a dynamic buffer of urls to store all the urls
    int url_arr_size = 0;
    int url_arr_capacity = 1;
    char** url_arr = (char**)malloc(sizeof(char*) * url_arr_capacity);
    
    while (1) {
        //Read a line from file
        char* url = readline_from_file(file);
        
        //If url is NULL, break. Last line has been found
        if (!url)
            break;
        
        //Ensure capacity and sizes are good
        //Add one to url_size
        ++url_arr_size;

        //If capacity is less than url_size, double size of capacity
        if (url_arr_capacity < url_arr_size) {
            url_arr = (char**)realloc(url_arr, url_arr_capacity * sizeof(char*) * 2);

            //Double capacity var
            url_arr_capacity *= 2;
        }
        
        //Add url to url array
        url_arr[url_arr_size - 1] = url;
    }
   
    // Create url_array struct to return
    url_array ret_url_array = {url_arr, url_arr_size};

    //Close file;
    fclose(file);
    return ret_url_array;
}

/*
Desc: Takes in a file object and reads until it reaches EOF or newline
Then it creates a char* in the heap and returns that ptr

Input:
    file: File ptr to be read from
Ret: Returns the string read from the file's one line
*/
char* readline_from_file(FILE* file) {
    // If file ptr is at EOF, return NULL
    if (feof(file)) {
        return NULL;
    }

    //Init all values to start reading and creating strings from file
    char c = 'a';
    
    //Init a dynamic buffer of chars to store url
    int url_size = 0;
    int url_capacity = 1;
    char* url = (char*)malloc(sizeof(char) * url_capacity);

    while (1) {
        // Read a char from file
        c = getc(file);

        //Ensure capacity and sizes are good
        //Add one to url_size
        ++url_size;

        //If capacity is less than url_size, double size of capacity
        if (url_capacity < url_size) {
            url = (char*)realloc(url, url_capacity * sizeof(char) * 2);
            //Double url_capacity var
            url_capacity *= 2;
        }
    
        // If char is newline make last char NULL and break from loop
        if (c == '\n') {
            url[url_size - 1] = '\0';
            break;
        }
        //Else if char is EOF, free the url memory, and break from loop
        else if (c == EOF) {
            free(url);
            url = NULL;
            break;
        }
        // Else let current buffer ptr equal the read valid char
        else {
            url[url_size - 1] = c;
        } 
    }

    return url;
}
