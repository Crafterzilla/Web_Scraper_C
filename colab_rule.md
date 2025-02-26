# Collaberation Rules

Here are some of the Rules, Plan, and Goal for the program

## Plan
- [ ] Create Foundation for Coding
- [ ] Fetch HTML Data with Multithreading
- [ ] Terminal Front-End for Program
    - [ ] Run Program and program request user to input website
    - [ ] User runs ./web_scraper file.txt and it scrapes those websites
- [ ] Count Reoccurances for any n number of words requested by user
- [ ] Ensure Programs Runs and Cannot be crashed by incorrect input


## GOAL

The goal is to create a program that will scrape any number of n websites
and save the HTML into seperate files for each website.

### Example 1

User runs:
> make build
> ./web_scraper file.txt

Program will ask which words to look for using stdin:

Input words: "User inputs here"


Program will read each of the lines in files.txt with each line containing a website

file.txt:
https://google.com
https://example.com
...

Program will then scrape the data from each website and then in return in stdout

Word1 Reoccurance: x times
Word2 Reoccurances: y times


Program in seperate files in a new file /output
will create

google.html
example.html


### Example 2

Same above, however will instead use stdin to get the website names.

Input Website 1: "Input Website"
Input Website 2: "Input Website"
...
Input Wenite n: "Input Website"

## Documentations

So everyone can understand all code that is written by each other, each function
much be very well defined and well commented. For example

/*
Desc: This is a function that prints out a string
Args:
    str: String to be printed out

Ret: Returns int for number of chars printed

*/
int print_stuff(const char* str) {
    return printf("String: %s\n", str);
}


## Coding Rules

Please split function into multiple functions. Refrain from creating massive
huge functions that do everything. This will explainations difficult and confusing.
The more split up the function the better.

