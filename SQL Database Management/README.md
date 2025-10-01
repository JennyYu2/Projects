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
- [ER Diagram](#er-diagram)
- [Database Tables](#database-tables)
- [Pipeline](#pipeline)

---

## Description

This project is a Java and SQL arcade management system that simulates an arcade’s database! <br>

Users can log in as Admins (to manage members, games, and prizes) or as Customers (to buy tokens, redeem prizes, and manage accounts). <br>
Additionally, pre-built queries allow users to analyze arcade activity, such as top scores and spending.

---

## Instructions to Run the Program:

0. Prerequisites
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

## ER Diagram

<div align="center">  
  <img src="database/images/ER Diagram.png" alt="ER diagram" width="700" height="641">
</div>

---

## Database Tables

### Coupon

Manages coupons assigned to members
```
 ________________________________________________________________
| CID | MID (fk to MID in Member) | description | expirationDate |
 ----------------------------------------------------------------
```

### Game

Defines arcade games with token cost and score multiplier (factor)
```
 _________________________________
| GID | name | tokenCost | factor |
 ---------------------------------
```

### GamePlay

Logs every game played by a member, including score and tickets earned
```
 _____________________________________________________________________________________________________
| GameplayID GID (fk to GID in Game) | MID (fk to MID in Member) | score | ticketsEarned | datePlayed |
 -----------------------------------------------------------------------------------------------------
```

### Member

Stores customer account information
```
 ___________________________________________________________________
| MID | name | phoneNo | address | tier | totalSpent | totalTickets |
 -------------------------------------------------------------------
```

### Prize

Arcade prizes with ticket costs and available inventory
```
 _____________________________________________________
| PrizeID | description | ticketCost | inventoryCount |
 -----------------------------------------------------
```

### PrizeRedemption

Records prize redemption transactions
```
 __________________________________________________________________________________
| XactID | MID (fk to MID in Member) | PrizeID (fk to PrizeID in Prize) | xactDate |
 ----------------------------------------------------------------------------------
```

### TokenPurchase

Tracks token purchases by members
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

4. Enter information to update data in the database or run queries to display current data in the database
   a.

5. When ready to leave the program, select option 0 until back to the main menu and select option 4 to exit

