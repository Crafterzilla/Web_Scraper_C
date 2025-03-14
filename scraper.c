#include "include/web_scraper.h"
#include "include/multithread.h"
#include "include/count.h"
#include "include/utils.h"

int main(const int argc, const char** argv) {
    // Osmar will put all your code together here

    url_array arr = read_urls_file("example_urls.txt");



    // Free memory for url_array
    for (int i = 0; i < arr.size; i++) {
        printf("String: %s\n", arr.urls[i]);
        free(arr.urls[i]);
        arr.urls[i] = NULL;
    }
    free(arr.urls);
}
