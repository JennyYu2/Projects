# ₊ ⊹ Magic Library ⊹₊ ⋆

<div align="center">
  <img src="https://github.com/user-attachments/assets/37b1ce4f-6c68-44f6-b46d-50abf4e00c91" width="300" height="300"/>
</div>

Welcome to the **Magic Library**!  
This is a website inspired by a real-world scenario of a library where users can browse, submit, and manage books.  
Users can log in as **Readers**, **Authors**, or **Publishers**, and utilize the different functionalities.

---

## Table of Contents
- [How to run the program](#how-to-run-the-program)
- [Project requirements](#project-requirements)
- [Modules and work split](#modules-and-work-split)
- [Functionalities](#functionalities)

---

## How to run the program

### Prerequisites:
- Must have express installed
  ```bash
  npm install express
  ```
- Must have express-session installed(to manage user sessions)
  ```bash
  npm install express-session
  ```

### To run the server:
1. Clone this GitHub repository
```bash
git clone https://github.com/JennyYu2/CSC337-Final-Project.git
```
2. Navigate to the project root folder
3. Start the server:
```bash
node server.js
```
4. Open your browser and visit: http://localhost:8080

---

## Project Requirements:

- Minimum of three interconnected modules:
  - Three modules: Readers, Authors and Publishers
  - All modules are interconnected. When users run the server they are greeted with the homepage where they can use the links in the nav bar to login or signup as one of the three types of users.
  - Once they login/signup users will be taken to the homepage for their specific user type and they can use the functionalities for that user type.
    
- User module with authentication (login, logout, etc.)
  - Users can login from the homepage(index.html) and they can logout from any of the three modules, which takes them back to the general homepage(index.html).
  - Logging out also destroys the current session.
    
- Use of session management:
  - Sessions are managed using express-session where Session data(username and type) is stored when users login and destroyed when they logged out.
    
- Data persistence using files or databases (e.g., CSV, JSON, MongoDB):
  - User information(username, password and account type) is stored in **user_data.json**, where the passwords are encrypted using crypto.
  - List of books in the library are stored in **books.json** and the contents of the file gets read when the data is displayed on the website.
  - List of author submitted books for publisher approval is stored in **author_books.json** and the Publisher account types can access these submissions.
  - Files can be found in the /files folder.
    
- Logical navigation between pages/modules:
  - When server is first started it takes users to the general homepage where they can login/signup
  - After logging in, the respective user dashboards are shown for the different user types
  - Users will then have access to browsing, submitting, editing, or approving books based on user type from the nav bar
    
- A working frontend using HTML, CSS, and JavaScript:
  - HTML pages display the necessary information for each webpage.
  - Various CSS pages are applied to HTML pages for general website style and specific page styles to make the overall website appear coherent and aesthetically pleasing.
  - JavaScript files are applied to HTML pages for dynamic updates from files for each specific webpage. 
  - HTML, CSS and JS files are separated into respective folders for organization.
    
- A working backend code using the technologies taught in class:
  - Website is served using Node.js.
  - Uses Express.js and express-session for session management in the backend.
  - Server handles the routes in the backend for file reading/writing, form submissions and link navigation.

---

## Modules and Work split

### 0. **Jenny** -- General(non-logged-in pages)
- index.html
- show_books.html
- login.html
- gisnup.html
- contact.html
- logout.html

### 1. **Josh** -- /Readers
- reader_home.html
- checkout.html
- your_books.html
- reader_contact.html

### 2. **Jenny** -- /Authors  
- author_home.html
- author_books.html
- submit_books.html
- view_stats.html
- author_contact.html

### 3. **Mariposa** -- /Publishers  
- publisher_home.html
- publisher_books.html
- approve_books.html
- edit_library.html
- publisher_contact.html

### 4. **Other** 
- Each group member worked on the CSS and JavaScript files that are linked and applied in their HTML files for their submodule.
- Each member also added to server.js to serve the HTML files they wrote.
- Josh added express_session for session handling and also added the encryption before passwords are stored.
- Jenny wrote page_format.css for general style across all HTML pages and also mousetrail.js for the mousetrail.
- Mariposa handeled maintainence on the JSON files.

---

## Functionalities

### General:
  - Homepage
  - View books in the library
    - Displays a table with: Title, Author, Genre, Copies available, Rating
  - Login form 
  - Signup form
  - Contact us form

### Readers:
  - Homepage
  - View books in the library
    - Additional button for checking out books
    - Checkout books
  - View their books
    - Button to return books
    - Readers can enter a rating for their books before returning them
  - Contact us form
 
### Authors:
  - Homepage
  - View books in the library
    - Displays a table with: Title, Author, Genre, Copies available, Rating
  - Submit books for approval form
  - View your stats
    - General stats: Total, Average rating, Highest rated genre(average)
    - Displays a table with: Title, Genre, Rating for only their books
    - Can sort by rating
  - Contact us form
 
### Publishers:
  - Homepage
  - View books in the library
    - Displays a table with: Title, Author, Genre, Copies available, Rating
  - Approve or decline new book submissions
    - Displays a table with: Title, Author, Genre, Copies available, Description
    - Buttons to approve or decline new books
  - Edit libaray
    - Displays a table with: Title, Author, Genre, Copies available, Rating
    - Buttons to edit the Author, Title, Genre, Copies available, Rating
  - Contact us form
