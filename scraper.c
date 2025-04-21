#include "include/multithread.h"
#include "include/utils.h"
#include <stdio.h>

int main(const int argc, const char** argv) {
    puts("Ivin, Ken, Juli, Osmar Epic Scraper 5000 v1");
    puts("HTML files are places in ./output/");
    puts("Individual count files are places in ./output/");

    if (argc != 3) {
        fprintf(stderr, "Missing args!!!\n");
        fprintf(stderr, "Run with ./scraper html.file word.file\n");
        return 1;
    }
    
    // Delete any files in ./output
    // This is mainly due to libcurl appending in chucks. 
    // Temporary will find better solution later
    system("rm ./output/**");


    //Step 1: Read urls from file
    str_array url_arr = read_str_file(argv[1]);
    
    // Step 2: Scrape websites using multithreading
    if (multifetch_websites(url_arr.strings, url_arr.size) != NO_ERROR) {
        fprintf(stderr, "Error scraping websites\n");
        return 1;
    }
    
    // Print URL ID in stdout
    for (int i = 0; i < url_arr.size; i++) {
        printf("[%d] ID for %s\n", i, url_arr.strings[i]);
    }
 
    // Step 3: Open scraped files    
    FILE** files = create_file_array(url_arr.size);

    // Step 4: Read words from file
    str_array words_arr = read_str_file(argv[2]);
    
    // Step 5: Multithreading couting of all files and each of the words
    if (multicount(files, url_arr, words_arr.strings, words_arr.size) != NO_ERROR) {
        fprintf(stderr, "Error counting html files\n");
        return 1;
    };


    // Step 6: FREE ALL MEMORY
    // Free files array
    for (int i = 0; i < url_arr.size; i++) {
        fclose(files[i]);
    }
    free(files);
    free_str_array(url_arr);
    free_str_array(words_arr);
}
