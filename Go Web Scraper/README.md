# Go Webscraper

<div align="center">  
  <img src="go%20go%20go/images/beaver.png" alt="go beaver" width="300" height="300">
</div>

## Authors:
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

It scrapes from four websites:
- Stack Overflow 
- GeeksforGeeks  
- W3Schools
- Tutorialspoint

And supports searching in four programming languages:
- **Java**
- **Python**
- **C**
- **C++**

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
     - 4 --> Tutorialspoint
     - 5 --> All four

3. Relevant code snippets will be printed to the console!

---

## Example Run

#### Searching for `Floyd Warshall Algorithm`

Run the scrapper using `go run scraper.go` then enter the algorithm name or a brief description of the function when prompted. <br>
We’ll search in Python (enter `2` when prompted) and select all four websites (enter `5`).

<img src="go%20go%20go/images/search1.jpeg" alt="first image of example run" width="450" height="363">

The scraper will then search the chosen sites **concurrently** using **Goroutines**. <br>
It also displays the URLs where it found code snippets.

<img src="go%20go%20go/images/search2.jpeg" alt="second image of example run" width="800" height="356">

Next, it prints the relevant code snippets found. <br>
Below we can see code for the Floyd Warshall Algorithm in **Python** from **GeeksforGeeks**.

<img src="go%20go%20go/images/search3.jpeg" alt="third image of example run" width="400" height="419">

If no code snippets are found on a site, an error message is displayed. <br>
If no code is available in the specified language, the scraper may show snippets in another language.

<img src="go%20go%20go/images/search4.jpeg" alt="fourth image of example run" width="500" height="364">

When the search is complete, the program will display a “SEARCH COMPLETE” message.

<img src="go%20go%20go/images/search5.jpeg" alt="fifth image of example run" width="450" height="322">

---

## Features
[Back to top](#table-of-contents)

- Concurrent searching using Goroutines
- Scrapes multiple coding resources
- Works with Java, Python, C and C++
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

