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
    const logo = document.querySelector(".logo");



    button.style.display = "block";
    if (window.scrollY > logo.offsetHeight) {
        button.style.display = "block"; // Show button
    } else {
        button.style.display = "none"; // Hide button
    }
})
