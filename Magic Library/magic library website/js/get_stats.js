function getStats() {
    fetch('/get_author_stats')
    .then(function(res){
        return res.json()
    })
    .then(function(data){
        // table
        var table = document.getElementById('books')

        if(data.books.length == 0) {
            var row = document.createElement('tr')
            row.innerHTML = `<td colspan="3" style="text-align: center;">You have no books in the library</td>`
            table.appendChild(row);
        }

        for(var i = 0; i < data.books.length; i++) {
            var book = data.books[i];

            var row = document.createElement('tr')
            row.innerHTML = `
            <td>${book.title}</td>
            <td>${book.type}</td>
            <td>${book.rating ?? 'N/A'}</td>` // display N/A if rating is null  
            table.appendChild(row)        
        }

        // general stats
        var gen1 = document.getElementById('gen1')
        var gen2 = document.getElementById('gen2')
        var gen3 = document.getElementById('gen3')

        gen1.innerHTML = 'Total books submitted: '+data.books.length
        gen2.innerHTML = 'Average rating across all books: '+getAverage(data.books)
        gen3.innerHTML = 'Highest rated genre(s): '+getMost(data.books)

    })
    .catch(function(err){
        console.log(err)
    })
}

function getAverage(books) {
    var sum = 0
    var total = 0
    for(var i = 0; i < books.length; i++) {
        if (books[i].rating != null) {
            sum = sum+books[i].rating
            total = total+1
        }
    }
    
    if(sum == 0 || total == 0) {
        return 'N/A'
    }
    return (sum/total).toFixed(2)
}


function getMost(books) {
    var genreRatings = {} // ratings for each genre and the number of books for that genre

    for (var i = 0; i < books.length; i++) {
        var genre = books[i].type
        var rating = books[i].rating

        if (rating != null) {
            // genre doesn't already exist
            if (!genreRatings[genre]) {
                genreRatings[genre] = {sum:0, count:0} // add new genre and rating
            }
            genreRatings[genre].sum += rating
            genreRatings[genre].count += 1
        }
    }

    var bestAvg = 0 // best average
    var bestGenres = [] // list of genres in case there is a tie
    for (var genre in genreRatings) {
        var average = genreRatings[genre].sum/genreRatings[genre].count

        // get the maximum average rating and the genre it belongs to
        if (average > bestAvg) {
            bestAvg = average
            bestGenres = [genre]
        } 
        else if (average === bestAvg) {
            bestGenres.push(genre)
        }
    }

    if (bestGenres.length == 0) {
        return 'N/A'
    }

    return bestGenres.join(', ')+' ('+bestAvg.toFixed(2)+')'
}


function getVal(val) {
    if (val == 'N/A') {
        return Infinity
    }
    else {
        return parseFloat(val)
    }
}

var ascending = true
function sortRating(event) {
    event.preventDefault() // stop the loading

    var table = document.getElementById("books")
    var rows = table.rows
    var data = []

    // get all the rows
    for (var i = 1; i < rows.length; i++) {
        data.push(rows[i])
    }

    // sort the list in ascending order
    if(ascending) {
        for(var i = 0; i < data.length; i++) {
            for(var j = 0; j < data.length-i-1; j++) {
                var rowOne = data[j].cells[2].innerText
                var rowTwo = data[j+1].cells[2].innerText

                var first = getVal(rowOne)
                var second = getVal(rowTwo)

                if(first > second) {
                    var temp = data[j]
                    data[j] = data[j + 1]
                    data[j + 1] = temp
                }
            }
        }
    }
    // sort the list by descending order
    else if(!ascending) {
        for(var i = 0; i < data.length; i++) {
            for(var j = 0; j < data.length-i-1; j++) {
                var rowOne = data[j].cells[2].innerText
                var rowTwo = data[j+1].cells[2].innerText

                var first = getVal(rowOne)
                var second = getVal(rowTwo)

                if(first < second) {
                    var temp = data[j]
                    data[j] = data[j + 1]
                    data[j + 1] = temp
                }
            }
        }
    }

    for (var i = 0; i < data.length; i++) {
        table.appendChild(data[i])
    }

    ascending = !ascending
}