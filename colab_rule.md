# Collaberation Rules

Here are some of the Rules, Plan, and Goal for the program

## Plan
- [x] Create Foundation for Coding
- [ ] Fetch HTML Data and Store Into File
- [ ] Parse and Count Reoccurances For Each File
- [ ] Multithread HTML Fetching
- [ ] Terminal Front-End for Program
    - [ ] Run Program and program request user to input website
    - [ ] User runs ./scraper file.txt and it scrapes those websites
- [ ] Ensure Programs Runs, Handles Errors, and Cannot be crashed by Invalid Input


## Task Division

### Fetching HTML Data And Store into Output Files

Create a basic scraper that fetches HTML Data. Then, place those files into 
./output for the user to read. Ensure filename parameter to easily pick a filename
name.

```
Function Declaration in "./include/web_scaper.h"
Function Implementation in "./src/web_scaper.c"

Branch: web_scraper
```

### Count Reoccurances For Each File

Given an array of strings, count the number of times each string occurred.

```
Function Declaration in "./include/count.h"
Function Implementation in "./src/count.c"

Branch: count
```

### Multithreading Operations

Take the web_scraper and multithread it to run in parallel.
Take the counting of reoccurances and multithread that too.

```
Function Declaration in "./include/multithread.h"
Function Implementation in "./src/multithread.c"

Branch: multithread
```

### Reading User Input and Error Handling

Create function to read user input and make it usable in the program.

```
Some key functions needed:
    1.) Read Url File and create a const char**
    2.) Read Special Words and craete a const char** and int*
    3.) Read output files and create an array of FILE**

Potential Function Declaration in "./include/util.h"
Potential Function Implementation in "./src/util.c"

Branch: io
```

## GOAL

The goal is to create a program that will scrape any number of n websites
and save the HTML into seperate files for each website. In addition it will
count the reoccurances of m words in those each file, and then overall in all files.


### Example 1

User runs:
> make build<br>
> ./scraper file.txt

Program will ask which words to look for using stdin:

```
Input words: "User inputs here"
```

Program will read each of the lines in files.txt with each line containing a website

```
file.txt:
https://google.com
https://example.com
...
```

Program will then scrape the data from each website and then in return in stdout

```
Word1 Reoccurance: x times
Word2 Reoccurances: y times
...
Wordn Reoccurances: m times
```

Program in seperate files in a new file in output/ and create

```
// In ./output/

google.html
example.html
```

### Example 2

Same above, however will instead use stdin to get the website names.

```
Input Website 1: "Input Website"
Input Website 2: "Input Website"
...
Input Wenite n: "Input Website"
```

## Documentations

So everyone can understand all code that is written by each other, each function
much be very well defined and well commented. For example

```
/*
Desc: This is a function that prints out a string
Args:
    str: String to be printed out

Ret: Returns int for number of chars printed

*/
int print_stuff(const char* str) {
    return printf("String: %s\n", str);
}
```
In addition COMMENT AS MUCH AS POSSIBLE!!! We should be able to read each others
code line by line like if it were English without having to even read the code itself.


## Coding Rules

Please split function into multiple functions. Refrain from creating massive
huge functions that do everything. This will explainations difficult and confusing.
The more split up the function the better.
