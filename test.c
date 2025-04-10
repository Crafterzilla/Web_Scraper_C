#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/multithread.h"

#define MAX_URLS 16
#define MAX_LINE 256
#define WORD_COUNT 3

int main() {
    // Step 1: Read URLs from file
    FILE* url_file = fopen("example_urls.txt", "r");
    if (!url_file) {
        perror("Failed to open URL file");
        return 1;
    }

    const char* urls[MAX_URLS];
    char* lines[MAX_URLS];
    int count = 0;

    char buffer[MAX_LINE];
    while (fgets(buffer, MAX_LINE, url_file) && count < MAX_URLS) {
        lines[count] = strdup(buffer);
        // Remove trailing newline
        lines[count][strcspn(lines[count], "\n")] = 0;
        urls[count] = lines[count];
        count++;
    }
    fclose(url_file);

    // Step 2: Scrape websites
    if (multifetch_websites(urls, count) != NO_ERROR) {
        fprintf(stderr, "Error scraping websites\n");
        return 1;
    }

    // Step 3: Open scraped files
    FILE* files[MAX_URLS];
    for (int i = 0; i < count; ++i) {
        char filename[64];
        snprintf(filename, 64, "output/site_%d.html", i);
        files[i] = fopen(filename, "r");
        if (!files[i]) {
            perror("Failed to open output file");
            return 1;
        }
    }

    // Step 4: Define words to count
    const char* words[WORD_COUNT] = {"cat", "dog", "word"};

    // Step 5: Count words
    multicount(files, count, words, WORD_COUNT);

    // Step 6: Free lines
    for (int i = 0; i < count; ++i) {
        free(lines[i]);
    }

    return 0;
}

//to run: gcc -o test test.c src/multithread.c src/web_scraper.c src/count.c -lpthread -lcurl