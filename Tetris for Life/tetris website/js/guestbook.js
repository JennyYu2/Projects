// load guestbook entries from localStorage
document.addEventListener("DOMContentLoaded", loadEntries);

function loadEntries() {
    let entries = JSON.parse(localStorage.getItem("guestbookEntries")) || [];

    entries.forEach(function (entry) {
        // fetch table element
        let table = document.getElementById("guestbook-table");

        // create table elements to append
        let nameRow = document.createElement("tr");
        let commentRow = document.createElement("tr");
        let nameData = document.createElement("th");
        let commentData = document.createElement("td");
        let commentDiv = document.createElement("div");

        //populate table elements
        nameData.className = "name";
        nameData.textContent = entry.name;
        commentDiv.className = "comment";
        commentDiv.textContent = entry.comment;
        console.log(entry);

        // add new table elements to table
        nameRow.appendChild(nameData);
        commentData.appendChild(commentDiv);
        commentRow.appendChild(commentData);
        table.prepend(commentRow);
        table.prepend(nameRow);
    });
}

// add new entry to localStorage
document.getElementById("guestbook-form").addEventListener("submit", function (event) {
    event.preventDefault();
    // fetch guestbook data and form data
    let entries = JSON.parse(localStorage.getItem("guestbookEntries")) || [];
    let name = document.getElementById("inputName").value.trim();
    let comment = document.getElementById("inputComment").value.trim();

    // add form data to the list and store the updated list
    entries.push({name, comment});
    localStorage.setItem("guestbookEntries", JSON.stringify(entries));

    event.target.reset();
    location.reload();
})

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

console.log("script loaded");
