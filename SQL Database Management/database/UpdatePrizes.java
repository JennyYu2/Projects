package programFour;

import java.sql.*; // For access to the SQL interaction methods
import java.text.DecimalFormat;
import java.util.Scanner;


/*
 * Name: Jenny Yu
 * Course: CSC 460 
 * Instructor: McCann (TA: Musa)
 * File: UpdatePrizes.java
 * Due date: 4/29/24
 * 
 * Description: Queries to add and delete prizes from the
 * Prize table. Takes user input for prizeID to add or 
 * delete from the Prize table. Users can choose which option
 * they want to run based on the menu. 
 * 
 */


public class UpdatePrizes {
	
	
	/*
	 * Pre-condition: Needs the Prize database to be set up in Oracle.
	 * Post-condition: Called when the user wants to add a new prize or 
	 * add to an existing prize. Adds new prize to the Prize table or adds
	 * to the inventoryAmount of an existing prize.
	 * 
	 * Params: dbconn - Connection
	 *         stmt - Statement
	 *         answer - ResultSet
	 *         
	 * Purpose: Asks user for prizeID of new prize to add. If the prizeID
	 * already exists, add one to the inventoryAmount of the existing prize.
	 * If prizeID does not exist, asks user to give a description, the ticketCost
	 * and inventoryCount for the new prize they want to add. Adds the new prize 
	 * with the specifications to the Prize table. 
	 * 
	 */
	private static void addPrize(Connection dbconn, Statement stmt, ResultSet answer) {
		try {
			stmt = dbconn.createStatement(); // Create statement
			Scanner sc = new Scanner(System.in); // Create a new scanner to take input
			
			System.out.print("Enter prizeID for the prize to add: ");
	        String PID = sc.nextLine(); // Get the prizeID from user input
	        
	        // Query to check for the prize in the Prize table using prizeID
	        String checkForPrize = "SELECT COUNT(*) FROM jennyyu.Prize WHERE prizeID = "+PID;
	        answer = stmt.executeQuery(checkForPrize); // Execute the query
	        answer.next();
	        
	        // If there was no result, the prize does not already exist
	        if(answer.getInt(1) == 0) {
	        	System.out.print("Enter prize description: ");
		        String description = sc.nextLine(); // Get the prize description from user input
	        	
	        	System.out.print("Enter ticketCost for the new prize: ");
		        String cost = sc.nextLine(); // Get the tokenCost from user input
		        
		        System.out.print("Enter inventory amount for the new prize: ");
		        String amount = sc.nextLine(); // Get the inventoryAmount from user input
				
		        // Query to add new prize to Prize table
		        String query = "INSERT INTO jennyyu.Prize(prizeID, description, ticketCost, inventoryCount)"
		        		+ "VALUES("+PID+", '"+description+"',"+cost+", "+amount+")";
			
		        answer = stmt.executeQuery(query); // Execute query
		        System.out.println("\nNew prize added.");
	        }
	        
	        else {
	        	// Prize already exists, add one more to the inventory count
	        	System.out.println("\nPrize already exists. Adding one more to the inventory count...");
	        	
	        	// Query to add one to the specified prize using prizeID
	        	String update = "UPDATE jennyyu.Prize SET inventoryCount = inventoryCount+1 WHERE prizeID = "+PID;
		        answer = stmt.executeQuery(update); // Execute query
		        System.out.println("Prize added.");
	        }
	        
	        System.out.println();
			
		} catch (SQLException e) {
			System.err.println("*** SQLException:  " + "Could not fetch query results.");
			System.err.println("\tMessage:   " + e.getMessage());
			System.err.println("\tSQLState:  " + e.getSQLState());
			System.err.println("\tErrorCode: " + e.getErrorCode());
			System.exit(-1);
		}
	}
	
	
	/*
	 * Pre-condition: Needs the Prize and PrizeRedemption database to be set up 
	 * in Oracle.
	 * Post-condition: Called when the user wants to delete a prize. Checks if the 
	 * prizeID exits in the Prize table. If it does, delete the prize from the 
	 * PrizeRedemption table first since it is a foreign key and then delete the 
	 * prize from the Prize table.
	 * 
	 * Params: dbconn - Connection
	 *         stmt - Statement
	 *         answer - ResultSet
	 *         
	 * Purpose: Asks for user input for prizeID for prize to delete. Checks if the
	 * prize exists in the Prize table. If it doesn't exist, print error. If it does
	 * exist, delete prize with specified prizeID from PrizeRedemption table since it
	 * uses prizeID as a foreign key. Then delete prize with specified prizeID from
	 * the Prize table.
	 * 
	 */
	private static void deletePrize(Connection dbconn, Statement stmt, ResultSet answer) {
		try {
			stmt = dbconn.createStatement(); // Create statement
			Scanner sc = new Scanner(System.in); // Create a new scanner to take input
			
			System.out.print("Enter prizeID of the prize to delete: ");
	        String PID = sc.nextLine(); // Get the prizeID from user input
	        
	        // Query to check if the prize from corresponding prizeID exists in the Prize table
	        String checkForPrize = "SELECT COUNT(*) FROM jennyyu.Prize WHERE prizeID = "+PID;
	        answer = stmt.executeQuery(checkForPrize); // Execute the query
	        answer.next();
	        
	        // If there was no result, the prize to delete does not exist
	        if(answer.getInt(1) == 0) {
	        	System.out.println("\nPrize does not exist.");			
	        }
	        
	        else {
	        	// Query to delete prize from PrizeRedemption based on prizeID
	        	String deleteFromPrizeRedemption = "DELETE from jennyyu.PrizeRedemption where prizeID = "+PID;
		        answer = stmt.executeQuery(deleteFromPrizeRedemption); // Execute the query

		        // Query to delete prize from Prize based on prizeID
	        	String deleteFromPrize = "DELETE from jennyyu.Prize where prizeID = "+PID;
	        	answer = stmt.executeQuery(deleteFromPrize); // Execute the query
	        	
	        	System.out.println("\nPrize deleted.");
	        }
	        
	        System.out.println();
			
		} catch (SQLException e) {
			System.err.println("*** SQLException:  " + "Could not fetch query results.");
			System.err.println("\tMessage:   " + e.getMessage());
			System.err.println("\tSQLState:  " + e.getSQLState());
			System.err.println("\tErrorCode: " + e.getErrorCode());
			System.exit(-1);
		}
	}
	
	
	/*
	 * Pre-condition: Needs the databases to be set up in Oracle. 
	 * Post-condition: Runs the program to take continuous user input and 
	 * execute the corresponding query.
	 * 
	 * Params: args = String[]
	 *         
	 * Purpose: Connects the user to Oracle using their username and password.
	 * Prints out the menu options of queries for the user to choose from and 
	 * then takes continuous user input for which query they want to execute. 
	 * Calls the corresponding functions for each query and prints the results
	 * to the screen. Typing "3" will exit the program. 
	 * 
	 */
	public static void main(String[] args) {		
		final String oracleURL = // Magic lectura -> aloe access spell
				"jdbc:oracle:thin:@aloe.cs.arizona.edu:1521:oracle";
		
		String username = null, // Oracle DBMS username
				password = null; // Oracle DBMS password

		if (args.length == 2) { // get username/password from cmd line args
			username = args[0];
			password = args[1];
		} 
		else {
			System.out.println("\nUsage:  java JDBC <username> <password>\n"
					+ "    where <username> is your Oracle DBMS" + " username,\n    and <password> is your Oracle"
					+ " password (not your system password).\n");
			System.exit(-1);
		}

		// load the (Oracle) JDBC driver by initializing its base
		// class, 'oracle.jdbc.OracleDriver'.
		try {
			Class.forName("oracle.jdbc.OracleDriver");

		} catch (ClassNotFoundException e) {
			System.err.println("*** ClassNotFoundException:  " + "Error loading Oracle JDBC driver.  \n"
					+ "\tPerhaps the driver is not on the Classpath?");
			System.exit(-1);
		}

		// make and return a database connection to the user's
		// Oracle database
		Connection dbconn = null;

		try {
			dbconn = DriverManager.getConnection(oracleURL, username, password);

		} catch (SQLException e) {
			System.err.println("*** SQLException:  " + "Could not open JDBC connection.");
			System.err.println("\tMessage:   " + e.getMessage());
			System.err.println("\tSQLState:  " + e.getSQLState());
			System.err.println("\tErrorCode: " + e.getErrorCode());
			System.exit(-1);
		}

		// Send the query to the DBMS, and get and display the results
		Statement stmt = null; // query stmt
		ResultSet answer = null; // answer after running query

		try {
			// Creates new scanner to take user input
	        Scanner sc = new Scanner(System.in);
	        	        
	        // Print out the menu with the query options
			System.out.println("\nPlease make a selection:\n");
			System.out.println("1. Add prize");
			System.out.println("2. Delete prize");
			System.out.println("3. Exit\n");
			
			String input = sc.nextLine(); // Get the user input
			// Keep getting input 
			while(true) {
				// Input is '3', exit the program
				if(input.equals("3")) {
					break;
				}
				
				// Input is not a valid option, print error message
				else if(!input.equals("1") && !input.equals("2") && !input.equals("3")) {
					System.out.println("\""+input+"\" not a valid query option\n");
		            input = sc.nextLine(); // Get the next input
				}
				
				// Input is '1', run the first query - addPrize
				else if(input.equals("1")) {
					addPrize(dbconn, stmt, answer);
		            input = sc.nextLine(); // Get the next input
				}
				
				// Input is '2', run the second query - deletePrize
				else if(input.equals("2")) {
					deletePrize(dbconn, stmt, answer);
		            input = sc.nextLine(); // Get the next input
				}
			}
	        
			sc.close(); // Close the scanner
			// Shut down the connection to the DBMS.
			if(stmt != null) {
				stmt.close();
			}
			dbconn.close();

		} catch (SQLException e) {
			System.err.println("*** SQLException:  " + "Could not fetch query results.");
			System.err.println("\tMessage:   " + e.getMessage());
			System.err.println("\tSQLState:  " + e.getSQLState());
			System.err.println("\tErrorCode: " + e.getErrorCode());
			System.exit(-1);
		}
	}

}
