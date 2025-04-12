package model;

import java.io.Serializable;

/**
 * Each user that logs in to Slaydoku gets an account created. This account
 * keeps track of the username, the number of games played, and the best time
 * they had for a won game
 * 
 * @author Josh Samadder, Jenny Yu, Ricky Su, Chang Chia En
 *
 */

public class SudokuAccount implements Serializable {

	private static final long serialVersionUID = 1L;
	private String name;
	private double gamesPlayed;
	private int[] bestTime;
	private double gamesWon;

	public SudokuAccount(String userName) {
		name = userName;
		gamesPlayed = 1;
		bestTime = new int[] { 100, 100, 100 };
		gamesWon = 0;
	}

	/**
	 * Retrieves the name of the accounts
	 * 
	 * @return name - The username of the account
	 */
	public String getName() {
		return name;
	}

	/**
	 * Increases the number of games a user has played
	 */
	public void addGame() {
		gamesPlayed++;
	}

	/**
	 * Retrieves the number of games the user has played
	 * 
	 * @return gamesPlayed - The number of games the user has played
	 */
	public double getGamesPlayed() {
		return gamesPlayed;
	}

	/**
	 * Increases the number of wins when the user successfully completes a Slaydoku
	 * game
	 */
	public void addWin() {
		gamesWon++;
	}

	/**
	 * Retrieves the number of wins the user has
	 * 
	 * @return gamesWon - The number of wins the user has
	 */
	public double getWins() {
		return gamesWon;
	}

	/**
	 * Compares the hours, minutes, and seconds of the current time and the best
	 * time to see which time is faster. If the current time is better than the
	 * previous best time, then the best time is set to be the current time
	 * 
	 * @param time - An array that is expected to have the time in the format of
	 *             [hours, minutes, seconds].
	 * 
	 */
	public void setBestTime(int[] time) {

		if (time[0] < bestTime[0]) {
			bestTime = time;
		}

		// hours are the same
		else if (time[0] == bestTime[0]) {
			// check minutes
			if (time[1] < bestTime[1]) {
				bestTime = time;
			}

			// minutes are the same
			else if (time[1] == bestTime[1]) {
				// check seconds

				if (time[2] < bestTime[2]) {
					bestTime = time;
				}
			}
		}
	}

	/**
	 * Retrieves the user's best time
	 * 
	 * @return bestTime - The user's best time in completing a Slaydoku game
	 */
	public int[] getBestTime() {
		return bestTime;
	}

}
