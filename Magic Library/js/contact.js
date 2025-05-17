var params = new URLSearchParams(window.location.search)

if(params.get('error') == 'sentmessage') {
    alert("Your message has been sent!")
}
