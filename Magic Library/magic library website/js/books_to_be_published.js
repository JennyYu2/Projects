function getBooks() {
    fetch('/get_books_to_publish')
    .then(function(res){
        return res.json()
    })
    .then(function(data){
        var count=0
        var formID = 1000
        var table = document.getElementById('books')

        if(data.submissions.length == 0) {
            var row = document.createElement('tr');
            row.innerHTML = `<td colspan="6" style="text-align: center;">There are no books to be approved</td>`;
            table.appendChild(row);
        }


        for(var i = 0; i < data.submissions.length; i++) {
            var book = data.submissions[i];
            var row = document.createElement('tr')
            row.setAttribute("id",count)
            row.innerHTML = `
                <td>${book.title}</td>
                <td>${book.author}</td>
                <td>${book.genre}</td>
                <td>${book.copies}</td>
                <td>${book.description}</td>
            `

             var buttons = document.createElement("td")

            // // build not approve
            var dissproval = document.createElement("input")
            dissproval.setAttribute("value","Disapprove")
            dissproval.setAttribute("class","approve")
            dissproval.setAttribute("type","button")
            dissproval.setAttribute("onclick", "deny('"+count+"', '"+formID+"')")



            // so we do a secret submit for the table 
            var form = document.createElement("form")
            form.setAttribute("method","POST")
            form.setAttribute("action","/publish_book")
            form.setAttribute("id",formID)

            
            
            // hidden inputs: we dont need desc. 
            
            var book_title = document.createElement("input")
            book_title.setAttribute("type","hidden")
            book_title.setAttribute("value",book.title)
            book_title.setAttribute("name","title")

            
            var book_author = document.createElement("input")
            book_author.setAttribute("type","hidden")
            book_author.setAttribute("value",book.author)
            book_author.setAttribute("name","author")

            
            var book_genre = document.createElement("input")
            book_genre.setAttribute("type","hidden")
            book_genre.setAttribute("value",book.genre)
            book_genre.setAttribute("name","genre")

            var book_copies = document.createElement("input")
            book_copies.setAttribute("type","hidden")
            book_copies.setAttribute("value",book.copies)
            book_copies.setAttribute("name","copies")

             
            // // build approval 
             var approval = document.createElement("input")
             approval.setAttribute("value","Approve")
             approval.setAttribute("class","approve")
             approval.setAttribute("type","button")
             approval.setAttribute("onclick", "approve('"+count+"', '"+formID+"')")


           
            form.appendChild(book_author)
            form.appendChild(book_genre)
            form.appendChild(book_copies)
            form.appendChild(book_title)

            buttons.appendChild(approval)
            buttons.appendChild(dissproval)

            row.appendChild(buttons)
            row.appendChild(form)
            table.appendChild(row)
            count +=1
            formID+=1
            table.appendChild(row)
        }
    })
    .catch(function(err){
        console.log(err)
    })
}

function approve(id,formID){

    var form = document.getElementById(formID)
    var status = document.createElement("input")
    status.setAttribute("type","hidden")
    status.setAttribute("value","allow")
    status.setAttribute("name","status")
    form.appendChild(status)
    form.submit()
    document.getElementById(id).remove()

    
}


function deny(id,formID){

    var form = document.getElementById(formID)
    var status = document.createElement("input")
    status.setAttribute("type","hidden")
    status.setAttribute("value","deny")
    status.setAttribute("name","status")
    form.appendChild(status)
    form.submit()
    document.getElementById(id).remove()

    
}
//document.addEventListener('DOMContentLoaded', getBooks);
