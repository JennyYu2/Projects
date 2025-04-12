import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Scanner;
public class UI {

	public static void main(String[] args) throws SQLException{
		// Oracle connection (courtesy of Professor McCann)
		final String oracleURL = "jdbc:oracle:thin:@aloe.cs.arizona.edu:1521:oracle"; // The Oracle URL
		String username = null; // The user's Oracle username
		String password = null; // The user's Oracle password
				
		if (args.length == 2) {   
			username = args[0];
		    password = args[1];
		} 
				
		// Print out error if the user entered less than or more than two arguments
		else {
			System.out.println("\nUsage:  java JDBC <username> <password>\n"
		                       + "    where <username> is your Oracle DBMS"
		                       + " username,\n    and <password> is your Oracle"
		                       + " password (not your system password).\n");
			System.exit(-1);
		}
				
		// Load the driver
		try {
			Class.forName("oracle.jdbc.OracleDriver");
		} 
				
		catch (ClassNotFoundException e) {

			System.err.println("*** ClassNotFoundException:  "
		                + "Error loading Oracle JDBC driver.  \n"
		                + "\tPerhaps the driver is not on the Classpath?");
			System.exit(-1);

		}

		Connection dbconn = null; // The connection to Oracle

		// Print out error if we could not connect to the Oracle database
		try {
			dbconn = DriverManager.getConnection
		                     (oracleURL,username,password);

		} 
		catch (SQLException e) {
			System.err.println("*** SQLException:  "
		                + "Could not open JDBC connection.");
		    System.err.println("\tMessage:   " + e.getMessage());
		    System.err.println("\tSQLState:  " + e.getSQLState());
		    System.err.println("\tErrorCode: " + e.getErrorCode());
		    System.exit(-1);

		}
		
		Scanner kb = new Scanner(System.in); // The scanner for the user to type in input
		// Keep allowing user to execute queries until they want to exit
		while (true) {
			// Print out the menu
			System.out.println("Menu: Type in a number to execute the operation...");
			System.out.println("\t    1. Add/update/delete member");
			System.out.println("\t    2. Add/delete game");
			System.out.println("\t    3. Add/delete prize");
			System.out.println("\t    4. List all games in the arcade and the names of the members who have the current high scores.");
			System.out.println("\t    5. Give the names and membership information of all members who have spent at least $100 on tokens in the past month.");
			System.out.println("\t    6. For a given member, list all arcade rewards that they can purchase with their tickets.");
			System.out.println("\t    7. For a given member, get the game that they have the highest score in.");
			System.out.println("Alternatively, type 'e' or 'E' to exit...");
			
			String next = kb.next(); // Get the next input for the user
			
			System.out.println("\n");
			
			// Exit out of the loop if the user types in 'e' or 'E'
			if (next.equals("e") || next.equals("E")) {
				System.out.println("Exiting...");
				break;
			}
			else {
				int num; // Used to get the integer inputted by the user
							
				// Print out error if the input could not be parsed as an integer, which means the user typed in a string that
				// was not 'e' or 'E'
				try {
					num = Integer.parseInt(next);
				}
				catch (NumberFormatException e) {
					System.out.println("The input was not a number but was not 'e' or 'E' either :(\n\n");
					continue;
				}
							
				// Print out error message if the number inputted was not between 1 and 4
				if (num < 1 || num > 7) {
					System.out.println("Please select a valid option (input an integer between 1 and 7)\n\n");
					continue;
				}
				
				if (num == 4) {
					Queries.query1(dbconn);
				}
				else if (num == 5) {
					Queries.query2(dbconn);
				}
				else if (num == 6) {
					System.out.println("Enter member ID: ");
					String MID = kb.next();
					
					Queries.query3(MID, dbconn);
				}
				else {
					System.out.println("Enter member ID: ");
					String MID = kb.next();
					
					Queries.query4(MID, dbconn);
				}
			}
		}
		kb.close();
	}

}
