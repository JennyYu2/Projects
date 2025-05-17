var express = require('express')
var app = express()
var path = require('path')
var fs = require('fs')
var session = require("express-session")
var crypto = require("crypto")

var rootFolder = __dirname
app.use(express.static(rootFolder))
app.use(express.urlencoded({ extended: true }))
app.use(session ({
    secret: "leepicbacon",
    resave: false,
    saveUninitialized: true
}))
app.use(express.json())

// Retrieve session information ------------------------------------------------------------
app.get('/get_session', function(req, res){
    res.json({
        "user": req.session.user,
        "type": req.session.type
    })
}) 

// Write updated user/book information (such as after returning books, checking out books, etc.)
app.post('/update-files', function(req, res){
    var body = req.body
    var newUserList = {"users": body["users"]}
    var newBookList = {"books": body["books"]}
    
    var userFile = path.join(rootFolder, 'files', 'user_data.json')
    var booksFile = path.join(rootFolder, 'files', 'books.json')

    fs.writeFile(userFile, JSON.stringify(newUserList, null, 4), {'encoding':'utf8'}, function(err){
        if (err != null) console.log(err)
    })
    fs.writeFile(booksFile, JSON.stringify(newBookList, null, 4), {'encoding':'utf8'}, function(err){
        if (err != null) console.log(err)
    })
})

// Homepage --------------------------------------------------------------------------------
app.get('/', function(req, res){
    res.sendFile(path.join(rootFolder, 'index.html'))
})

app.get('/index', function(req, res){
    res.sendFile(path.join(rootFolder, 'index.html'))
})


// login page --------------------------------------------------------------------------------
app.get('/login.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'login.html'))    
})

// login_action
app.post('/login_action', function(req, res) {
    var name = req.body.name
    // encrypt password to compare with password in the file
    var password = crypto.createHash('sha256').update(req.body.password).digest('hex')
    var type = req.body.type

    if(!name || !password || !type) {
        return res.send("Fields not filled out")
    }

    // path to user_data.json
    var filePath = path.join(rootFolder, 'files', 'user_data.json')
    var users = [] // list of previous data from the file
    
    // read existing data from the file into the users list if file exists
    if(fs.existsSync(filePath)) {
        fs.readFile(filePath, {'encoding':'utf8'}, function(err, out){
            if(err == undefined){
                // read JSON file into array
                var parse = JSON.parse(out)
                users = parse.users

                // check if username exists
                var exists = false
                for(var i=0; i < users.length; i++) {
                    // if username exists
                    if(users[i].name == name) {
                        // check if password matches, if password matches
                        if(users[i].password == password) {
                            // check if type matches
                            if(users[i].type == type) {
                                exists = true
                            }
                        }
                    }
                }
                
                // if the username, password and type match an existing user
                if(exists) {
                    req.session.user = name
                    req.session.type = type

                    // go to the homepage for the user type
                    if(type == "author") {
                        res.redirect('/author_home.html')
                        //res.sendFile(path.join(rootFolder, 'subpages', 'authors', 'author_home.html'))
                    }
                    else if(type == "reader") {
                        res.redirect('/reader_home.html')
                        //res.sendFile(path.join(rootFolder, 'subpages', 'readers', 'reader_home.html'))
                    }
                    else if(type == "publisher") {
                        res.redirect('/publisher_home.html')
                        //res.sendFile(path.join(rootFolder, 'subpages', 'publishers', 'publisher_home.html'))
                    } 
                }
                else {
                    res.redirect('/login.html?error=notexist')
                }
            }
            else{
                console.log(err)
            }
        })
    }
    // file does not already exist, there are no users, should not be able to log in
    else {
        res.redirect('/login.html?error=notexist')
    }
})


// signup page --------------------------------------------------------------------------------
app.get('/signup.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'signup.html'))
})

// signup_action
app.post('/signup_action', function(req, res) {
    var name = req.body.name
    // encrypt password before storing it
    var password = crypto.createHash('sha256').update(req.body.password).digest('hex')
    var type = req.body.type

    if(!name || !password || !type) {
        return res.send("Fields not filled out")
    }

    // path to user_data.json
    var filePath = path.join(rootFolder, 'files', 'user_data.json');
    var users = [] // list of previous data from the file

    // read existing data from the file into the users list if file exists
    if(fs.existsSync(filePath)) {
        fs.readFile(filePath, {'encoding':'utf8'}, function(err, out){
            if(err == undefined){
                // read JSON file into array
                var parse = JSON.parse(out)
                users = parse.users

                // check if username exists
                var taken = false
                for(var i=0; i < users.length; i++) {
                    // if username exists, check if account type matches
                    if(users[i].name == name) {
                        if(users[i].type == type) {
                            taken = true
                            return res.redirect('/signup.html?error=taken')
                        }
                    }
                }
                
                // if not taken, fs.appendFile the new user {"name":"","password":"", "type":""}
                var newUser = {"name":name, "password":password, "type":type}
                if(taken == false) {
                    if (type == "reader") newUser.books = [];

                    users.push(newUser) // add new user to the array
                    var writeData = {users} // put users in a dictionary

                    // write the array of users back into the file
                    fs.writeFile(filePath, JSON.stringify(writeData, null, 4), {'encoding':'utf8'}, function(err){
                        if(err == undefined){   
                            req.session.user = name;
                            req.session.type = type;
                            // go to the homepage for the user type
                            if(type == "author") {
                                res.redirect('/author_home.html')
                                //res.sendFile(path.join(rootFolder, 'subpages', 'authors', 'author_home.html'))
                            }
                            else if(type == "reader") {
                                res.redirect('/reader_home.html')
                                //res.sendFile(path.join(rootFolder, 'subpages', 'readers', 'reader_home.html'))
                            }
                            else if(type == "publisher") {
                                res.redirect('/publisher_home.html')
                                //res.sendFile(path.join(rootFolder, 'subpages', 'publishers', 'publisher_home.html'))
                            } 
                        }
                        else{
                            console.log(err)
                        }
                    })
                }
            }
            else{
                console.log(err)
            }
        })
    }

    // file does not already exist
    else {
        var newUser = {"name":name, "password":password, "type":type}
        users.push(newUser) // add new user
        var writeData = {users} // put users in a dictionary

        // write to new file
        fs.writeFile(filePath, JSON.stringify(writeData, null, 4), {'encoding':'utf8'}, function(err){
            if(err == undefined){   
                // go to the homepage for the user type
                if(type == "author") {
                    res.redirect('/author_home.html')
                    //res.sendFile(path.join(rootFolder, 'subpages', 'authors', 'author_home.html'))
                }
                else if(type == "reader") {
                    res.redirect('/reader_home.html')
                    //res.sendFile(path.join(rootFolder, 'subpages', 'readers', 'reader_home.html'))
                }
                else if(type == "publisher") {
                    res.redirect('/publisher_home.html')
                    //res.sendFile(path.join(rootFolder, 'subpages', 'publishers', 'publisher_home.html'))
                } 
            }
            else{
                console.log(err)
            }
        })
    }
})


// contact us page --------------------------------------------------------------------------------
app.get('/contact.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'contact.html'))
})

app.post('/contact_action', function(req, res){
    res.redirect("/contact.html?error=sentmessage")
})


// show books table --------------------------------------------------------------------------------
app.get('/show_books.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'show_books.html'))
})

app.get('/get_books', function(req, res){
    var filePath = path.join(rootFolder, 'files', 'books.json')

    fs.readFile(filePath, { encoding: 'utf8' }, function(err, out) {
        if (err == undefined) {
            var books = JSON.parse(out)
            res.json(books)
        }
        else {
            console.log(err)
        }
    })
})


// logout page --------------------------------------------------------------------------------
app.get('/logout.html', function(req, res){
    req.session.destroy(function(err) {
        if (err) {
            console.log(err)
        }
    })
    res.sendFile(path.join(rootFolder, 'subpages', 'logout.html'))
})


// AUTHOR pages --------------------------------------------------------------------------------
app.get('/author_home.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'authors', 'author_home.html'))
})

// author see books 
app.get('/author_books.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'authors', 'author_books.html'))
})

app.get('/get_author_books', function(req, res){
    var filePath = path.join(rootFolder, 'files', 'books.json');

    fs.readFile(filePath, { encoding: 'utf8' }, function(err, out) {
        if (err == undefined) {
            var books = JSON.parse(out)
            res.json(books)
        }
        else {
            console.log(err)
        }
    })
})

// submit books 
app.get('/submit_books.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'authors','submit_books.html'))
})

app.post('/submit_book_action', function(req,res){
    var title = req.body.title
    var author = req.body.author
    var genre = req.body.genre
    var number = req.body.copies
    var description = req.body.description

    // check if author matches the logged in author
    var loggedIn = req.session.user

    // username does not match author name
    if(loggedIn.toLowerCase() !== author.toLowerCase()) {
        res.redirect('/submit_books.html?error=notmatch')
    }
    // username matches, add the book for review
    else {
        // path to user_data.json
        var filePath = path.join(rootFolder, 'files', 'author_books.json')
        var submissions = [] // list of previous data from the file

        // read existing data from the file into the users list if file exists
        if(fs.existsSync(filePath)) {
            fs.readFile(filePath, {'encoding':'utf8'}, function(err, out){
                if(err == undefined){
                    // read JSON file into array
                    var parse = JSON.parse(out)
                    submissions = parse.submissions

                    var newSub = {"title":title, "author":author, "genre":genre, "copies":number, "description":description}
                    submissions.push(newSub)
                    var writeData = {submissions} // submissions:submissions
                    
                    // write new submission into file
                    fs.writeFile(filePath, JSON.stringify(writeData, null, 4), {'encoding':'utf8'}, function(err) {
                        if(err == undefined){   
                            res.redirect('/submit_books.html?error=success')
                        }
                        else {
                            console.log(err)
                        }
                    })
                }
                else{
                    console.log(err)
                }
            })
        }
        // file does not already exist
        else {
            var newSub = {"title":title, "author":author, "genre":genre, "copies":number, "description":description}
            submissions.push(newSub)
            var writeData = {submissions} // submissions:submissions

            // write to new file
            fs.writeFile(filePath, JSON.stringify(writeData, null, 4), {'encoding':'utf8'}, function(err){
                if(err == undefined){   
                    res.redirect('/submit_books.html?error=success')
                }
                else{
                    console.log(err)
                }
            })
        }
    }
})

// view stats 
app.get('/view_stats.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'authors','view_stats.html'))
})

app.get('/get_author_stats', function(req, res){
    var filePath = path.join(rootFolder, 'files', 'books.json')
    var curUser = req.session.user

    fs.readFile(filePath, { encoding: 'utf8' }, function(err, out) {
        if (err == undefined) {
            var parsed = JSON.parse(out)
            var books = parsed.books;
            var yourBooks = []

            for(var i = 0; i < books.length; i++) {
                if(books[i].author.toLowerCase() == curUser.toLowerCase()) {
                    yourBooks.push(books[i])
                }
            }
            res.json({books: yourBooks}); 
        }
        else {
            console.log(err);
        }
    })
})

// contact us
app.get('/author_contact.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'authors','author_contact.html'))
})

app.post('/author_contact_action', function(req, res){
    res.redirect("/author_contact.html?error=sentmessage")
})


// READER pages --------------------------------------------------------------------------------
app.get('/reader_home.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'readers', 'reader_home.html'))
})

app.get('/your_books.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'readers', 'your_books.html'))
})

app.get('/checkout.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'readers', 'checkout.html'))
})

// contact us
app.get('/reader_contact.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'readers','reader_contact.html'))
})

app.post('/reader_contact_action', function(req, res){
    res.redirect("/reader_contact.html?error=sentmessage")
})


// PUBLISHER pages --------------------------------------------------------------------------------
app.get('/publisher_home.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'publishers', 'publisher_home.html'));
})

// publisher see books 
app.get('/publisher_books.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'publishers', 'publisher_books.html'))
})

app.get('/get_publisher_books', function(req, res){
    var filePath = path.join(rootFolder, 'files', 'books.json')

    fs.readFile(filePath, { encoding: 'utf8' }, function(err, out) {
        if (err == undefined) {
            var books = JSON.parse(out)
            res.json(books)
        }
        else {
            console.log(err)
        }
    })
})

// contact us
app.get('/publisher_contact.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'publishers','publisher_contact.html'))
})

app.post('/publisher_contact_action', function(req, res){
    res.redirect("/publisher_contact.html?error=sentmessage")
})

// edit library
app.get('/edit_library.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'publishers','edit_library.html'))
})

app.get('/get_books_to_edit', function(req, res){
    var filePath = path.join(rootFolder, 'files', 'books.json');
    fs.readFile(filePath, { encoding: 'utf8' }, function(err, out) {
        if (err == undefined) {
            var books = JSON.parse(out);
            res.json(books); 
        }
        else {
            console.log(err);
        }
    })
})

// approve books
app.get('/approve_books.html', function(req, res){
    res.sendFile(path.join(rootFolder, 'subpages', 'publishers','approve_books.html'))
})

app.get('/get_books_to_publish', function(req, res){
    var filePath = path.join(rootFolder, 'files', 'author_books.json');
    fs.readFile(filePath, { encoding: 'utf8' }, function(err, out) {
        if (err == undefined) {
            var books = JSON.parse(out);
            res.json(books); 
        }
        else {
            console.log(err);
        }
    })
})


// publish actions :) 
app.post('/publish_book', function(req, res){
    var title = req.body.title
    var author = req.body.author
    var genre = req.body.genre
    var copies = req.body.copies
    var status = req.body.status
    var filePath_author = path.join(rootFolder, 'files', 'author_books.json')
    var filePath_books = path.join(rootFolder, 'files', 'books.json')

    if(fs.existsSync(filePath_author)) {
        // this is reading and writing
        fs.readFile(filePath_author, {'encoding':'utf8'}, function(err, out){
            if(err == undefined){
                // this gets data to update
                var parse = JSON.parse(out)
                var submissions = parse.submissions
                
                // before this splice we have to first update all the book ids to match
                
                //getting book to remove on publisher list (match title and author)
                for(var i =0; i < submissions.length; i++){
                    if(submissions[i].title == title && submissions[i].author == author){
                        submissions.splice(i,1)
                    }
                }
                var writeDataAuthor = {submissions}

                // write data for author
                fs.writeFile(filePath_author, JSON.stringify(writeDataAuthor, null, 4), {'encoding':'utf8'}, function(err) {
                    if(err == undefined){   

                    }
                    else {
                        console.log(err)
                    }
                })               

                // writes to public books
                fs.writeFile(filePath_author, JSON.stringify(writeDataAuthor, null, 4), {'encoding':'utf8'}, function(err) { // ffeffe
                    if(err == undefined){   
                    }
                    else {
                        console.log(err)
                    }
                })
            }
            else{
                console.log(err)
            }
        })

        if(status == "allow"){
        fs.readFile(filePath_books, {'encoding':'utf8'}, function(err, out){
           
            if(err == undefined){
                var parse02 = JSON.parse(out)
                books = parse02.books
                
                book_id = books.length +1
                var newEntry = {"book_id":book_id, "title":title, "author":author, "type":genre, "rating":null, "num_available":parseInt(copies)}
                books.push(newEntry)
                var writeData = {books}

                
                fs.writeFile(filePath_books, JSON.stringify(writeData, null, 4), {'encoding':'utf8'}, function(err) {
                    if(err == undefined){   
                        res.redirect('/approve_books.html?error=published')
                    }
                    else {
                        console.log(err)
                    }
                })
            }
            else{
                console.log(err)
            }
        })
    }else{
        res.redirect('/approve_books.html?error=denied')
    }
}
})



// edit actions :) 
app.post('/edit_library', function(req, res){
    var id = req.body.bookID
    var status = req.body.status

    var filePath = path.join(rootFolder, 'files', 'books.json')

    if(fs.existsSync(filePath)) {
        fs.readFile(filePath, { encoding: 'utf8' }, function(err, out) {
            if (err == undefined) {
                var parse = JSON.parse(out)
                var books = parse.books
                for(var i =0; i < books.length; i++){
                    if(books[i].book_id == id){
                        if(status == "author"){
                            //console.log(req.body.newAuthor)
                            if(req.body.newAuthor != 'null'){
                                //console.log(req.body.newAuthor)
                            books[i].author = req.body.newAuthor
                            }
                        }else if(status == "genre"){
                            if(req.body.genre != 'null'){
                            books[i].type = req.body.genre
                            }
                        }else if(status == "rating"){
                            if(req.body.newRating != 'null'){
                            books[i].rating = req.body.newRating
                            }
                        }else if(status == "amount"){
                            //console.log(req.body.amountChanged)
                            if(req.body.amountChanged != 'null'){
                                books[i].num_available = parseInt(req.body.amountChanged)
                            }
                        }
                    }   
                }

                var writeData = {books}
                fs.writeFile(filePath, JSON.stringify(writeData, null, 4), {'encoding':'utf8'}, function(err) {
                    if(err == undefined){   
                    }
                    else {
                        console.log(err)
                    }
                    if(status == "author"){
                        res.redirect("/edit_library.html?error=author")
                    }else if(status == "genre"){
                        res.redirect("/edit_library.html?error=genre")
                    }else if(status == "rating"){
                        res.redirect("/edit_library.html?error=rating")
                    }else if(status == "amount"){
                        res.redirect("/edit_library.html?error=amount")
                    }
                })               
                        }
            else {
                console.log(err)
            }
        })        
}
})


// serve the server --------------------------------------------------------------------------------
app.listen(8080, function(){
    console.log('server running')
})