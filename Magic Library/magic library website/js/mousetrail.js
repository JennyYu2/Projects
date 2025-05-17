// mousetrail
document.addEventListener("mousemove", function(e) {
    var sparkle = document.createElement("div")
    sparkle.classList.add("sparkle-trail")
    sparkle.textContent = "⊹"

    sparkle.style.left = e.pageX + "px"
    sparkle.style.top = e.pageY + "px"
    
    document.body.appendChild(sparkle)

    setTimeout(function() {
        sparkle.remove()
    }, 500)
})