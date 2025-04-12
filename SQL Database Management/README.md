# SQL Database Management

## Instructions for running the program:

i.) Go to the root directory and compile all .java files using:

    javac *.java

ii.) Run MemberManagementApp.java and enter credentials when prompted:
     
     java MemberManagementApp
     

a) When program is run, a menu displays the options for the user to pick their role. Type the number of the corresponding role that you want to pick and press enter to make a selection.
    
    Choose your role:
    1. Database Admin
    2. Customer
    3. Queries
    4. Exit Program


b) Then depending on what you choose, you get either the menu for Admin operations:

    0. <-- to Main Menu
    Member Operations:
    1. Add Member
    2. Update Member
    3. Delete Member
    Game Operations:
    4. Add Game
    5. Delete Game
    Prize Operations:
    6. Add Prize
    7. Delete Prize

  
   Or you get the menu for Customer operations:

    0. <-- to Main Menu
    Member Operations:
    1. Update Your Account Info
    2. Delete Your Account
    3. Redeem Prizes
    4. Buy Tokens

   Or you get the menu for the Queries:

    Select a query to run:
    1. List all games and high scores
    2. Members who spent $100 on tokens this month
    3. Prizes a member can redeem
    4. Highest game score by a member
    0. Return to main menu

c) Then enter the number for the corresponding operation you would like to execute for Admin/Customer/Queries, press enter, and enter all the necessary data when prompted by the program. The program will then tell you the outcome of the operation you have ran. 

d) When you are done, return to the main menu if not already there (option 0, enter) and type the option to Exit Program, press enter. 

<br>
<br>


## Workload distribution:
* Josh Samadder:
  - Wrote the code for all of the queries that the application is to be able to answer.
  - Worked on the ER diagram and normalization analysis.
  - Wrote the design.pdf document detailing the project.
  - Worked on the README file.
  
* Hamad Ayaz:
  - Wrote the code for the JDBC application’s interface to enable users to add, update and delete a member.
  - Wrote the code for the JDBC application’s interface to enable users to add or delete a game.
  - Worked on the ER diagram and normalization analysis.
  - Created the UI for the user to perform the required functionalities and run the queries.
  - Worked on the README file.

* Jenny Yu:
  - Wrote the sql scripts to set up and populate the tables with data. 
  - Wrote the code for the JDBC application’s interface to enable users to add or delete a prize.
  - Worked on the ER diagram and normalization analysis.
  - Worked on the README file.


