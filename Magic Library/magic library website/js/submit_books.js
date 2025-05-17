var params = new URLSearchParams(window.location.search)

if(params.get('error') == 'success') {
    alert("Successfully submitted book for review!")
}
else if(params.get('error') == 'notmatch') {
    alert("Author does not match your username")
}
