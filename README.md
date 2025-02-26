# Web_Scrapper

Multithreaded Web Scraper made in c

## How to build

To compile the program use the following command

> make build

If make not installed then you can use gcc using the following command

> gcc -std=c11 -pedantic -o web_scraper web_scraper.c ./src/*.c -lm

## How to run

To run, use the command below:

> ./web_scraper

Or if using a file with a list of websites instead:

> ./web_scraper INSERT_FILE_HERE
