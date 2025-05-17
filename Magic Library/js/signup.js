var params = new URLSearchParams(window.location.search)

if(params.get('error') == 'taken') {
    alert("Username already taken for this account type")
}
