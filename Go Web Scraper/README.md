# Go Webscraper

<div align="center">  
  <img src="go%20go%20go/images/beaver.png" alt="go beaver" width="300" height="300">
</div>

### Authors:
- Hamad Ayaz
- Cj Chen
- **Jenny Yu**
- May Niu

*November 27, 2024*

---

## Table of Contents

- [Description](#description)
- [Instructions to Run](#instructions-to-run)
- [Example Run](#example-run)
- [Features](#features)
- [Included Files](#included-files)

---

## Description
[Back to top](#table-of-contents)

This is a **webscraper** written in Go that finds relevant code snippets based on user input.

It scrapes from three websites:
- Stack Overflow 
- GeeksforGeeks  
- W3Schools

And supports searching in three programming languages:
- **Java**
- **Python**
- **C**

---

## Instructions to Run
[Back to top](#table-of-contents)

0. Prerequisites
   - Must have Go installed
   - Clone this repository or download all the files


1. Navigate to the project folder and type:
```
go run scraper.go
```

2. Follow the prompts
   - **Function name (optional)**: enter a function you want to look up

     Example:
     ```
     bubble sort
     ```
     
   - **Description**: enter a brief description of what you want to look up

     Example:
     ```
     bubble sort function
     ```
   - **Language (optional)**: enter the language you want to find code for

     Example:
     ```
     java
     ```
     
   - **Website(s)**: enter the number corresponding to the website(s) you want to search on
     - 1 --> Stack Overflow
     - 2 --> GeeksforGeeks
     - 3 --> W3Schools
     - 4 --> All three

3. Relevant code snippets will be printed to the console!

---

## Example Run

#### Searching for `Floyd Warshall Algorithm`

Run the scrapper and type in Floyd Warshall to search

[insert image]



---

## Features
[Back to top](#table-of-contents)

- Concurrent searching using Goroutines
- Scrapes multiple coding resources
- Works with Java, Python, and C
- User-friendly command-line interface

---

## Included Files 
[Back to top](#table-of-contents)

- `chromedp.go`
    - Searches through google and extracts code from URLs
- `main.go`
    - The command line interface which uses goroutines to search URLs
- `test.go`
    - Simpler command line interface without goroutines  

