/*
 * Author: Josh Samadder
 * 
 * Purpose: Script to initialize tables
 */


import java.io.IOException;
import java.io.BufferedWriter;
import java.io.FileWriter;


public class InitTables {

	public static void createTableMember() throws IOException{
		
		BufferedWriter writer = new BufferedWriter(new FileWriter("createTableScripts/createMember.sql"));
		writer.write("CREATE TABLE beans.Member (");
		writer.newLine();
		
		writer.write("\tMID\tvarchar2(7) NOT NULL,");
		writer.newLine();
		
		writer.write("\tname\tvarchar2(100),");
		writer.newLine();
		
		writer.write("\tphoneNo\tvarchar2(13),");
		writer.newLine();
		
		writer.write("\taddress\tvarchar2(100),");
		writer.newLine();
		
		writer.write("\ttier\tvarchar(7),");
		writer.newLine();
		
		writer.write("\ttotalSpent\tnumber(8, 2),");
		writer.newLine();
		
		writer.write("\ttotalTickets\tinteger,");
		writer.newLine();
		
		writer.write("\tprimary key\t(MID)");
		writer.newLine();
		
		writer.write(");");
		writer.close();
	}
	
	public static void createTablePrizeRedemption() throws IOException{
		
		BufferedWriter writer = new BufferedWriter(new FileWriter("createtableScripts/createPrizeRedemption.sql"));
		writer.write("CREATE TABLE beans.PrizeRedemption (");
		writer.newLine();
		
		writer.write("\txactID\tvarchar2(7) NOT NULL,");
		writer.newLine();
		
		writer.write("\tMID\tvarchar2(7),");
		writer.newLine();
		
		writer.write("\tPrizeID\tvarchar2(7),");
		writer.newLine();
		
		writer.write("\txactDate\tdate,");
		writer.newLine();
		
		writer.write("\tticketsSpent\tinteger,");
		writer.newLine();
		
		writer.write("\tprimary key\t(xactID)");
		writer.newLine();
		
		writer.write(");");
		writer.close();
	}
	
	public static void createTablePrize() throws IOException{
		BufferedWriter writer = new BufferedWriter(new FileWriter("createTableScripts/createPrize.sql"));
		writer.write("CREATE TABLE beans.Prize (");
		writer.newLine();
		
		writer.write("\tprizeID\tvarchar2(7) NOT NULL,");
		writer.newLine();
		
		writer.write("\tdescription\tvarchar2(100),");
		writer.newLine();
		
		writer.write("\tticketCost\tinteger,");
		writer.newLine();
		
		writer.write("\tprimary key\t(prizeID)");
		writer.newLine();
		
		writer.write(");");
		writer.close();
	}
	
	public static void createTableTokenPurchase() throws IOException{
		BufferedWriter writer = new BufferedWriter(new FileWriter("createTableScripts/createTokenPurchase.sql"));
		writer.write("CREATE TABLE beans.TokenPurchase (");
		writer.newLine();
		
		writer.write("\tPID\tvarchar2(7) NOT NULL,");
		writer.newLine();
		
		writer.write("\tMID\tvarchar2(7),");
		writer.newLine();
		
		writer.write("\ttokenNo\tinteger,");
		writer.newLine();
		
		writer.write("\tpurchaseDate\tdate,");
		writer.newLine();
		
		writer.write("\tprimary key\t(PID)");
		writer.newLine();
		
		writer.write(");");
		writer.close();
	}
	
	public static void createTableCoupon() throws IOException{
		BufferedWriter writer = new BufferedWriter(new FileWriter("createTableScripts/createCoupon.sql"));
		writer.write("CREATE TABLE beans.Coupon (");
		writer.newLine();
		
		writer.write("\tCID\tvarchar2(7) NOT NULL,");
		writer.newLine();
		
		writer.write("\tMID\tvarchar2(7),");
		writer.newLine();
		
		writer.write("\tdescription\tvarchar2(100),");
		writer.newLine();
		
		writer.write("\texpirationDate\tdate,");
		writer.newLine();
		
		writer.write("\tprimary key\t(CID)");
		writer.newLine();
		
		writer.write(");");
		writer.close();
	}
	
	public static void createTableGame() throws IOException{
		BufferedWriter writer = new BufferedWriter(new FileWriter("createTableScripts/createGame.sql"));
		writer.write("CREATE TABLE beans.Game (");
		writer.newLine();
		
		writer.write("\tGID\tvarchar2(7) NOT NULL,");
		writer.newLine();
		
		writer.write("\tname\tvarchar2(100),");
		writer.newLine();
		
		writer.write("\ttokenCost\tinteger,");
		writer.newLine();
		
		writer.write("\tticketAmount\tinteger,");
		writer.newLine();
		
		writer.write("\tprimary key\t(GID)");
		writer.newLine();
		
		writer.write(");");
		writer.close();
	}
	
	public static void createTableGamePlay() throws IOException{
		BufferedWriter writer = new BufferedWriter(new FileWriter("createTableScripts/createGamePlay.sql"));
		writer.write("CREATE TABLE beans.GamePlay (");
		writer.newLine();
		
		writer.write("\tGameplayID\tvarchar2(7) NOT NULL,");
		writer.newLine();
		
		writer.write("\tGID\tvarchar2(7),");
		writer.newLine();
		
		writer.write("\tMID\tvarchar2(7),");
		writer.newLine();
		
		writer.write("\tscore\tinteger,");
		writer.newLine();
		
		writer.write("\tticketsEarned\tinteger,");
		writer.newLine();
		
		writer.write("\tdate\tdate,");
		writer.newLine();
		
		writer.write("\tprimary key\t(GameplayID)");
		writer.newLine();
		
		writer.write(");");
		writer.close();
	}
	
	public static void main(String[] args) throws IOException{
		createTableMember();
		createTablePrizeRedemption();
		createTablePrize();
		createTableTokenPurchase();
		createTableCoupon();
		createTableGame();
		createTableGamePlay();
	}

}
