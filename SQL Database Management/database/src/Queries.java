
import java.sql.*;


public class Queries {
	
	// List all games in the arcade and the names of the members who have the current high scores.
	public static void query1(Connection dbconn) {
		Statement stmt = null;
		ResultSet ans = null;
		
		try {
			
			String query = "select GID, max(score) from jennyyu.GamePlay right join jennyyu.Game using (GID) group by GID";
			stmt = dbconn.createStatement();
			ans = stmt.executeQuery(query);
			
			System.out.println("High Scores:\n");
			System.out.printf("%-30s %-30s %-30s\n", "Game Name", "Member Name", "Score");
			System.out.println("-".repeat(90));
			while (ans.next()) {
				int score = ans.getInt("max(score)");
				int gid = ans.getInt("GID");
				
				
				String gameNameQuery = "select name from jennyyu.Game where GID = " + gid;
				stmt = dbconn.createStatement();
				ResultSet gameQuery = stmt.executeQuery(gameNameQuery);
				gameQuery.next();
				String gameName = gameQuery.getString("name");
				
				if (score > 0) {
					String memberNameQuery = "select name from jennyyu.Member join jennyyu.GamePlay using (MID) where score = " + score + " and GID = " + gid;
					stmt = dbconn.createStatement();
					ResultSet memberQuery = stmt.executeQuery(memberNameQuery);
					memberQuery.next();
					
					String memberName = memberQuery.getString("name");
					
					System.out.printf("%-30s %-30s %-30d\n", gameName, memberName, score);
				}
				
				else {
					System.out.printf("%-30s %-30s %-30s\n", gameName, "NULL", "NULL");
				}
				
			}
			System.out.println();
		}
		catch (SQLException e){
			System.err.println("*** SQLException:  "
                    + "Could not fetch query results.");
			System.err.println("\tMessage:   " + e.getMessage());
			System.err.println("\tSQLState:  " + e.getSQLState());
			System.err.println("\tErrorCode: " + e.getErrorCode());
			System.exit(-1);
		}
		
	
	}
	
	// Give the names and membership information of all members who have spent at least $100 on tokens in the past month.
	public static void query2(Connection dbconn){
		Statement stmt = null;
		ResultSet ans = null;
		
		try {
			String query = "select name, tier from jennyyu.Member where totalSpent >= 100";
			stmt = dbconn.createStatement();
			ans = stmt.executeQuery(query);
		
			System.out.println("-------- List member names and membership information of those who spent $100 or more --------\n");
			System.out.printf("%-30s %-30s\n", "Name", "Membership Tier");
			System.out.println("-".repeat(90));
			while(ans.next()) {
				String name = ans.getString("name");
				String tier = ans.getString("tier");
				
				System.out.printf("%-30s %-30s\n", name, tier);
			}
		}
		catch (SQLException e){
			System.err.println("*** SQLException:  "
                    + "Could not fetch query results.");
			System.err.println("\tMessage:   " + e.getMessage());
			System.err.println("\tSQLState:  " + e.getSQLState());
			System.err.println("\tErrorCode: " + e.getErrorCode());
			System.exit(-1);
		}
		System.out.println();
	}
	
	public static void query3(String MID, Connection dbconn){
		// First query gives us the number of tickets the member has
		Statement stmt1 = null;
		ResultSet ans1 = null;
		
		try {
			String ticketsQuery = "select totalTickets from jennyyu.Member where MID = " + MID;
			stmt1 = dbconn.createStatement();
			ans1 = stmt1.executeQuery(ticketsQuery);
		
			if (ans1.next()) {
				int ticketNo = ans1.getInt("totalTickets");
			
				Statement finalStmt = null;
				ResultSet finalResult = null;
			
				String prizesQuery = "select description from jennyyu.Prize where ticketCost <= " + ticketNo;
				finalStmt = dbconn.createStatement();
				finalResult = finalStmt.executeQuery(prizesQuery);
			
			
				if (finalResult.next()) {
					System.out.println("-------- Items this member can purchase with their tickets --------\n");
					System.out.println(finalResult.getString("description"));
					while(finalResult.next()) {
						String val = finalResult.getString("description");
						System.out.println(val);
					}
				}
				else {
					System.out.println("The member is too poor to buy any of the prizes LOL");
				}
			}
			else {
				System.out.println("Could not find member with the given member ID D:");
			}
			System.out.println();
		}
		catch (SQLException e){
			System.err.println("*** SQLException:  "
                    + "Could not fetch query results.");
			System.err.println("\tMessage:   " + e.getMessage());
			System.err.println("\tSQLState:  " + e.getSQLState());
			System.err.println("\tErrorCode: " + e.getErrorCode());
			System.exit(-1);
		}
	}
	
	public static void query4(String MID, Connection dbconn){
		Statement stmt = null;
		ResultSet ans = null;
		
		try {
			String query = "select jennyyu.Game.Name, score from jennyyu.Member join jennyyu.GamePlay using (MID) join jennyyu.Game using (GID) where MID = " + MID;
			stmt = dbconn.createStatement();
			ans = stmt.executeQuery(query);
		
			
			String memberQuery = "select name from jennyyu.Member where MID = " + MID;
			stmt = dbconn.createStatement();
			ResultSet memName = stmt.executeQuery(memberQuery);
			memName.next();
			
			if (ans.next()) {
				String gameName = ans.getString("name");
				int max = ans.getInt("score");
				String memberName = memName.getString("name");
				
				while (ans.next()) {
					int curScore = ans.getInt("score");
					if (curScore > max) {
						max = curScore;
						gameName = ans.getString("name");
					}
				}
				
				if (max > 0) {
					System.out.println("Member " + memberName + " has the highest score on " + gameName + " with a score of " + max);
				}
			
			}
			else {
				System.out.println("Member has not played any games!");
			}
			
			System.out.println();
		}
		catch (SQLException e){
			System.err.println("*** SQLException:  "
                    + "Could not fetch query results.");
			System.err.println("\tMessage:   " + e.getMessage());
			System.err.println("\tSQLState:  " + e.getSQLState());
			System.err.println("\tErrorCode: " + e.getErrorCode());
			System.exit(-1);
		}
	}
}
