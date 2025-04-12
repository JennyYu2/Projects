package model;

import java.util.Random;
import view_controller.Timer;

/**
 * The main state of the current game of Slaydoku. Some functionality include
 * creating a valid Slaydoku board and removing random values, setting the
 * difficulty of a Slaydoku game, and setting the timer when a new Slaydoku game
 * is created. Whenever the Slaydoku game is changed, such as creating a new
 * game, the view is changed.
 * 
 * @author Josh Samadder, Jenny Yu, Ricky Su, Chang Chia En
 *
 */

public class SudokuGame extends OurObservable {

	public int[][] board;
	public int[][] solvedBoard;
	private int N; // number of columns/rows.
	private int SRN; // square root of N
	private int missing; // No. Of missing digits
	private boolean loggedIn = false;
	private boolean didGiveUp = false;
	private boolean hasWon;
	private Timer timer;

	public SudokuGame(int N, int K) {
		startNewGame(N, K);
	}

	/**
	 * Changes the difficulty of the Slaydoku game. Whenever the difficulty is
	 * changed, we start a new Slaydoku game and the view is updated.
	 * 
	 * @param difficulty - A number that represents the number of values to remove
	 *                   from the Slaydoku game. The more values removed, the harder
	 *                   the game.
	 */
	public void changeDifficulty(int difficulty) {
		startNewGame(N, difficulty);
	}

	/**
	 * Clears from the current Slaydoku game any user changes and shows it on the
	 * view
	 */
	public void clearChanges() {
		notifyObservers(this);
	}

	/**
	 * Retrieves the current difficulty of the Slaydoku game.
	 * 
	 * @return missing - The number of values removed from the current Slaydoku
	 *         game.
	 */
	public int getCurrentDifficulty() {
		return this.missing;
	}

	/**
	 * Solves the board by setting the board of the current game to the board of the
	 * solved game. The solved board is displayed in the view. This is done when the
	 * user could not solve the board and gave up
	 */
	public void solveBoard() {
		board = solvedBoard;
		setDidGiveUp(true);
		notifyObservers(this);
	}

	/**
	 * Changes the value of didGiveUp to keep track of if the player gave up or not
	 * 
	 * @param giveUp - True if the user gave up and False otherwise
	 */
	public void setDidGiveUp(boolean giveUp) {
		didGiveUp = giveUp;
	}

	/**
	 * Retrieves the value of didGiveUp, which is True if the user gave up
	 * 
	 * @return didGiveUp - True if the user gave up, False otherwise
	 */
	public boolean getDidGiveUp() {
		return didGiveUp;
	}

	/**
	 * Changes the value of hasWon to keep track of if the player won or not
	 * 
	 * @param won - True if the user won the Slaydoku game, False otherwise
	 */
	public void setHasWon(boolean won) {
		hasWon = won;
	}

	/**
	 * Retrieves the value of hasWon, which is true if the user has won
	 * 
	 * @return hasWon - True if the user won the Slaydoku game, False otherwise
	 */
	public boolean getHasWon() {
		return hasWon;
	}

	/**
	 * Retrieves the solved Slaydoku board
	 * 
	 * @return solvedBoard - An integer array that has all values of the Slaydoku
	 *         board filled out
	 */
	public int[][] getSolvedBoard() {
		return solvedBoard;
	}

	/**
	 * This starts a new Slaydoku game. Fills the Slaydoku board and starts a new
	 * timer. The new game is then displayed to the user.
	 * 
	 * @param N - The number of rows and columns of the Slaydoku game
	 * @param K - The current difficulty of the Slaydoku game
	 */
	public void startNewGame(int N, int K) {
		this.N = N;
		this.missing = K;
		setHasWon(false);
		setDidGiveUp(false);

		Double temp = Math.sqrt(N);
		SRN = temp.intValue();
		board = new int[N][N];
		fillValues();

		//printSudoku();
		timer = new Timer();
		notifyObservers(this);
	}

	/**
	 * Retrieves the timer object of the current game
	 * 
	 * @return timer - The timer object that keeps track of how long the user takes
	 *         for the Slaydoku game
	 */
	public Timer getTimer() {
		return timer;
	}

	// Sudoku Generator
	private void fillValues() {
		// Fill the diagonal of SRN x SRN matrices
		fillDiagonal();

		// Fill remaining blocks
		fillRemaining(0, SRN);

		printSudoku();

		solvedBoard = new int[9][];
		for (int i = 0; i < 9; i++) {
			int[] aRow = board[i];
			solvedBoard[i] = new int[9];
			System.arraycopy(aRow, 0, solvedBoard[i], 0, 9);
		}

		// Remove values
		removeValues();
	}

	// Fill the diagonal SRN number of SRN x SRN matrices
	private void fillDiagonal() {
		for (int i = 0; i < N; i = i + SRN)
			fillBox(i, i);
	}

	// Returns false if given 3 x 3 block contains num.
	private boolean unUsedInBox(int rowStart, int colStart, int num) {
		for (int i = 0; i < SRN; i++) {
			for (int j = 0; j < SRN; j++) {
				if (board[rowStart + i][colStart + j] == num) {
					return false;
				}
			}
		}
		return true;
	}

	// Fill a 3 x 3 matrix.
	private void fillBox(int row, int col) {
		int num;
		for (int i = 0; i < SRN; i++) {
			for (int j = 0; j < SRN; j++) {
				do {
					num = randomGenerator(N);
				} while (!unUsedInBox(row, col, num));

				board[row + i][col + j] = num;
			}
		}
	}

	// Random generator
	private int randomGenerator(int num) {
		return (int) Math.floor((Math.random() * num + 1));
	}

	// Check if safe to put in cell
	private boolean CheckIfSafe(int i, int j, int num) {
		return (unUsedInRow(i, num) && unUsedInCol(j, num) && unUsedInBox(i - i % SRN, j - j % SRN, num));
	}

	// check in the row for existence
	private boolean unUsedInRow(int i, int num) {
		for (int j = 0; j < N; j++)
			if (board[i][j] == num)
				return false;
		return true;
	}

	// check in the row for existence
	private boolean unUsedInCol(int j, int num) {
		for (int i = 0; i < N; i++)
			if (board[i][j] == num)
				return false;
		return true;
	}

	/*
	 * A recursive function to fill remaining matrix
	 */
	private boolean fillRemaining(int i, int j) {
		if (j >= N && i < N - 1) {
			i = i + 1;
			j = 0;
		}

		if (i >= N && j >= N) {
			return true;
		}

		if (i < SRN) {
			if (j < SRN)
				j = SRN;
		}

		else if (i < N - SRN) {
			if (j == (int) (i / SRN) * SRN) {
				j = j + SRN;
			}
		}

		else {
			if (j == N - SRN) {
				i = i + 1;
				j = 0;
				if (i >= N) {
					return true;
				}
			}
		}

		// Recursively fills in the rest of the board
		for (int num = 1; num <= N; num++) {
			if (CheckIfSafe(i, j, num)) {
				board[i][j] = num;
				if (fillRemaining(i, j + 1)) {
					return true;
				}
				board[i][j] = 0;
			}
		}
		return false;
	}

	/*
	 * Remove the K no. of digits to complete game
	 */
	private void removeValues() {
		int count = missing;
		Random rand = new Random();

		while (count != 0) {
			int i = rand.nextInt(9);
			int j = rand.nextInt(9);

			if (board[i][j] != 0) {
				count--;
				board[i][j] = 0;
			}
		}
	}

	/**
	 * Retrieves the Slaydoku board of a new game without any changes
	 * 
	 * @return board - The initial Slaydoku game shown to the user when a new game
	 *         is created
	 */
	public int[][] getBoard() {
		return board;
	}

	/**
	 * If the user is logged in, then we set the boolean loggedIn to true
	 */
	public void isLoggedIn() {
		loggedIn = true;
	}

	/**
	 * Retrieves the value of loggedIn, which is true if the user is logged in
	 * 
	 * @return loggedIn - True if the user is logged in, False otherwise
	 */
	public boolean getLoggedIn() {
		return loggedIn;
	}

	/**
	 * Prints out a text version of the Slaydoku board
	 */
	public void printSudoku() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				System.out.print(board[i][j] + " ");
			System.out.println();
		}
		System.out.println();
	}

}