/* 
  Author: Buddy

  File: aboutUs.js
  
  Description: aboutIs.js file from the AboutUs subdirectory.  
  
  Provides the JavaScript for the card flipping effect on the About Us Page
  This is the .css file referenced in the AboutUs.html file.
*/


const sections = document.querySelectorAll('.section');

// Click Listener Event
sections.forEach(function (section) {
    section.addEventListener('click', toggleActiveClass);
});


// Click to reveal 
function myClickHandler(event) {
    event.target.classList.add("revealed"); 
    event.target.style.cursor = "default"; 
    event.target.removeEventListener("click", myClickHandler); 

}

// Event handlers
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
    const footerRect = footer.getBoundingClientRect();

    // Show button when the footer is nearing the viewport
    if (footerRect.top < window.innerHeight && footerRect.bottom > 0) {
        button.style.display = "block"; 
    } else {
        button.style.display = "none"; 
    }
});


document.querySelectorAll('.card').forEach(card => {
    card.addEventListener('click', () => {
        card.classList.toggle('flipped');
    });
});