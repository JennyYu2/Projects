function getBooks() {
    fetch('/get_books_to_edit')
    .then(function(res){
        return res.json()
    })
    .then(function(data){
        var count = 0
        var formID = 1000
        var table = document.getElementById('books')
        for(var i = 0; i < data.books.length; i++) {
            var book = data.books[i];
            var row = document.createElement('tr')
            row.setAttribute("id",count)
            

            row.innerHTML = `
            <td>${book.title}</td>
            <td>${book.author}</td>
            <td>${book.type}</td>
            <td>${book.num_available}</td>
            <td>${book.rating}</td>
        `
            var form = document.createElement("form") // what is being submitted for removal. 
            form.setAttribute("method","POST")
            form.setAttribute("action","/edit_library")
            form.setAttribute("id",formID)




            // form information, its stored as hidden inputs to be used 
            var bookID = document.createElement("input")
            bookID.setAttribute("type","hidden")
            bookID.setAttribute("value",book.book_id)
            bookID.setAttribute("name","bookID")


            // make editAuthor 
            var edit_author = document.createElement("input")
            edit_author.setAttribute("type","button")
            edit_author.setAttribute("value","edit Author")
            edit_author.setAttribute("class","actions")
            edit_author.setAttribute("onclick", "editAuthor('"+formID+"')")


            // make rating chane 
            var rate = document.createElement("input")
            rate.setAttribute("type","button")
            rate.setAttribute("value","Change rating")
            rate.setAttribute("class","actions")
            rate.setAttribute("onclick", "changeRating('"+formID+"')")

            

            // make copies  
            var amount = document.createElement("input")
            amount.setAttribute("type","button")
            amount.setAttribute("value","Change copies")
            amount.setAttribute("class","actions")
            amount.setAttribute("onclick", "changeAmount('"+formID+"')")

            


            // make genre  
            var genre = document.createElement("input")
            genre.setAttribute("type","button")
            genre.setAttribute("value","Change Genre")
            genre.setAttribute("class","actions")
            genre.setAttribute("onclick", "changeGenre('"+formID+"')")
            
            
            form.appendChild(bookID)
            
            // add all the entries to the row

            var actions = document.createElement("div")
            actions.setAttribute("class","divActions")
            
            actions.appendChild(edit_author)
            actions.appendChild(rate)
            actions.appendChild(amount)
            actions.appendChild(genre)
            actions.appendChild(form)

            row.appendChild(actions)
            table.appendChild(row)
            count+=1
            formID += 1
        }
    })
    .catch(function(err){
        console.log(err)
    })
}


// done 
function editAuthor(formID){
    var new_author = window.prompt("Enter the new Author")
    var form = document.getElementById(formID)
    var status = document.createElement("input")
    
    status.setAttribute("type","hidden")
    status.setAttribute("value","author")
    status.setAttribute("name","status")
   
    

    var author = document.createElement("input")
    author.setAttribute("type","hidden")
    author.setAttribute("value",new_author)
    author.setAttribute("name","newAuthor")



    form.appendChild(status)
    form.appendChild(author)
    form.submit()
}



// done
function changeRating(formID){
    var new_rating = window.prompt("Enter the new rating")
    if(new_rating == null){
        
    }else{ // i wanted to give them a chance to leave before trying inputs or a bit after hence why i check twice!
    while( isNaN((new_rating)) || new_rating < 0 || new_rating > 10){
            new_rating = window.prompt("Invalid. Please enter a positve integer")
            if(new_rating == null){
                break
            }else{
                new_rating = parseInt(new_rating)
            }
    }
}


    var form = document.getElementById(formID)

    
    var status = document.createElement("input")
    status.setAttribute("type","hidden")
    status.setAttribute("value","rating")
    status.setAttribute("name","status")



    var rating = document.createElement("input")
    rating.setAttribute("type","hidden")
    rating.setAttribute("value",new_rating)
    rating.setAttribute("name","newRating")

    form.appendChild(status)
    form.appendChild(rating)

    form.submit()
}

// done 
function changeAmount(formID){
    var new_amount = window.prompt("Enter the new amount of copies")
    if(new_amount == null){
        
    }else{ // i wanted to give them a chance to leave before trying inputs or a bit after hence why i check twice!
    while( isNaN((new_amount)) || new_amount < 0){
            new_amount = window.prompt("Invalid. Please enter a positve integer")
            if(new_amount == null){
                break
            }else{
               new_amount = parseInt(new_amount)
            }
    }
}

    var form = document.getElementById(formID)
    var status = document.createElement("input")
    status.setAttribute("type","hidden")
    status.setAttribute("value","amount")
    status.setAttribute("name","status")



    var amount = document.createElement("input")
    amount.setAttribute("type","hidden")
    amount.setAttribute("value",new_amount)
    amount.setAttribute("name","amountChanged")


    form.appendChild(status)
    form.appendChild(amount)

    form.submit()

}


function changeGenre(formID){
    var new_genre = window.prompt("Enter the new genre")
    
    
    var form = document.getElementById(formID)
    var status = document.createElement("input")
    
    status.setAttribute("type","hidden")
    status.setAttribute("value","genre")
    status.setAttribute("name","status")



    var genre = document.createElement("input")
    genre.setAttribute("type","hidden")
    genre.setAttribute("value",new_genre)
    genre.setAttribute("name","genre")


    form.appendChild(status)
    form.appendChild(genre)

    form.submit()

}
//document.addEventListener('DOMContentLoaded', getBooks);
