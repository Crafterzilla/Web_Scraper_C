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
    // Check if the file pointer or word is NULL; if so, return 0 (no occurrences)
    if (html_data == NULL || word == NULL) {
        return 0;
    }

    // Reset the file pointer to the beginning of the file to ensure we read from the start
    rewind(html_data);

    // Initialize a counter to keep track of the number of occurrences of the word
    int count = 0;
    // Create a buffer to store each line read from the file
    char buffer[1024];
    // Get the length of the word to search for
    size_t word_len = strlen(word);

    // Convert the search word to lowercase for case-insensitive comparison
    char lowercase_word[word_len + 1];  // +1 for the null terminator
    for (size_t i = 0; i < word_len; i++) {
        lowercase_word[i] = tolower(word[i]);   // Convert each character to lowercase
    }
    lowercase_word[word_len] = '\0';  // Null-terminate the lowercase word

    // Print the lowercase word being searched for (for debugging purposes)
    // printf("Searching for the word: '%s'\n", lowercase_word);

    // Read the file line by line
    while (fgets(buffer, sizeof(buffer), html_data)) {

        //Print the current line being processed (for debugging purposes)
        //printf("Processing line: %s", buffer);

        // Convert the current line to lowercase for case-insensitive comparison
        char lowercase_buffer[sizeof(buffer)]; // Create a buffer for the lowercase line
        for (size_t i = 0; i < strlen(buffer); i++) {
            lowercase_buffer[i] = tolower(buffer[i]);   // Convert each character to lowercase
        }
        lowercase_buffer[strlen(buffer)] = '\0';  // Null-terminate the lowercase buffer

        // Search for the lowercase word in the lowercase buffer
        char* pos = lowercase_buffer;   // Start searching from the beginning of the buffer
        while ((pos = strstr(pos, lowercase_word)) != NULL) {
            // Check if the found word is a whole word
            if ((pos == lowercase_buffer || !isalnum(*(pos - 1))) &&    // Check the character before the word
                (!isalnum(*(pos + word_len)) || ispunct(*(pos + word_len)) || *(pos + word_len) == '\0')) { // Check the character after the word
                count++; // Increment the count if it's a whole word match

                // Print the updated count (for debugging)
                // printf("Valid occurrence. Count incremented to %d\n", count);
            }
            pos += word_len;  // Move the search position forward to avoid overlapping matches
        }
    }

    // Reset the file pointer for future reads
    rewind(html_data);  
    // Return the total count of word occurrences
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
int* count_all_reoccurances(FILE* html_data, const char** words, const int size) {
    //Check if the file pointer, words array, or size is invalid; if so, return NULL
    if (html_data == NULL || words == NULL || size <= 0) {
        return NULL;
    }

    //Allocate memory for an array to store the counts of each word
    int* counts = (int*)malloc(size * sizeof(int));
    //Check if memory allocation failed; if so, return NULL
    if (counts == NULL) {
        return NULL;
    }
    
    //Loop through each word in the array and count its occurrences in the file
    for (int i = 0; i < size; i++) {
        counts[i] = count_reoccurance(html_data, words[i]); //Store the count for current word
    }

    return counts;  //Return the array of counts
}
