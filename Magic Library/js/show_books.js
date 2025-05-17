function getBooks() {
    fetch('/get_books')
    .then(function(res){
        return res.json()
    })
    .then(function(data){
        var table = document.getElementById('books')

        for(var i = 0; i < data.books.length; i++) {
            var book = data.books[i]

            var rating
            if(book.rating == null) {
                rating = 'N/A'
            }
            else{
                rating = book.rating
            }

            var row = document.createElement('tr')
            row.innerHTML = `
                <td>${book.title}</td>
                <td>${book.author}</td>
                <td>${book.type}</td>
                <td>${book.num_available}</td>
                <td>${rating}</td>
            `
            table.appendChild(row)
        }
    })
    .catch(function(err){
        console.log(err)
    })
}

