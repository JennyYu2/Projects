function checkoutBook(button, user, userList, bookList){
    var row = button.parentNode.parentNode
    var tds = row.getElementsByTagName("td")
    var bookTitle = tds[0].textContent
    var author = tds[1].textContent
    var type = tds[2].textContent

    // Add the book id to the user's book list
    for (book of bookList){
        if (book.title == bookTitle && book.author == author && book.type == type){
            book.num_available--
            for (username of userList){
                if (username.name == user.name){
                    username.books.push(book.book_id)
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

    // Remove that row from the table
    row.parentNode.removeChild(row)
}


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
        var table = document.getElementById("checkout_books")
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
                    for (book of allBooks){
                        // List the books in the table if there is at least one available
                        // and the user doesn't have it yet
                        if (book.num_available > 0 && !userBookList.includes(book.book_id)){
                            var newRow = table.insertRow()
                            var cell0 = newRow.insertCell(0)
                            var cell1 = newRow.insertCell(1)
                            var cell2 = newRow.insertCell(2)
                            var cell3 = newRow.insertCell(3)
                            var cell4 = newRow.insertCell(4)
                            var cell5 = newRow.insertCell(5)

                            cell0.appendChild(document.createTextNode(book.title))
                            cell1.appendChild(document.createTextNode(book.author))
                            cell2.appendChild(document.createTextNode(book.type))
                            cell3.appendChild(document.createTextNode(book.rating))
                            cell4.appendChild(document.createTextNode(book.num_available))

                            var checkoutButton = document.createElement("input")
                            checkoutButton.className = "checkoutButton"
                            checkoutButton.type = "button"
                            checkoutButton.value = "Checkout"
                            checkoutButton.onclick = function () {
                                checkoutBook(this, user, userList, allBooks)
                            }
                            cell5.appendChild(checkoutButton)

                        }
                    }
                })
            }
        })
    })
})