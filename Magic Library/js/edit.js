var params = new URLSearchParams(window.location.search);

if(params.get('error') == 'author') {
    alert("The author has been updated")
}
else if(params.get('error') == 'genre') {
    alert("The genre of the book has been updated")
}
else if(params.get('error') == 'amount') {
    alert("The amount of copies has been modifed")
}
else if(params.get('error') == 'rating') {
    alert("book rating has been updated")
}

