# SQL Database Management

## Authors:

- Hamad Ayaz
- Josh Samadder
- **Jenny Yu**

*April 2024* 

---

## Table of Contents
- [Description](#description)
- [Instructions](#instructions-to-run-the-program)
- [Database Tables](#database-tables)
- [Pipeline](#pipeline)

---

## Description

This project is a SQL Database simulator that is based on an arcade! 

There are two different roles with different functionalities:
1. Database admin
   - Add, update and delete members
   - Add and delete arcade games
   - Add and delete prize options
  
2. Customer
   - Manage account and account information
   - Buy tokens
   - Redeem prizes

<br>

Additionally there are also queries that users can run:
- List all games and high scores
- Members who spent $100 on tokens this month
- Prizes a member can redeem
- Highest game score by a member

---

## Instructions to Run the Program:

0. Prerequities
   - Must have Java installed
   - Clone this repository or download all files

1. Navigate to the root directory and compile all .java files:
```
    javac *.java
```

2. Run MemberManagementApp.java:
```   
     java MemberManagementApp
``` 
    
3. Enter the number for the corresponding prompts to execute, enter necessary information when prompted

4. Have fun editing data running queries!


---

## Database Tables

### Coupon
```
 ________________________________________________________________
| CID | MID (fk to MID in Member) | description | expirationDate |
 ----------------------------------------------------------------
```

### Game
```
 _________________________________
| GID | name | tokenCost | factor |
 ---------------------------------
```

### GamePlay
```
 _____________________________________________________________________________________________________
| GameplayID GID (fk to GID in Game) | MID (fk to MID in Member) | score | ticketsEarned | datePlayed |
 -----------------------------------------------------------------------------------------------------
```

### Member
```
 ___________________________________________________________________
| MID | name | phoneNo | address | tier | totalSpent | totalTickets |
 -------------------------------------------------------------------
```

### Prize
```
 _____________________________________________________
| PrizeID | description | ticketCost | inventoryCount |
 -----------------------------------------------------
```

### PrizeRedemption
```
 __________________________________________________________________________________
| XactID | MID (fk to MID in Member) | PrizeID (fk to PrizeID in Prize) | xactDate |
 ----------------------------------------------------------------------------------
```

### TokenPurchase
```
 ________________________________________________________________________
| PID | MID (fk to MID in Member) | tokenNo | amountSpent | purchaseDate |
 ------------------------------------------------------------------------
```

---

## Pipeline

1. When program is first ran, user is prompted to select their role or run queries:
```
Choose your role:
    1. Database Admin
    2. Customer
    3. Queries
    4. Exit Program
```

2. Then depending on their choice the user is presented with the menu with the options:
   a. Database Admin
   ```
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
   ```

   b. Customer
   ```
   0. <-- to Main Menu
   Member Operations:
   1. Update Your Account Info
   2. Delete Your Account
   3. Redeem Prizes
   4. Buy Tokens
   ```

   c. Queries
   ```
   Select a query to run:
   1. List all games and high scores
   2. Members who spent $100 on tokens this month
   3. Prizes a member can redeem
   4. Highest game score by a member
   0. Return to main menu
   ```

3. Enter information to update data in the database or run queries to display current data in the database
   a.

4. When ready to leave the program, select option 0 until back to the main menu and select option 4 to exit

