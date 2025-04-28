# Makefile to build program
all: build

build:
	@echo "Building"
	@echo "Header files in include"
	@echo "Implemention/Code in src"
	gcc -std=c11 -pedantic -pthread -lcurl -o scraper scraper.c ./src/*.c -lm

run:
	./scraper

clean:
	@echo "Cleaning and removing files"
	rm scraper
	rm output/**
