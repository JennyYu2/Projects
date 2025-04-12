let themeMode = localStorage.getItem('darkmode')
const themeSwitch = document.getElementById('theme-switch')

const enableDark = () => {
    document.body.classList.add('darkmode')
    document.getElementById("theme-switch").classList.add("darkmode")
    localStorage.setItem('darkmode', 'active')
}

const disableDark = () => {
    document.body.classList.remove('darkmode')
    document.getElementById("theme-switch").classList.remove("darkmode")
    localStorage.setItem('darkmode', null)
}

if(themeMode === "active") enableDark()

themeSwitch.addEventListener("click", () => {
    themeMode = localStorage.getItem('darkmode')
    themeMode !== "active" ? enableDark() : disableDark()
})