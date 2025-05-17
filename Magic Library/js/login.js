var params = new URLSearchParams(window.location.search)

if (params.get('error') == 'notfound') {
    alert("User not found")
} 
else if (params.get('error') == 'notexist') {
    alert("Username, password, or account type is incorrect")
}