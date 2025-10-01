# SQL Database Management

## Authors:

- Hamad Ayaz
- Josh Samadder
- **Jenny Yu**

*April 2024* 

---

## Table of Contents
- [Description](#description)
- [Database Concepts](#database-concepts)
- [Instructions](#instructions-to-run-the-program)
- [ER Diagram](#er-diagram)
- [Database Tables](#database-tables)
- [Pipeline](#pipeline)

---

## Description
[Back to top](#table-of-contents)

This project is a Java and SQL arcade management system that simulates an arcade’s database! <br>

Users can log in as:
- **Admins** --> manage members, games, and prizes
- **Customers** --> buy tokens, redeem prizes, and manage their accounts

Additionally, pre-built queries allow users to analyze arcade activity, such as top scores and spending.

---

## Database Concepts
[Back to top](#table-of-contents)

- **Normalization**
  - Ensures the database avoids redundancy and anomalies by organizing into BCNF.  
  - All relations are in Boyce-Codd Normal Form (BCNF) .
  - Each table has a primary key that uniquely identifies rows.
  - Example: `GamePlayID --> (GID, MID, score, ticketsEarned, datePlayed)` ensures no repeating groups.
 
- **Keys and Constraints**
  - **Primary Keys (PK):** Every table has a unique identifier (Ex: `MID` for Member, `GID` for Game).
  - **Foreign Keys (FK):** Relationships are enforced (Ex: `MID` in TokenPurchase references Member).
  - **Referential Integrity:** Cascading updates/deletes can be applied to maintain consistency.
 
- **Relationships**
  - **One-to-Many:** A Member can have many TokenPurchase or GamePlay records.
  - **Many-to-Many:** Members redeem many Prizes through PrizeRedemption.
   
- **Queries showcasing SQL concepts:**
  - Aggregations and Joins: 

    Example: Query 2. Members who spent $100 on tokens this month
    ```java
    // Java query string for SQL query
    
    String query = "SELECT m.name, m.tier, SUM(tp.amountSpent) AS TotalSpent " +
					"FROM hamadayaz.Member m " +
					"JOIN hamadayaz.TokenPurchase tp ON m.MID = tp.MID " +
					"WHERE tp.purchaseDate >= ADD_MONTHS(CURRENT_DATE, -1) " +
					"GROUP BY m.name, m.tier " +
					"HAVING SUM(tp.amountSpent) >= 100";
    ```
    
  - Selections: 
 
    Example: Query 3. Prizes a member can redeem
    ```java
    // Java query string for SQL query

    String ticketsQuery = "SELECT totalTickets FROM hamadayaz.Member WHERE MID = ?"; // Initial query that gets us the number of tickets the member has
    int ticketNo = ans1.getInt("totalTickets"); // Grab the number of tickets they have as an integer
		String prizesQuery = "SELECT description FROM hamadayaz.Prize WHERE ticketCost <= ?"; // Get the prizes that the member can get with the amount of tickets they have
    ```
    
  - Ordering/Grouping:
 
    Example: Query 4. Highest game score by a member
    ```java
    // Java query string for SQL query
    
    String query = "SELECT g.Name AS GameName, gp.score FROM hamadayaz.GamePlay gp " +
					"JOIN hamadayaz.Game g ON gp.GID = g.GID " +
					"WHERE gp.MID = ? ORDER BY gp.score DESC";
    ```

---

## Instructions to Run the Program:
[Back to top](#table-of-contents)

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
[Back to top](#table-of-contents)

<div align="center">  
  <img src="database/images/ER Diagram.png" alt="ER diagram" width="700" height="641">
</div>

---

## Database Tables
[Back to top](#table-of-contents)

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
[Back to top](#table-of-contents)

1. When the program is first run, user is prompted to select their role or run queries:
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

3. Enter the specified information to update data in the database or run queries to display current data in the database

4. When ready to leave the program, select option 0 until back to the main menu and select option 4 to exit

