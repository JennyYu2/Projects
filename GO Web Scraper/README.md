# Go Webscraper

<div align="center">  
  <img src="go%20go%20go/images/beaver.png" alt="go beaver" width="300" height="300">
</div>

### Authors
- Hamad Ayaz
- Cj Chen
- **Jenny Yu**
- May Niu

*November 27, 2024*

---

## Description

This is a webscraper written in Go that finds relevant code snippets based on user input.

It can scrape from three websites:
- stackoverflow
- geeksforgeeks
- w3 schools

In three different languages:
- Java
- Python
- C

---

## Instructions to run

0. Prerequisites
- Clone this repository or download all the files

1. Navigate to the project folder and type:
```
go run scraper.go
```

2. Will prompt for function name (optional), enter a function name you want to look up

Example:
```
bubble sort
```

3. Will prompt for description, enter a brief description of what you want to look up

Example:
```
bubble sort function
```
4. Will prompt for language (optional), enter the language you want to find code for

Example:
```
java
```

5. Will ask which website you want to search on, enter the number corresponding to website(s) you want to search on
- 1 for java
- 2 for python
- 3 for C

6. Relevant code snippets will be printed to the conole

--

## Features

- Use of Goroutines for concurrent searching
- 

---

## Included files 

- chromedp.go
    - Searches through google and extracts code from urls
- main.go
    - The command line interface which uses goroutines to search urls
- test.go
    - The command line interface without goroutines  


