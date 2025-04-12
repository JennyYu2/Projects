package model;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * Serializes and deserialzes all files that we need to save such as the users
 * and the stats of each user.
 * 
 * @author Josh Samadder, Jenny Yu, Ricky Su, Chang Chia En
 *
 */

public class Serialize {
	private HashMap<String, String> newUsers;
	private ArrayList<SudokuAccount> newStats;

	/**
	 * Serializes a new user into our file of users
	 * 
	 * @param map - A hashmap that contains the usernames of every user that has
	 *            created an account in Slaydoku
	 */
	public void serializeUsers(HashMap<String, String> map) {
		try {
			FileOutputStream fileOut = new FileOutputStream("Users");
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(map);
			out.close();
			fileOut.close();
		} catch (IOException i) {
			System.out.println("Error");
		}
	}

	/**
	 * Deserializes the file of users into a hashmap
	 * 
	 * @return newUsers - A hashmap that contains every user
	 */
	@SuppressWarnings("unchecked")
	public HashMap<String, String> deserializeUsers() {
		try {
			FileInputStream file = new FileInputStream("Users");
			ObjectInputStream in = new ObjectInputStream(file);

			try {
				newUsers = (HashMap<String, String>) in.readObject();
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
			file.close();
			in.close();

		} catch (IOException i) {
			System.out.println("no map file???");
		}

		return newUsers;
	}

	/**
	 * Serializes the stats for each user
	 * 
	 * @param map - The list of accounts that has their own stats
	 */
	public void serializeStats(ArrayList<SudokuAccount> map) {
		try {
			FileOutputStream fileOut = new FileOutputStream("Stats");
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(map);
			out.close();
			fileOut.close();
		} catch (IOException i) {
			System.out.println("Error");
		}
	}

	/**
	 * Deserializes the accounts into an arraylist
	 * 
	 * @return newStats - An arraylist that contains each account and their stats
	 */
	@SuppressWarnings("unchecked")
	public ArrayList<SudokuAccount> deserializeStats() {
		try {
			FileInputStream file = new FileInputStream("Stats");
			ObjectInputStream in = new ObjectInputStream(file);
			try {
				newStats = (ArrayList<SudokuAccount>) in.readObject();
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
			file.close();
			in.close();
		} catch (IOException i) {
			System.out.println("no map file???");
		}
		return newStats;
	}

}
