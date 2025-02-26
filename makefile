# Makefile to build program
all: build

build:
	@echo "Building"
	@echo "Header files in include"
	@echo "Implemention/Code in src"
	gcc -std=c11 -pedantic -o web_scraper web_scraper.c ./src/*.c -lm

run:
	./web_scraper

clean:
	@echo "Cleaning and removing files"
	rm web_scraper
	rm output/**
	rmdir output
