var params = new URLSearchParams(window.location.search)

if(params.get('error') == 'published') {
    alert("The book has been successfully published")
}
else if(params.get('error') == 'denied') {
    alert("Book has been denied for publishing")
}
