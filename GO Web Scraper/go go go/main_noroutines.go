/*
Authors: Jenny Yu, Hamad Ayaz, CJ Chen, May Niu
File: scraper.go
Description: Takes user input and looks up code from websites. Scrapes the code from the site(s) and prints the code
snippets onto the console.
Instructions: 
> go run scraper.go
will prompt for function name (optional), enter a function name you want to look up
will prompt for description, enter a brief description of what you want to look up
will prompt for language (optional), enter the language you want to find code for
will ask which website you want to search on, enter the number corresponding to website(s) you want to search on
relevant code snippets will be printed to the conole
*/

package main

import (
	"bufio"
	"context"
	"fmt"
	"os"
	"strings"
	"time"

	"github.com/chromedp/chromedp"
)

// Main ----------------------------------------------------------------------------------------------------------------------------------------------

/*
The main function runs the code
*/
func main() {
	runScraperNoGoRoutines()
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

// Run Scraper ---------------------------------------------------------------------------------------------------------------------------------------

func runScraperNoGoRoutines() {
	// Getting user input for their query
	functionName, description, language, websiteChoice := getUserQuery()

	// Get user input for which sites they want to search
	_, sites, inputIsInvalid := processWebsiteChoice(websiteChoice)
	if inputIsInvalid {
		return
	}

	startTime := time.Now()
	// If user chooses to search multiple sites, use the goroutine
	for _, site := range sites {
		if runQuery(functionName, description, language, site) == 1 {
			fmt.Println("Time to process query without Go routines: ", time.Since(startTime))
			return
		}
	}
	fmt.Println("Time to process query without Go routines: ", time.Since(startTime))
}

/*
This function takes user input for name of a function they want to look up, description of the function,
language of the function and which site they want to search on.
*/
func getUserQuery() (string, string, string, string) {
	reader := bufio.NewReader(os.Stdin)

	// Get user input for function name
	fmt.Print("Enter the function name (optional): ")
	functionName, _ := reader.ReadString('\n')
	functionName = strings.TrimSpace(functionName)

	// Get user input for function description
	fmt.Print("Enter a brief description of the function: ")
	description, _ := reader.ReadString('\n')
	description = strings.TrimSpace(description)

	// Get user input for language
	fmt.Print("Enter the programming language (optional): ")
	language, _ := reader.ReadString('\n')
	language = strings.TrimSpace(language)

	// Get user input for which site(s) to search
	fmt.Println("Choose the website(s) to search (1: StackOverflow, 2: GeeksforGeeks, 3: W3Schools, 4: All 3 sites):")
	websiteChoice, _ := reader.ReadString('\n')
	websiteChoice = strings.TrimSpace(websiteChoice)

	return functionName, description, language, websiteChoice
}

/*
This function adds the websites that the user wants to search into an array based on the choice the user picked.
*/
func processWebsiteChoice(websiteChoice string) (int, []string, bool) {
	goR := 0 // Goroutine only for option 4 (multiple sites)

	var sites []string // Array of websites
	switch websiteChoice {
	case "1":
		sites = []string{"stackoverflow.com"}
	case "2":
		sites = []string{"geeksforgeeks.org"}
	case "3":
		sites = []string{"w3schools.com"}
	case "4":
		sites = []string{"stackoverflow.com", "geeksforgeeks.org", "w3schools.com"}
		goR = 1
	default:
		fmt.Println("Invalid choice. Exiting.")
		return 0, nil, true
	}
	return goR, sites, false
}

/*
This function generates the query to search up based on the user inputs and it then searches google for links to
site(s) that the user wants to see. Then it scrapes the code snippets off the sites and prints the relevant snippets
to the console.
*/
func runQuery(functionName, description, language, site string) int {
	// Put the user inputs together to create a query string
	query := generateQuery(functionName, description, language, site)
	fmt.Println("Searching for:", query)

	// Get the website(s) to search for
	link, err := searchWeb(query, site)
	if err != nil {
		fmt.Printf("Error during search on %s: %v\n", site, err)
		return 1
	}
	fmt.Println("First link found on", site, ":", link) // print the link

	// Scrape the code snippets off of the sites
	snippets, err := extractCodeSnippets(link)
	if err != nil {
		fmt.Printf("Error extracting code snippets from %s: %v\n", site, err)
		return 1
	}

	// User input for name and description
	keywords := strings.Fields(functionName + " " + description)
	// Get the relevant snippets
	snippets = filterRelevantSnippets(snippets, keywords, language)

	// No snippets found
	if len(snippets) == 0 {
		fmt.Println("No relevant code snippets found on", site)
		return 1
	}

	// Print the relevant code snippets in the array
	fmt.Println("\nRelevant Code Snippets Found on", site, ":")
	for i, snippet := range snippets {
		// Get the programming language of the code snippet
		detectedLanguage := detectLanguage(snippet)
		fmt.Printf("\nSnippet %d (%s):\n%s\n", i+1, detectedLanguage, snippet)
	}
	return 0
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

// Scraper Functions ---------------------------------------------------------------------------------------------------------------------------------

/*
This function will string together the user's input for what they want to search for to generate a query to look up
*/
func generateQuery(functionName, description, language, site string) string {
	// Query to look up
	query := fmt.Sprintf("%s function %s", functionName, description)
	if language != "" {
		query = fmt.Sprintf("%s %s example site:%s", query, language, site)
	} else {
		query = fmt.Sprintf("%s example site:%s", query, site)
	}
	return query
}

/*
This function goes through the array of website(s) that the user wants to search on and search those sites and
save the code snippets.
*/
func searchWeb(query, site string) (string, error) {
	// Use chromedp library
	ctx, cancel := chromedp.NewContext(context.Background())
	defer cancel()

	var firstLink string // Link to visit

	fmt.Printf("Searching %s...\n", site)
	err := chromedp.Run(ctx,
		chromedp.Navigate("https://www.google.com"),                                                       // Navigate to google
		chromedp.WaitVisible(`textarea[aria-label="Search"]`, chromedp.ByQuery),                           // Wait for google to load
		chromedp.SendKeys(`textarea[aria-label="Search"]`, query+"\n", chromedp.ByQuery),                  // Search on google
		chromedp.Sleep(2*time.Second),                                                                     // Wait for results to load
		chromedp.AttributeValue(`#search a[href*="`+site+`"]`, "href", &firstLink, nil, chromedp.ByQuery), // Click the first link
	)
	// Error searching
	if err != nil {
		return "", fmt.Errorf("failed to perform search: %w", err)
	}
	if firstLink == "" {
		return "", fmt.Errorf("no link found in search results")
	}
	return firstLink, nil
}

/*
This function gets the code snippets off the links that are found when searching for the user's query
*/
func extractCodeSnippets(url string) ([]string, error) {
	// Use chromedp import
	ctx, cancel := chromedp.NewContext(context.Background())
	defer cancel()

	var snippets []string // Save snippets in an array

	fmt.Printf("Navigating to %s...\n", url)
	err := chromedp.Run(ctx,
		chromedp.Navigate(url), // Click on the link
		chromedp.WaitVisible(`pre, code, .code-container *`, chromedp.ByQuery), // Scrape from the specified containers in the website's html
		chromedp.Evaluate(`
			Array.from(document.querySelectorAll('pre, code, .code-container *'))
				.filter(el => el.innerText.length > 50)
				.map(el => el.innerText)
		`, &snippets), // Get all the elements from the specified containers and filter the content
	)
	// Error searching
	if err != nil {
		return nil, fmt.Errorf("failed to extract code snippets: %w", err)
	}

	return snippets, nil
}

/*
This function detects a coding lanuage and returns the name of the language
*/
func detectLanguage(snippet string) string {
	lowerSnippet := strings.ToLower(snippet) // code snippet

	// Identifies the language by searching for language specific markers
	switch {
	case strings.Contains(lowerSnippet, "public static void main") ||
		strings.Contains(lowerSnippet, "System.out.print ") ||
		strings.Contains(lowerSnippet, "void") ||
		strings.Contains(lowerSnippet, "int[]"):
		return "Java"
	case strings.Contains(lowerSnippet, "def ") ||
		strings.Contains(lowerSnippet, "self") ||
		strings.Contains(lowerSnippet, "elif") ||
		strings.Contains(lowerSnippet, "print("):
		return "Python"
	case strings.Contains(lowerSnippet, "#include") ||
		strings.Contains(lowerSnippet, "int main") ||
		strings.Contains(lowerSnippet, "printf("):
		return "C/C++"
	default:
		return "Unknown"
	}
}

/*
This function filters the code snippets based on the language that the user specified.
*/
func filterRelevantSnippets(snippets []string, keywords []string, language string) []string {
	uniqueSnippets := make(map[string]bool) // Use a map to get unique snippets
	var filtered []string                   // Array of filtered code snippets

	// Define language-specific markers
	languageMarkers := map[string][]string{
		"Python": {"def ", "elif", "print(", "lambda "},
		"Java":   {"import java", "System.out.print", "public ", "static "},
		"C/C++":  {"#include", "int main", "printf("},
	}

	// Go through array of code snippets found
	for _, snippet := range snippets {
		// Skip short or duplicate snippets
		if len(snippet) < 50 || uniqueSnippets[snippet] {
			continue
		}
		uniqueSnippets[snippet] = true

		// Check for language-specific markers
		markers, ok := languageMarkers[language]
		if ok {
			hasMarker := false
			// Checking for language
			for _, marker := range markers {
				if strings.Contains(snippet, marker) {
					hasMarker = true
					break
				}
			}
			if !hasMarker {
				continue
			}
		}

		// Check relevance to keywords
		isRelevant := false
		for _, keyword := range keywords {
			if strings.Contains(strings.ToLower(snippet), strings.ToLower(keyword)) {
				isRelevant = true
				break
			}
		}
		// If the snippet has the relevant keywords, add it to the array of relevant snippets
		if isRelevant {
			filtered = append(filtered, snippet)
		}
	}
	return filtered
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
