import java.sql.*;
import java.util.Scanner;

public class Project {

    private static final String oracleURL = "jdbc:oracle:thin:@aloe.cs.arizona.edu:1521:oracle";
    private static Connection dbconn;

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.print("Enter your Oracle DBMS username: ");
            String username = scanner.nextLine();
            System.out.print("Enter your Oracle password: ");
            String password = scanner.nextLine();

            Class.forName("oracle.jdbc.OracleDriver");
            dbconn = DriverManager.getConnection(oracleURL, username, password);
            dbconn.setAutoCommit(false);  // Set autoCommit to false once for all

            System.out.println("Connected to the database successfully.");

            boolean exitProgram = false;
            while (!exitProgram) {
                System.out.println("\nChoose your role:");
                System.out.println("1. Database Admin");
                System.out.println("2. Customer");
                System.out.println("3. Queries");
                System.out.println("4. Exit Program");
                System.out.print("Enter your choice: ");
                int role = Integer.parseInt(scanner.nextLine());

                switch (role) {
                    case 1:
                        adminOperations(scanner);
                        break;
                    case 2:
                        customerOperations(scanner);
                        break;
                    case 3:
                        runQueries(scanner);
                        break;
                    case 4:
                        exitProgram = true;  // Set flag to exit while loop and program
                        break;
                    default:
                        System.out.println("Invalid role selected. Please try again.");
                }
            }

            dbconn.close();
            System.out.println("Exiting program.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    private static void adminOperations(Scanner scanner) throws SQLException {
        while (true) {
            System.out.println("\n0. <-- to Main Menu");
            System.out.println("Member Operations:");
            System.out.println("1. Add Member");
            System.out.println("2. Update Member");
            System.out.println("3. Delete Member");
            System.out.println("Game Operations:");
            System.out.println("4. Add Game");
            System.out.println("5. Delete Game");
            System.out.println("Prize Operations:");
            System.out.println("6. Add Prize");
            System.out.println("7. Delete Prize");

            System.out.print("Choose an option: ");
            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 0:
                    return;
                case 1:
                    addMember(scanner);
                    break;
                case 2:
                    updateMember(scanner);
                    break;
                case 3:
                    deleteMember(scanner);
                    break;
                case 4:
                    addGame(scanner);
                    break;
                case 5:
                    deleteGame(scanner);
                    break;
                case 6:
                    addOrUpdatePrize(scanner);
                    break;
                case 7:
                    deletePrize(scanner);
                    break;
                default:
                    System.out.println("Invalid choice. Please select a valid option.");
            }
        }
    }

    private static void customerOperations(Scanner scanner) throws SQLException {
        while (true) {
            System.out.println("\n0. <-- to Main Menu");
            System.out.println("Member Operations:");
            System.out.println("1. Update Your Account Info");
            System.out.println("2. Delete Your Account");
            System.out.println("3. Redeem Prizes");
            System.out.println("4. Buy Tokens");
            System.out.print("Choose an option: ");
            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 0:
                    return;
                case 1:
                    updateMember(scanner);
                    break;
                case 2:
                    deleteMember(scanner);
                    break;
                case 3:
                    redeemPrizes(scanner);
                    break;
                case 4:
                    buyTokens(scanner);
                    break;
                default:
                    System.out.println("Invalid choice. Please select a valid option.");
            }
        }
    }

    private static void addMember(Scanner scanner) throws SQLException {
        System.out.print("Enter Member ID: ");
        String mid = scanner.nextLine();
        System.out.print("Enter Name: ");
        String name = scanner.nextLine();
        System.out.print("Enter Phone Number: ");
        String phoneNo = scanner.nextLine();
        System.out.print("Enter Address: ");
        String address = scanner.nextLine();
        System.out.print("Enter Member Tier: ");
        String tier = scanner.nextLine();
        System.out.print("Enter Total Spent ($): ");
        double totalSpent = scanner.nextDouble();
        System.out.print("Enter Total Tickets: ");
        int totalTickets = scanner.nextInt();
        scanner.nextLine();  // Consume newline

        String sql = "INSERT INTO hamadayaz.Member (MID, name, phoneNo, address, tier, totalSpent, totalTickets) " +
                "VALUES (?, ?, ?, ?, ?, ?, ?)";
        try (PreparedStatement pstmt = dbconn.prepareStatement(sql)) {
            pstmt.setString(1, mid);
            pstmt.setString(2, name);
            pstmt.setString(3, phoneNo);
            pstmt.setString(4, address);
            pstmt.setString(5, tier);
            pstmt.setDouble(6, totalSpent);
            pstmt.setInt(7, totalTickets);
            int count = pstmt.executeUpdate();
            System.out.println(count + " member(s) added.");
        }
    }

    private static void updateMember(Scanner scanner) throws SQLException {
        System.out.print("Enter Member ID to update: ");
        String MID = scanner.nextLine();
        System.out.print("Enter new Name: ");
        String name = scanner.nextLine();
        System.out.print("Enter new Phone Number: ");
        String phoneNo = scanner.nextLine();
        System.out.print("Enter new Address: ");
        String address = scanner.nextLine();
        System.out.print("Enter new Member Tier: ");
        String tier = scanner.nextLine();

        String sql = "UPDATE hamadayaz.Member SET name = ?, phoneNo = ?, address = ?, tier = ? WHERE MID = ?";
        try (PreparedStatement pstmt = dbconn.prepareStatement(sql)) {
            pstmt.setString(1, name);
            pstmt.setString(2, phoneNo);
            pstmt.setString(3, address);
            pstmt.setString(4, tier);
            pstmt.setString(5, MID);
            pstmt.executeUpdate();
            System.out.println("Member updated successfully.");
        }
    }

    private static void deleteMember(Scanner scanner) throws SQLException {
        System.out.print("Enter Member ID to delete: ");
        String MID = scanner.nextLine();

        try {
            String sqlCheckTickets = "SELECT totalTickets FROM hamadayaz.Member WHERE MID = ?";
            PreparedStatement pstmt = dbconn.prepareStatement(sqlCheckTickets);
            pstmt.setString(1, MID);
            ResultSet rs = pstmt.executeQuery();

            if (rs.next()) {
                int totalTickets = rs.getInt("totalTickets");
                if (totalTickets > 10) {
                    manageTicketRedemption(scanner, MID, totalTickets);
                } else {
                    System.out.println("Member has fewer than 10 tickets, they can be deleted directly.");
                    proceedToDeleteMember(MID);
                }
            } else {
                System.out.println("No member found with ID: " + MID);
            }
        } catch (SQLException e) {
            System.out.println("Transaction failed: " + e.getMessage());
            dbconn.rollback();
            throw e;
        }
    }

    private static void manageTicketRedemption(Scanner scanner, String MID, int totalTickets) throws SQLException {
        while (totalTickets > 10) {
            System.out.println("Member has " + totalTickets + " tickets available for redemption:");
            if (listAndRedeemPrizes(scanner, MID, totalTickets)) {
                System.out.println("No prizes were redeemed. Exiting redemption process.");
                return;
            }
            totalTickets = updateMemberTicketCount(MID);
        }
        proceedToDeleteMember(MID);
    }

    private static boolean listAndRedeemPrizes(Scanner scanner, String MID, int totalTickets) throws SQLException {
        String sql = "SELECT PrizeID, description, ticketCost FROM hamadayaz.Prize WHERE ticketCost <= ? AND inventoryCount > 0 ORDER BY ticketCost";
        PreparedStatement pstmt = dbconn.prepareStatement(sql);
        pstmt.setInt(1, totalTickets);
        ResultSet rs = pstmt.executeQuery();

        boolean hasPrizes = false;
        while (rs.next()) {
            hasPrizes = true;
            String prizeID = rs.getString("PrizeID");
            String description = rs.getString("description");
            int ticketCost = rs.getInt("ticketCost");
            System.out.println("PrizeID: " + prizeID + ", Description: " + description + ", Ticket Cost: " + ticketCost);
        }

        if (!hasPrizes) {
            System.out.println("No prizes available for the current ticket count.");
            return true;
        }

        System.out.print("Enter Prize ID to redeem (or type 'skip' to cancel): ");
        String prizeId = scanner.nextLine();
        if ("skip".equalsIgnoreCase(prizeId)) {
            return true;
        }

        return !redeemSelectedPrize(MID, prizeId);
    }

    private static boolean redeemSelectedPrize(String MID, String prizeId) throws SQLException {
        String sql = "SELECT ticketCost, inventoryCount FROM hamadayaz.Prize WHERE PrizeID = ? AND inventoryCount > 0";
        PreparedStatement pstmt = dbconn.prepareStatement(sql);
        pstmt.setString(1, prizeId);
        ResultSet rs = pstmt.executeQuery();

        if (rs.next()) {
            int ticketCost = rs.getInt("ticketCost");
            int inventoryCount = rs.getInt("inventoryCount");

            if (inventoryCount > 0) {
                // Update Prize Inventory
                sql = "UPDATE hamadayaz.Prize SET inventoryCount = inventoryCount - 1 WHERE PrizeID = ?";
                pstmt = dbconn.prepareStatement(sql);
                pstmt.setString(1, prizeId);
                pstmt.executeUpdate();

                // Update Member Tickets
                sql = "UPDATE hamadayaz.Member SET totalTickets = totalTickets - ? WHERE MID = ?";
                pstmt = dbconn.prepareStatement(sql);
                pstmt.setInt(1, ticketCost);
                pstmt.setString(2, MID);
                pstmt.executeUpdate();

                // Record the transaction without ticketsSpent
                sql = "INSERT INTO hamadayaz.PrizeRedemption (XactID, MID, PrizeID, xactDate) VALUES (seq_prize_redemption.nextval, ?, ?, CURRENT_DATE)";
                pstmt = dbconn.prepareStatement(sql);
                pstmt.setString(1, MID);
                pstmt.setString(2, prizeId);
                pstmt.executeUpdate();

                dbconn.commit();
                System.out.println("Prize redeemed successfully.");
                return true;
            } else {
                System.out.println("Selected prize cannot be redeemed due to insufficient inventory.");
                return false;
            }
        } else {
            System.out.println("Selected prize not found or inventory is zero.");
            return false;
        }
    }

    
    private static int updateMemberTicketCount(String MID) throws SQLException {
        String sql = "SELECT totalTickets FROM hamadayaz.Member WHERE MID = ?";
        PreparedStatement pstmt = dbconn.prepareStatement(sql);
        pstmt.setString(1, MID);
        ResultSet rs = pstmt.executeQuery();
        if (rs.next()) {
            return rs.getInt("totalTickets");
        }
        return 0;  // Default if no data found
    }

    private static void proceedToDeleteMember(String MID) throws SQLException {
        try {
            // Delete related records from all dependent tables
            deleteRelatedRecords(MID);

            // Finally, delete the member
            String sqlDeleteMember = "DELETE FROM hamadayaz.Member WHERE MID = ?";
            try (PreparedStatement pstmtDelete = dbconn.prepareStatement(sqlDeleteMember)) {
                pstmtDelete.setString(1, MID);
                int affectedRows = pstmtDelete.executeUpdate();
                if (affectedRows > 0) {
                    System.out.println("Member deleted successfully.");
                    dbconn.commit(); // Commit all changes if everything is successful
                } else {
                    System.out.println("Failed to delete member. No member found with ID: " + MID);
                    dbconn.rollback(); // Rollback if the member does not exist
                }
            }
        } catch (SQLException e) {
            System.out.println("Error during deletion: " + e.getMessage());
            dbconn.rollback(); // Rollback on any error during the deletion process
            throw e;
        }
    }

    private static void deleteRelatedRecords(String MID) throws SQLException {
        // List of related tables
        String[] relatedTables = new String[] { "PrizeRedemption", "Coupon", "TokenPurchase", "Gameplay" };
        for (String table : relatedTables) {
            String sqlDelete = "DELETE FROM hamadayaz." + table + " WHERE MID = ?";
            try (PreparedStatement pstmt = dbconn.prepareStatement(sqlDelete)) {
                pstmt.setString(1, MID);
                pstmt.executeUpdate(); // Execute the delete command for each table
            }
        }
    }

    private static void addGame(Scanner scanner) throws SQLException {
        System.out.print("Enter Game ID: ");
        String gid = scanner.nextLine();
        System.out.print("Enter Game Name: ");
        String name = scanner.nextLine();
        System.out.print("Enter Token Cost: ");
        int tokenCost = scanner.nextInt();
        System.out.print("Enter Factor: ");
        int factor = scanner.nextInt();
        scanner.nextLine();  // Consume the newline

        String sql = "INSERT INTO hamadayaz.Game (GID, name, tokenCost, factor) VALUES (?, ?, ?, ?)";
        try (PreparedStatement pstmt = dbconn.prepareStatement(sql)) {
            pstmt.setString(1, gid);
            pstmt.setString(2, name);
            pstmt.setInt(3, tokenCost);
            pstmt.setInt(4, factor);
            int count = pstmt.executeUpdate();
            dbconn.commit();  // Commit the transaction
            System.out.println(count + " game(s) added.");
        } catch (SQLException e) {
            System.err.println("Error adding game: " + e.getMessage());
            dbconn.rollback();  // Rollback on error
            throw e;
        }
    }

    private static void deleteGame(Scanner scanner) throws SQLException {
        System.out.print("Enter Game ID to delete: ");
        String gid = scanner.nextLine();

        try {
            // Start by deleting gameplay records for the game
            String sqlDeleteGameplay = "DELETE FROM hamadayaz.GamePlay WHERE GID = ?";
            try (PreparedStatement pstmtGameplay = dbconn.prepareStatement(sqlDeleteGameplay)) {
                pstmtGameplay.setString(1, gid);
                pstmtGameplay.executeUpdate();  // Execute and ignore the row count for gameplay records
            }

            // Now, delete the game itself
            String sqlDeleteGame = "DELETE FROM hamadayaz.Game WHERE GID = ?";
            try (PreparedStatement pstmtGame = dbconn.prepareStatement(sqlDeleteGame)) {
                pstmtGame.setString(1, gid);
                int gameAffectedRows = pstmtGame.executeUpdate();

                if (gameAffectedRows > 0) {
                    dbconn.commit();  // Commit the transaction if game deletion is successful
                    System.out.println("Game and all associated gameplay records deleted successfully.");
                } else {
                    System.out.println("No game found with ID: " + gid + ", or game is still referenced in gameplay records.");
                    dbconn.rollback();  // Rollback if the game does not exist or other issues occur
                }
            }
        } catch (SQLException e) {
            System.err.println("Error deleting game: " + e.getMessage());
            dbconn.rollback();  // Rollback on error
            throw e;
        }
    }


    private static void redeemPrizes(Scanner scanner) throws SQLException {
        System.out.print("Enter Your Member ID: ");
        String MID = scanner.nextLine();
        try {
            // Fetch the total number of tickets the member has
            String sql = "SELECT totalTickets FROM hamadayaz.Member WHERE MID = ?";
            PreparedStatement pstmt = dbconn.prepareStatement(sql);
            pstmt.setString(1, MID);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                int totalTickets = rs.getInt("totalTickets");
                if (totalTickets > 0) {
                    System.out.println("You have " + totalTickets + " tickets. Redeeming prizes...");
                    if (listAndRedeemPrizes(scanner, MID, totalTickets)) {
                        System.out.println("No prizes were redeemed.");
                    }
                } else {
                    System.out.println("You do not have enough tickets to redeem any prizes.");
                }
            } else {
                System.out.println("Member ID not found. Please try again.");
            }
        } catch (SQLException e) {
            System.out.println("An error occurred: " + e.getMessage());
            dbconn.rollback();
        }
    }

    private static void buyTokens(Scanner scanner) throws SQLException {
        System.out.print("Enter Your Member ID: ");
        String MID = scanner.nextLine();
        System.out.print("Enter amount to spend on tokens ($): ");
        double amountSpent = scanner.nextDouble();
        scanner.nextLine(); // Clear the scanner buffer

        // Retrieve member details to calculate new totals and discounts
        String memberSql = "SELECT totalSpent, totalTickets, tier FROM hamadayaz.Member WHERE MID = ?";
        PreparedStatement pstmt = dbconn.prepareStatement(memberSql);
        pstmt.setString(1, MID);
        ResultSet rs = pstmt.executeQuery();

        if (rs.next()) {
            double currentSpent = rs.getDouble("totalSpent");
            int currentTickets = rs.getInt("totalTickets");
            String currentTier = rs.getString("tier");

            // Calculate new spending total
            double newTotalSpent = currentSpent + amountSpent;

            // Check for tier updates and calculate discount and bonus tickets
            String newTier = currentTier;
            double discount = 0.0;
            int bonusTickets = 0;

            if (newTotalSpent >= 500) {
                newTier = "Diamond";
                discount = 0.20; // 20% discount for Diamond members
                if (!"Diamond".equals(currentTier)) {
                    bonusTickets = (currentSpent < 250) ? 15000 : 10000; // Add difference if upgrading from Gold or None
                }
            } else if (newTotalSpent >= 250 && !"Gold".equals(currentTier) && !"Diamond".equals(currentTier)) {
                newTier = "Gold";
                discount = 0.10; // 10% discount for Gold members
                bonusTickets = 5000; // Bonus for reaching Gold
            }

            // Calculate the total new tickets
            int totalNewTickets = currentTickets + bonusTickets;

            // Calculate discounted amount and tokens purchased
            double discountedAmount = amountSpent * (1 - discount);
            int tokensPurchased = (int) (discountedAmount * 100); // Example: $1 = 100 tokens

            // Update member records with new totals, tickets, and tier
            String updateSql = "UPDATE hamadayaz.Member SET totalSpent = ?, totalTickets = ?, tier = ? WHERE MID = ?";
            PreparedStatement updateStmt = dbconn.prepareStatement(updateSql);
            updateStmt.setDouble(1, newTotalSpent);
            updateStmt.setInt(2, totalNewTickets);
            updateStmt.setString(3, newTier);
            updateStmt.setString(4, MID);
            updateStmt.executeUpdate();

            // Record the token purchase transaction
            String purchaseSql = "INSERT INTO hamadayaz.TokenPurchase (PID, MID, tokenNo, purchaseDate, amountSpent) VALUES (seq_token_purchase.nextval, ?, ?, CURRENT_DATE, ?)";
            PreparedStatement purchaseStmt = dbconn.prepareStatement(purchaseSql);
            purchaseStmt.setString(1, MID);
            purchaseStmt.setInt(2, tokensPurchased);
            purchaseStmt.setDouble(3, amountSpent);
            purchaseStmt.executeUpdate();

            dbconn.commit();
            System.out.println("Tokens purchased successfully. Total spent: $" + newTotalSpent + ", Tickets awarded: " + bonusTickets + ", New Tier: " + newTier);
        } else {
            System.out.println("Member ID not found.");
        }
    }

    private static void addOrUpdatePrize(Scanner scanner) throws SQLException {
        System.out.print("Enter Prize ID: ");
        String prizeID = scanner.nextLine();

        String sqlSelect = "SELECT * FROM hamadayaz.Prize WHERE prizeID = ?";
        PreparedStatement selectStmt = dbconn.prepareStatement(sqlSelect);
        selectStmt.setString(1, prizeID);
        ResultSet rs = selectStmt.executeQuery();

        if (rs.next()) {
            System.out.print("Prize already exists. Enter additional inventory to add: ");
            int additionalInventory = scanner.nextInt();
            scanner.nextLine(); // Consume newline left-over

            int newInventory = rs.getInt("inventoryCount") + additionalInventory;
            String sqlUpdate = "UPDATE hamadayaz.Prize SET inventoryCount = ? WHERE prizeID = ?";
            PreparedStatement updateStmt = dbconn.prepareStatement(sqlUpdate);
            updateStmt.setInt(1, newInventory);
            updateStmt.setString(2, prizeID);
            updateStmt.executeUpdate();
            System.out.println("Updated inventory for prize ID: " + prizeID);
        } else {
            System.out.print("Enter Description: ");
            String description = scanner.nextLine();
            System.out.print("Enter Ticket Cost: ");
            int ticketCost = scanner.nextInt();
            System.out.print("Enter Inventory Count: ");
            int inventoryCount = scanner.nextInt();
            scanner.nextLine(); // Consume newline left-over

            String sqlInsert = "INSERT INTO hamadayaz.Prize (prizeID, description, ticketCost, inventoryCount) VALUES (?, ?, ?, ?)";
            PreparedStatement insertStmt = dbconn.prepareStatement(sqlInsert);
            insertStmt.setString(1, prizeID);
            insertStmt.setString(2, description);
            insertStmt.setInt(3, ticketCost);
            insertStmt.setInt(4, inventoryCount);
            insertStmt.executeUpdate();
            System.out.println("New prize added.");
        }
        dbconn.commit();
    }

    private static void deletePrize(Scanner scanner) throws SQLException {
        System.out.print("Enter Prize ID to delete: ");
        String prizeID = scanner.nextLine();

        // Delete Prize Redemption records first
        String deleteRedemptionsSql = "DELETE FROM hamadayaz.PrizeRedemption WHERE PrizeID = ?";
        PreparedStatement deleteRedemptionsStmt = dbconn.prepareStatement(deleteRedemptionsSql);
        deleteRedemptionsStmt.setString(1, prizeID);
        int redemptionRowsAffected = deleteRedemptionsStmt.executeUpdate();

        System.out.println("Deleted " + redemptionRowsAffected + " prize redemption records for prize ID: " + prizeID);

        // Now delete the prize
        String deletePrizeSql = "DELETE FROM hamadayaz.Prize WHERE prizeID = ?";
        PreparedStatement deletePrizeStmt = dbconn.prepareStatement(deletePrizeSql);
        deletePrizeStmt.setString(1, prizeID);
        int prizeRowsAffected = deletePrizeStmt.executeUpdate();

        if (prizeRowsAffected > 0) {
            System.out.println("Prize deleted successfully.");
        } else {
            System.out.println("No prize found with ID: " + prizeID);
        }

        dbconn.commit();
    }

    private static void runQueries(Scanner scanner) throws SQLException {
        while (true) {
            System.out.println("\nSelect a query to run:");
            System.out.println("1. List all games and high scores");
            System.out.println("2. Members who spent $100 on tokens this month");
            System.out.println("3. Prizes a member can redeem");
            System.out.println("4. Highest game score by a member");
            System.out.println("0. Return to main menu");
            System.out.print("Enter your choice: ");
            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 0:
                    System.out.println("Returning to main menu...");
                    return;  // Exits the current method, thereby returning to the main menu.
                case 1:
                    Queries.query1(dbconn);
                    break;
                case 2:
                    Queries.query2(dbconn);
                    break;
                case 3:
                    System.out.print("Enter Member ID: ");
                    String MID = scanner.nextLine();
                    Queries.query3(MID, dbconn);
                    break;
                case 4:
                    System.out.print("Enter Member ID: ");
                    String memberID = scanner.nextLine();
                    Queries.query4(memberID, dbconn);
                    break;
                default:
                    System.out.println("Invalid choice. Please select a valid option.");
            }
        }
    }

}
