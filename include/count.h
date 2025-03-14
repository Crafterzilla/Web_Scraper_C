#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Add includes go here

/*
Desc: Takes in an html file and counts the number of time
the word occurs.

Input:
    html_data: Html file to be read from
    word: Special word to count
Ret: Returns the number of times word occured
*/
int count_reoccurance(FILE* html_data, const char* word);

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

*/
int* count_all_reoccurances(FILE* html_data, const char** words, const int size);

#endif
