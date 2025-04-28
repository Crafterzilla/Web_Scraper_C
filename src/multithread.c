#include "../include/multithread.h"

/* 
Desc: Takes in list of URLS gathered from URL file. Then it calls web_scraper
multiple times for each different URL to put into a thread pool. The thread pool
then executes and runs the scraper on the websites at the same time. This will result
in multiple files in ./output for each URL. Should overall be very fast. Handles invalid
or URLs that are not functional with web_scraper.h implementation. Returns code for error
if anything occurs with the multithreading
*/

/*
 * Struct: scrape_job
 * ------------------
 * Used to pass URL and output filename into each scraping thread.
 */
typedef struct {
    char* url;         // The URL to scrape
    char* filename;    // The file to save the scraped HTML into
} scrape_job;

/*
 * Struct: count_job
 * -----------------
 * Used to pass all necessary info into each counting thread.
 */
typedef struct {
    char* url;
    FILE* file;              // File pointer to HTML file
    char** words;      // Array of words to count
    int word_count;          // Number of words in the array
    int* result_array;       // Shared result array (indexed by word index)
    int index;               // Index of the file (for debugging, if needed)
    char* filename;          // File to save the contents of site count
} count_job;


/*
 * Function: deal_with_failed_scrape
 * ----------------------------
 * This is a function to deal with the failed URL that the web_scraper could not fetch.
 * It writes FAILURE to html file, so that the counter function does not count it, and
 * it adds the url to a failure.list file to log the websites that failed
 *
 * char* filename: filename where the html was supposed to go. Now it will just have FAILURE
 *                 written to it
 * char* url: the url that failed
 */
void deal_with_failed_scrape(char* filename, char* url) {
    //Inform user of url that failed to be scraped
    fprintf(stderr, "Error scraping URL: %s\n", url);
   
    // DEAL WITH FAILURE!!! 
    // Step 1: Output URL to a failure file
    const char* failure_file = "output/failure.list";
    // Open file in append or write mode depending if file exists
    FILE* file = open_file(failure_file);

    //Write failed url to failure list
    fprintf(file, "%s\n", url);
    fclose(file);


    //Step 2: Output FAILURE to HTML file
    FILE* html_file = fopen(filename, "w");
    fprintf(html_file, "FAILURE\n");
    fclose(html_file);
}

/*
 * Function: scrape_thread_func
 * ----------------------------
 * This function is run by each scraper thread. It calls the web_scraper() function
 * to fetch a URL and save it to a file.
 *
 * arg: A scrape_job struct containing the URL and filename.
 */
void* scrape_thread_func(void* arg) {
    scrape_job* job = (scrape_job*)arg;

    // Call web_scraper to fetch and save the site contents
    if (web_scraper(job->filename, job->url) != CURLE_OK) {
        deal_with_failed_scrape(job->filename, job->url);
    }

    // Clean up heap-allocated filename and struct
    free(job->filename);
    free(job);

    return NULL;
}

/*
 * Function: count_thread_func
 * ---------------------------
 * This function is run by each counting thread. It opens a file and uses
 * count_all_reoccurances() to count how often each word appears.
 *
 * arg: A count_job struct containing the file, words, and result pointer.
 */
void* count_thread_func(void* arg) {
    count_job* job = (count_job*)arg;

    // Count occurrences of all words in this file
    int* counts = count_all_reoccurances(job->file, (char**)job->words, job->word_count);

    // Print individual count on a seperate file
    write_count_results_to_file(job->filename, job->url, job->words, counts, job->word_count);

    // If counting was successful, accumulate results
    if (counts != NULL) {
        for (int i = 0; i < job->word_count; ++i) {
            job->result_array[i] += counts[i];  // Accumulate into shared total
        }
        free(counts);
    }

    // Clean up the job struct
    free(job->filename);
    free(job);
    return NULL;
}

/*
 * Function: multifetch_websites
 * -----------------------------
 * Uses multithreading to fetch all websites in parallel.
 *
 * URL_list: Array of URLs to fetch
 * size: Number of URLs in the list
 *
 * returns: NO_ERROR on success, FAILURE on failure
 */

enum THREAD_CODE multifetch_websites(char** URL_list, const int size) {
    //Array of pthreads the system will keep track
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * size);

    for (int i = 0; i < size; ++i) {
        //Init memory for job struct and it's values
        scrape_job* job = (scrape_job*)malloc(sizeof(scrape_job));
        job->url = URL_list[i];

        // Construct output filename (e.g., "output/site_0.html")
        char* filename = (char*)malloc(sizeof(char) * 64);
        snprintf(filename, 64, "output/site_%d.html", i);
        job->filename = filename;

        // Create the scraping thread
        if (pthread_create(&threads[i], NULL, scrape_thread_func, job) != 0) {
            perror("Failed to create thread for scraper");
            return FAILURE;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < size; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    free(threads);
    return NO_ERROR;
}

/* 
Desc: Takes in an array of file objects that point to the files in ./output. It counts the number of times those
words occur in each file using count's implemenation and does it in paralell. Once it counts all the reoccurances
and puts them into reports (Done by count.h), it counts the total times the words occurred in ALL files.

 * Function: multicount
 * --------------------
 * Uses multithreading to count word occurrences in all HTML files.
 *
 * output_HTML_files: Array of file pointers to opened HTML files
 * file_array_size: Number of files
 * words: Array of words to search for
 * word_size: Number of words in the array
 *
 * returns: NO_ERROR on success, FAILURE on failure
 */

enum THREAD_CODE multicount(FILE** output_HTML_files, str_array urls, char** words, const int word_size) {
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * urls.size);

    // Shared result array initialized to 0 for each word
    int* result_array = (int*)calloc(word_size, sizeof(int));

    for (int i = 0; i < urls.size; ++i) {
        // If file is null, do not do a count for this file, nor make a count file for it
        if (!output_HTML_files[i]) {
            continue;
        }

        // Set up a job for this thread
        count_job* job = malloc(sizeof(count_job));
        job->file = output_HTML_files[i];
        job->url = urls.strings[i];
        job->words = words;
        job->word_count = word_size;
        job->result_array = result_array;
        job->index = i;

        // Construct output filename (e.g., "output/site_0.html")
        char* filename = (char*)malloc(sizeof(char) * 128);
        snprintf(filename, 128, "output/site_%d_count.txt", i);
        job->filename = filename;

        // Create the counting thread
        if (pthread_create(&threads[i], NULL, count_thread_func, job) != 0) {
            perror("Failed to create thread for counter");
            return FAILURE;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < urls.size; ++i) {
        if (output_HTML_files[i])
            pthread_join(threads[i], NULL);
    }

    // Output final aggregated results
    printf("\nTotal word occurrences in ALL FILES combined:\n");
    for (int i = 0; i < word_size; ++i) {
        printf("%s: %d\n", words[i], result_array[i]);
    }
    
    free(threads);
    free(result_array);
    return NO_ERROR;
}
