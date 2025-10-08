/*
Project Name: chromedp.go
Description: This program holds two funcctions that operate as the web scraper:
	SearchGoogle() and ExtractCodeSnippets()

@author Hamad Ayaz, Jenny Yu, CJ Chen, May Niu
@since 2024-11-27

*/

package scraper

import (
	"context"
	"fmt"
	"time"

	"github.com/chromedp/chromedp"
)

// SearchGoogle performs a Google search and extracts the first result link.
func SearchGoogle(query string) (string, error) {
	ctx, cancel := chromedp.NewContext(context.Background())
	defer cancel()

	var firstLink string
	err := chromedp.Run(ctx,
		// Pulls up Google search box
		chromedp.Navigate("https://www.google.com"),
		chromedp.WaitVisible(`input[name="q"]`, chromedp.ByQuery),
		// Enters the query into Google
		chromedp.SendKeys(`input[name="q"]`, query+"\n", chromedp.ByQuery),
		chromedp.Sleep(2*time.Second),
		// Retrieves the Url from the search
		chromedp.AttributeValue(`#search a`, "href", &firstLink, nil, chromedp.ByQuery),
	)
	if err != nil {
		return "", fmt.Errorf("failed to perform search: %w", err)
	}
	return firstLink, nil
}

// ExtractCodeSnippets navigates to a URL and extracts code snippets.
func ExtractCodeSnippets(url string) ([]string, error) {
	ctx, cancel := chromedp.NewContext(context.Background())
	defer cancel()

	var snippets []string
	err := chromedp.Run(ctx,
		// Fetches the website through the Url
		chromedp.Navigate(url),
		chromedp.WaitVisible(`pre`, chromedp.ByQuery),
		// Inspects the Url's Javascript looking for code blocks (<pre>)
		chromedp.Evaluate(`Array.from(document.querySelectorAll('pre')).map(el => el.innerText)`, &snippets),
	)
	if err != nil {
		return nil, fmt.Errorf("failed to extract code snippets: %w", err)
	}
	return snippets, nil
}
