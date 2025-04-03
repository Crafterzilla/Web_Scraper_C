/*
Purpose: This file implements functions to count the occurrences of specific words within HTML files.
    It provides two main functionalities:
         1.) Counting the number of times a single word appears in an HTML file.
         2.) Counting the occurrences of multiple words in an HTML file and returning an array of counts.
    These functions are essential for analyzing the frequency of keywords in the scraped HTML data,
         which is a core part of the web scraping and word analysis pipeline.

*/

#include "../include/count.h"

/*
Desc: Takes in an html file and counts the number of time
the word occurs.

Input:
    html_data: Html file to be read from
    word: Special word to count
Ret: Returns the number of times word occured
*/
int count_reoccurance(FILE* html_data, const char* word) {
    // Check if either the file pointer or the word is NULL
    if (html_data == NULL || word == NULL) {
        return 0; // Return 0 as no occurrences can be counted
    }

    // Reset the file pointer to the beginning of the file to ensure all data is read
    rewind(html_data);

    // Initialize a counter to track the occurrences of the word
    int count = 0;
    // Buffer to store each line read from the file
    char buffer[1024];
    // Length of the word to search for
    size_t word_len = strlen(word);

    // Convert the search word to lowercase for case-insensitive matching
    char lowercase_word[word_len + 1]; // Allocate space for the lowercase word (+1 for null terminator)
    for (size_t i = 0; i < word_len; i++) {
        lowercase_word[i] = tolower(word[i]); // Convert each character to lowercase
    }
    lowercase_word[word_len] = '\0'; // Null-terminate the string

    // Read the HTML file line by line
    while (fgets(buffer, sizeof(buffer), html_data)) {
        // Convert the current line to lowercase for case-insensitive comparison
        char lowercase_buffer[sizeof(buffer)];
        for (size_t i = 0; i < strlen(buffer); i++) {
            lowercase_buffer[i] = tolower(buffer[i]); // Convert each character to lowercase
        }
        lowercase_buffer[strlen(buffer)] = '\0'; // Null-terminate the buffer

        // Search for the lowercase word in the lowercase buffer
        char* pos = lowercase_buffer; // Pointer to the current position in the line
        while ((pos = strstr(pos, lowercase_word)) != NULL) { // Find the next occurrence of the word

            //Keeping those code commented in case word counting is more strict

            // Check if the match is a whole word
            /* if ((pos == lowercase_buffer || !isalnum(*(pos - 1))) && // Ensure the character before is not alphanumeric */
            /*     (!isalnum(*(pos + word_len)) || *(pos + word_len) == '\0')) { // Ensure the character after is not alphanumeric */
            /*     count++; // Increment the occurrence count */
            /* } */
            
            // Counts plus one whenever strstr finds a "needle" in "haystack" (substring in string)
            count++;
            pos += word_len; // Move the pointer forward to continue searching
        }
    }

    // Reset the file pointer for subsequent reads
    rewind(html_data);

    // Return the total count of occurrences
    return count;
}


/*
Desc: Takes in an html file and counts all the words'
reoccurance. The array of strings will be in sorted 
order from a to z. It will give back the reoccurances
as an int array stored on the heap.

Ex: 
    Input: ["cat", "dog", "lizard"]

    Algorithm finds 5 cats, 2 dogs, and 0 lizards

    Return: [5, 2, 0]

Input:
    html_data: Html file to be read from
    words: Sorted Array of words that will be counted
    size: size of array words
Ret: Returns the an array of the number of times those words occured
in the order they came in.

TODO: STILL NEED TO DEBUG!

*/
int* count_all_reoccurances(FILE* html_data, char** words, const int size) {
    // Check if the input parameters are invalid
    if (html_data == NULL || words == NULL || size <= 0) {
        return NULL; // Return NULL if the file, words array, or size is invalid
    }

    // Allocate memory for the result array to store counts of each word
    int* counts = (int*)malloc(size * sizeof(int));
    if (counts == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Loop through each word in the `words` array
    for (int i = 0; i < size; i++) {
        // Count the occurrences of the current word using count_reoccurance
        counts[i] = count_reoccurance(html_data, words[i]);
    }

    // Return the array containing the counts
    return counts;
}
