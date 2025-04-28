#include "include/multithread.h"
#include "include/utils.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>

/*
 * Function: remove_all
 * ----------------------------
 * This will remove all files in output directory. It ignores "." and ".." directories and
 * deletes everything else by looping though all the filenames until NULL is eached. 
 *
 * Return -1 if some failure occurs in this process and 0 if it succeds. 
 */
int remove_all(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    // If file open failed, return -1
    if (!dir) {
        perror("opendir failed");
        return -1;
    }
    
    // Read all contents of output and delete each file/file
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        // Create fullpath which is output/filename
        char fullpath[4096];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        
        // Delete the file
        if (remove(fullpath) == -1) {
            perror("rm file failed");
            return -1;
        }
    }

    closedir(dir);
    return 0;
}

/*
 * Function: init_directories
 * ----------------------------
 * This will create the output directory. It will also delete all contents within that directory if it
 * does exist. This is mainly due to have libcurl output files have to be appended to the end of the file
 * rather than written to since it gathers data in chucks. 
 *
 * Return -1 if some failure occurs in this process and 0 if it succeds. 
 */
int init_directories() {
    // Output Path
    const char* path = "output";

    // Make the directory for output. If it exists, delete everything inside that directory
    if (mkdir(path, 0755) == -1) {
        if (errno != EEXIST) {
            // Directory does not exists and creating it failed, return -1
            // Some other error
            perror("Mkdir output failed");
            return -1;
        }
        else {
            if (remove_all(path) == -1) {
                return -1;
            };
        }
    }
    return 0;
}

int main(const int argc, const char** argv) {
    puts("Ivin, Ken, Juli, Osmar Epic Scraper 5000 v1");
    puts("HTML files are places in ./output/");
    puts("Individual count files are places in ./output/\n");
    
    // If there are no three args, then exit program!
    if (argc != 3) {
        fprintf(stderr, "Missing args!!!\n");
        fprintf(stderr, "Run with ./scraper url_to_fetch.file word_to_be_counted.file\n");
        return 1;
    }
    
    // Step 0: Create output file or erase everything in it
    // Create the output directory or remove all files is it already exists
    if (init_directories() == -1) {
        perror("Failed to init output directory!");
    }

    //Step 1: Read urls from file
    str_array url_arr = read_str_file(argv[1]);
    
    // Step 2: Scrape websites using multithreading
    if (multifetch_websites(url_arr.strings, url_arr.size) != NO_ERROR) {
        fprintf(stderr, "Error scraping websites\n");
        return 1;
    }
    
    // Extra step: Print URL ID in stdout and to a file
    FILE* id_file = fopen("./output/id.txt", "w");
    for (int i = 0; i < url_arr.size; i++) {
        fprintf(id_file, "[%d] ID for %s\n", i, url_arr.strings[i]);
        printf("[%d] ID for %s\n", i, url_arr.strings[i]);
    }
    fclose(id_file);
    
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
        // If the file ptr exists
        if (files[i])
            fclose(files[i]);
    }

    free(files);
    free_str_array(url_arr);
    free_str_array(words_arr);
}
