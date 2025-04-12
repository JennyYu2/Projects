Go webscraper
------------

Authors: Hamad Ayaz, Cj Chen, Jenny Yu, May Niu

Date: 11/27/2024

## Description
This is a webscrapper that can find code snippets relating to what the user inputs from three websites: stackoverflow, geeksforgeeks and w3 schools.

## Instructions to run
Type: go run scraper.go <br>
will prompt for function name (optional), enter a function name you want to look up <br>
will prompt for description, enter a brief description of what you want to look up <br>
will prompt for language (optional), enter the language you want to find code for <br>
will ask which website you want to search on, enter the number corresponding to website(s) you want to search on <br>
relevant code snippets will be printed to the conole

## Included files 

* chromedp.go  - Searches through google and extracts code from urls
* main.go      - The command line interface which uses goroutines to search urls
* test.go      - The command line interface without goroutines  


