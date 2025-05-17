function checkTableEmpty(){
    var table = document.getElementById("user_books")
    var rows = table.getElementsByTagName("tr")
    var textP = document.getElementById("no-books-message")
    if (rows.length <= 1){
        table.style.display = "none"
        textP.style.display = "block"
    }
    else{
        table.style.display = "table"
        textP.style.display = "none"
    }
}

// function to remove the row and return the book when the return button is clicked
function returnBook(button, user, userList, bookList){
    var row = button.parentNode.parentNode
    var tds = row.getElementsByTagName("td")
    var bookTitle = tds[0].textContent
    var author = tds[1].textContent
    var rating = tds[2].querySelector("input").value

    // First check if there is a rating for the book
    if (rating.trim() == ""){
        if (!confirm("You did not leave a rating for the book. Do you still wish to return it?")){
            return
        }
        else{
            rating = null
        }
    }

    // Find the user, remove the book ID from their list. Also increase the number of books available
    for (username of userList){
        if (user.name == username.name && user.type == username.type){
            for (book of bookList){
                if (bookTitle == book.title && book.author == author){
                    var bookID = book.book_id
                    if (rating != null){
                        rating = Number(rating)
                        if (rating < 1 || rating > 10){
                            alert("Please enter a number between 1 and 10")
                            return
                        }

                        if (book.rating == null){
                            book.rating = rating
                        }
                        else{
                            var average = (book.rating + rating) / 2
                            average = Math.round(average * 100) / 100
                            book.rating = average
                        }
                    }
                    user.books = user.books.filter(item => item != bookID)
                    book.num_available++
                }
            }
        } 
    }

    // Send the new data to server, and server will write to file
    fetch('/update-files', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            "users": userList,
            "books": bookList
        })
      })
      .then(res => res.json())
      .catch(err => console.error(err));

    // Now remove the row from the table
    row.parentNode.removeChild(row)
    checkTableEmpty()
}


// build the user's books from user data
fetch("/get_session")
.then(res => res.json())
.then(sessionData => {
    var username = sessionData.user
    var type = sessionData.type

    fetch("../../files/user_data.json")
    .then(response => {
        if (!response.ok) throw new Error("Failed to fetch JSON")
        return response.json()
    })
    .then(userData => {
        var userList = userData["users"]
        var table = document.getElementById("user_books")
        userList.forEach(user => {
            if (user.name == username && user.type == type){
                var userBookList = user.books
                fetch("../../files/books.json")
                .then(response => {
                    if (!response.ok) throw new Error("Failed to fetch JSON")
                    return response.json()
                })
                .then(bookData => {
                    var allBooks = bookData["books"]
                    for (bookID of userBookList){
                        for (book of allBooks){
                            if (bookID == book.book_id){
                                var newRow = table.insertRow()
                                var cell0 = newRow.insertCell(0)
                                var cell1 = newRow.insertCell(1)
                                var cell2 = newRow.insertCell(2)
                                var cell3 = newRow.insertCell(3)
            
                                cell0.appendChild(document.createTextNode(book.title))
                                cell1.appendChild(document.createTextNode(book.author))

                                var ratingInput = document.createElement("input")
                                ratingInput.type = "number"
                                ratingInput.className = "rating_input"
                                ratingInput.min = "0"
                                ratingInput.max = "5"
                                ratingInput.step = "0.1"
                                cell2.appendChild(ratingInput)

                                var returnButton = document.createElement("input")
                                returnButton.className = "return_button"
                                returnButton.type = "button"
                                returnButton.value = "Return"
                                returnButton.onclick = function() {
                                    returnBook(this, user, userList, allBooks)
                                }
                                cell3.appendChild(returnButton)
                            }
                        }
                    }
                    checkTableEmpty()
                })
            }
        })
    })
})

