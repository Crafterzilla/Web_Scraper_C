// Purpose: This file mainly deals with I/O and getting input from the user
// so that data can be used for the rest of the execution of program

#include "../include/utils.h"
#include <string.h>

char* readline_from_file(FILE* file);

/*
Desc: Read file from user like urls.txt. With such file,
read each line and return an array of strings.

Input:
    const char* filename: Name of file to be read
Ret: Returns a struct url_array that contain ptr to array of strings and its size
*/
str_array read_str_file(const char* filename) {
    // Attempt to open file in read mode
    FILE* file = fopen(filename, "r");

    // If some error occured, inform user and return NULL
    if (!file) {
        perror("Error opening file");
        str_array null = {NULL, 0};
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
    str_array ret_url_array = {url_arr, url_arr_size};

    //Close file;
    fclose(file);
    return ret_url_array;
}


/*
 * Function: open_file
 * ----------------------------
 * If file exists, open in append mode.
 * If file does not exist, open in write mode.
 *
 * arg: A scrape_job struct containing the URL and filename.
 */
FILE *open_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        // File exists, close it and reopen in append mode
        fclose(file);
        file = fopen(filename, "a");
    } else {
        // File does not exist, open in write mode
        file = fopen(filename, "w");
    }

    return file;
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


/*
Desc: This function is to be used to write the amount of times a word has been counted
for an html file to a file.

Input:
    char* filename: Name of the file that the output will be written to
    char** words: array of words that were counted from the html file
    int* count: the number of times those words were counted from the html file
    const int size: number of words counted
*/
void write_count_results_to_file(char* filename, char* url, char** words, int* count, const int size) {
    // Open file for writing
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing counting results");
    }
        
    // Print url to output count file
    fprintf(file, "%s\n", url);

    // For each word print out the word and count onto the file
    for (int i = 0; i < size; i++) {
        fprintf(file, "%s: %d\n", words[i], count[i]);
    }
    
    // Close file
    fclose(file);
}


/*
Desc: Takes in a url_array and frees the memory back to the OS

Input:
    url_array* arr: Name of file to be read
*/
void free_str_array(str_array arr) {
    // Free memory for url_array
    for (int i = 0; i < arr.size; i++) {
        free(arr.strings[i]);
        arr.strings[i] = NULL;
    }
    free(arr.strings);
}


/*
Desc: Reads the html files that were created by web_scraper.c and then creates
an array of FILE* to then be used for multicount. It then reads the file to make sure
it's a valid HTML file. If it has FAILURE because the scraper failed to fetch a website,
then instead of storing a FILE* ptr, it will instead store NULL to inform counter not
to count this file.

Input:
    int size: Number of html files created
*/
FILE** create_file_array(int size) {
    // Allocate an array of file ptrs to be read from
    FILE** files = (FILE**)malloc(sizeof(FILE*) * size);
    for (int i = 0; i < size; i++) {
        // Get string for filename and open file
        char filename[64];
        snprintf(filename, 64, "output/site_%d.html", i);
        files[i] = fopen(filename, "r");

        // If file failed to open, return NULL
        if (!files[i]) {
            perror("Failed to open output file");
            return NULL;
        }
        
        /* !!!LAST CHECK!!!! */
        // Read one line from the file
        char* line = readline_from_file(files[i]);
        
        // If the file's only contents is FAILURE, it is not
        // a valid HTML file. Close the file and make the ptr NULL
        if (strcmp(line, "FAILURE") == 0) {
            fclose(files[i]);
            files[i] = NULL;
        } else {
            // Return FILE* ptr to the begining of the file buffer
            rewind(files[i]);
        }
        
        //Free memory
        free(line);
    }

    return files;
}
