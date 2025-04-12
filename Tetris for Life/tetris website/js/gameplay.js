// Select all elements with the class 'section'
const sections = document.querySelectorAll('.section');

// Function to handle click event on each section
function toggleActiveClass(event) {
    // Allow users to copy or highlight the text without triggering the click event
    if (window.getSelection().toString().length > 0) {
        return;
    }
    // Prevent section from closing when clicking on a link
    if (event.target.tagName.toLowerCase() === 'a') {
        return;
    }

    this.classList.toggle('active'); // Toggle active class if no text is selected
}

// click event listener for each section
sections.forEach(function (section) {
    section.addEventListener('click', toggleActiveClass);
});

// Mouseover effect
function myMouseoverHandler(event) {
    if (!event.target.classList.contains("revealed")) {
        event.target.style.backgroundColor = "#DDA0DD";
    }
}

function myMouseoutHandler(event) {
    event.target.style.backgroundColor = ""; // Reset background on mouse out
}

// Click to reveal answer and change color
function myClickHandler(event) {
    event.target.classList.add("revealed"); // Add the revealed class
    event.target.style.cursor = "default"; // Change cursor to default to indicate it's no longer clickable
    event.target.removeEventListener("click", myClickHandler); 

}

// Register the event handlers
let elements = document.getElementsByClassName("highlight");
for (let i = 0; i < elements.length; i++) {
    elements[i].addEventListener("mouseover", myMouseoverHandler);
    elements[i].addEventListener("mouseout", myMouseoutHandler);
    elements[i].addEventListener("click", myClickHandler);
}


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