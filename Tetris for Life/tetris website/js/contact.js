// Smooth scroll to top 
document.getElementById("backToTop").addEventListener("click", function (event) {
    event.preventDefault();
    window.scrollTo({
        top: 0, // Scroll to the top
        behavior: "smooth"
    });
});


// Show/hide the back to top button based on scroll position (disappear when user scrolls back up)
window.addEventListener("scroll", function () {
    const button = document.getElementById("backToTop");
    const footer = document.querySelector("footer");
    const footerRect = footer.getBoundingClientRect(); // Get footer position

    // Show button when the footer is nearing the viewport
    if (footerRect.top < window.innerHeight && footerRect.bottom > 0) {
        button.style.display = "block"; // Show button
    } else {
        button.style.display = "none"; // Hide button
    }
})