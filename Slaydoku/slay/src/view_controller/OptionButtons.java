package view_controller;

import java.io.File;
import java.net.URI;
import java.util.ArrayList;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.stage.Stage;
import model.Serialize;
import model.SudokuAccount;
import model.SudokuGame;

/**
 * Creates the layout of various component of the main GUI that are not the
 * Slaydoku board. This includes a dropdown to change difficulties, buttons to
 * create a new game, to check the board, to give up, and more. Also adds the
 * timer to the GUI.
 * 
 * @author Josh Samadder, Jenny Yu, Ricky Su, Chang Chia En
 *
 */

public class OptionButtons extends GridPane {

	private Button clear;
	private Button newGame;
	private Button check;
	private Button stats;
	private Button pause;
	private Button solve;
	private final int EASY = 40;
	private final int MED = 48;
	private final int HARD = 52;	
//	private final int EASY = 10;
//	private final int MED = 10;
//	private final int HARD = 10;

	private Timer timer;
	private SudokuGame game;
	private LoginPane login;
	private SudokuBoard board;
	private Serialize serialized = new Serialize();
	private String name;

	private ArrayList<SudokuAccount> accounts;
	private SudokuAccount currAccount;

	private boolean gaveUp = false;

	// private SudokuBoard board;

	@SuppressWarnings("static-access")
	public OptionButtons(SudokuGame theGame, LoginPane theLogin, SudokuBoard theBoard) {
		game = theGame;
		login = theLogin;
		board = theBoard;

		this.setHgap(5);
		this.setVgap(5);
		Menu difficulty = new Menu("Difficulty");
		MenuItem diffEasy = new MenuItem("Easy");
		MenuItem diffMed = new MenuItem("Medium");
		MenuItem diffHard = new MenuItem("Hard");

		difficulty.getItems().addAll(diffEasy, diffMed, diffHard);
		MenuBar menu = new MenuBar();
		menu.getMenus().add(difficulty);

		timer = theGame.getTimer();
		this.add(menu, 4, 1);
		addButtons();
		this.add(timer, 32, 1);

		diffEasy.setOnAction(event -> {
			gaveUp = false;
			game.changeDifficulty(EASY);
			//System.out.println("easy");
			timer = game.getTimer();
			this.getChildren().removeIf(node -> this.getColumnIndex(node) == 32 && this.getRowIndex(node) == 1);
			this.add(timer, 32, 1);
			setButtonsClickable();
			updateGamesPlayed();
		});

		diffMed.setOnAction(event -> {
			gaveUp = false;
			game.changeDifficulty(MED);
			//System.out.println("meidum");
			timer = game.getTimer();
			this.getChildren().removeIf(node -> this.getColumnIndex(node) == 32 && this.getRowIndex(node) == 1);
			this.add(timer, 32, 1);
			setButtonsClickable();
			updateGamesPlayed();
		});

		diffHard.setOnAction(event -> {
			gaveUp = false;
			game.changeDifficulty(HARD);
			//System.out.println("hard");
			timer = game.getTimer();
			this.getChildren().removeIf(node -> this.getColumnIndex(node) == 32 && this.getRowIndex(node) == 1);
			this.add(timer, 32, 1);
			setButtonsClickable();
			updateGamesPlayed();
		});
	}

	private void setButtonsUnclickable() {
		clear.setDisable(true);
		check.setDisable(true);
		pause.setDisable(true);
		solve.setDisable(true);
	}
	
	private void setButtonsClickable() {
		clear.setDisable(false);
		check.setDisable(false);
		pause.setDisable(false);
		solve.setDisable(false);
	}
	
	
	private void updateGamesPlayed() {
		accounts = serialized.deserializeStats();
		if (login.getLoggedIn()) {
			name = login.getCurName();
			currAccount = findAccount();
			currAccount.addGame();
			serialized.serializeStats(accounts);
		}
	}

	@SuppressWarnings("static-access")
	private void addButtons() {
		clear = new Button("Clear Board");
		newGame = new Button("New Game");
		check = new Button("Check Board");
		stats = new Button("Stats");
		pause = new Button("Pause");
		solve = new Button("Give Up");

		this.add(clear, 11, 1);
		this.add(newGame, 13, 1);
		this.add(check, 15, 1);
		this.add(stats, 17, 1);
		this.add(solve, 19, 1);
		this.add(pause, 21, 1);

		stats.setOnAction(event -> {
			statAlert();
		});

		pause.setOnAction(event -> {
			pauseAlert();
			timer.resume();
		});

		newGame.setOnAction(event -> {
			gaveUp = false;
			int currentDifficulty = game.getCurrentDifficulty();
			game.startNewGame(9, currentDifficulty);
			timer = game.getTimer();
			this.getChildren().removeIf(node -> this.getColumnIndex(node) == 32 && this.getRowIndex(node) == 1);
			this.add(timer, 32, 1);
			setButtonsClickable();
			updateGamesPlayed();
		});

		check.setOnAction(event -> {
			checkInputs();
		});

		clear.setOnAction(event -> {
			game.clearChanges();
		});

		solve.setOnAction(event -> {
			game.solveBoard();
			gaveUp = true;
			timer.pause();
			setButtonsUnclickable();
		});
	}

	private void checkInputs() {
		System.out.println("check board");
		ArrayList<TextField> inputs = board.getSudokuBoard();
		int[][] solvedBoard = game.getSolvedBoard();
		int[][] unsolvedBoard = game.getBoard();
		int wrong = 0;
		int blank = 0;
		boolean isInt = true;

		for (int i = 0; i < inputs.size(); i++) {

			// index row
			int row = (i) / 9;
			// index col
			int col = (i) % 9;

			try {
				if(inputs.get(i).getText().trim().length() != 0) {
					int temp = Integer.parseInt(inputs.get(i).getText().trim());
				}

			} catch (NumberFormatException E) {
				//System.out.println("not a number");
				inputs.get(i).setStyle("-fx-background-radius: 0; -fx-text-fill: blue; -fx-background-color: #f68b83");
				isInt = false;
			}

			// If not empty and is a number
			if (inputs.get(i).getText().trim() != "" && isInt) {
				if (Integer.parseInt(inputs.get(i).getText().trim()) != solvedBoard[row][col]) {
					//System.out.println("the input is incorrect");
					wrong++;
					inputs.get(i).setStyle("-fx-background-radius: 0; -fx-text-fill: blue; -fx-background-color: #f68b83");
				} else {
					if (unsolvedBoard[row][col] == 0) {
						inputs.get(i).setStyle("-fx-background-radius: 0; -fx-text-fill: blue;");
					}
				}
			}

			// blank box
			else if(inputs.get(i).getText().trim().length() == 0) {
				inputs.get(i).setStyle("-fx-background-radius: 0; -fx-text-fill: blue;");
				blank++;
			}
		}

		// User wins the game
		if (wrong == 0 && blank == 0 && !gaveUp) {
			setButtonsUnclickable();
			playSong();
			winAlert();
			game.solveBoard();
			if (login.getLoggedIn()) {
				accounts = serialized.deserializeStats();
				name = login.getCurName();
				currAccount = findAccount();
				currAccount.addWin();
				int[] currTime = timer.getCurrentTime();
				currAccount.setBestTime(currTime);
				serialized.serializeStats(accounts);
			}
		}
	}

	private void playSong() {
		String path = "Songfiles/Studio_Project_V0.mp3";
		File file = new File(path);
		URI uri = file.toURI();

		Media media = new Media(uri.toString());
		MediaPlayer mediaPlayer = new MediaPlayer(media);
		mediaPlayer.play();
	}

	// Finds current SudokuAccount
	private SudokuAccount findAccount() {
		for (SudokuAccount account : accounts) {
			if (account.getName().equals(name)) {
				return account;
			}
		}
		return null;
	}

	private void statAlert() {
		Alert stats = new Alert(Alert.AlertType.INFORMATION);
		stats.setTitle("User stats");
		
		if (login.getLoggedIn()) {
			accounts = serialized.deserializeStats();
			name = login.getCurName();
			currAccount = findAccount();
			int h = currAccount.getBestTime()[0];
			int m = currAccount.getBestTime()[1];
			int s = currAccount.getBestTime()[2];

			if (h == 100) {
				h = 0;
			}
			if (m == 100) {
				m = 0;
			}

			if (s == 100) {
				s = 0;
			}

			stats.setHeaderText("Here are your stats:\n Best Time: " + h + "hr " + m + "m " + s + "s"
					+ "\n Games Played: " + currAccount.getGamesPlayed() + "\n Games won: " + currAccount.getWins());
		} else {
			stats.setHeaderText("Please log in to see stats");
		}
		stats.showAndWait();
	}

	private void winAlert() {
		Alert won = new Alert(Alert.AlertType.INFORMATION);
		Stage pauseStage = (Stage) won.getDialogPane().getScene().getWindow();
		pauseStage.getIcons().add(new Image("file:src/documents/nezuko.jpg"));
		timer.pause();

		won.setTitle("Won");
		won.setHeaderText("Slay girl! Way to go queen! You won!");
		Image image = new Image("file:src/documents/chicka.gif");
		ImageView iv = new ImageView(image);
		iv.setFitHeight(60);
		iv.setFitWidth(60);
		won.setGraphic(iv);

		won.showAndWait();
	}

	private void pauseAlert() {
		Alert stats = new Alert(Alert.AlertType.INFORMATION);
		Stage pauseStage = (Stage) stats.getDialogPane().getScene().getWindow();
		pauseStage.getIcons().add(new Image("file:src/documents/nezuko.jpg"));
		timer.pause();

		stats.setTitle("Pause");
		stats.setHeaderText("Game paused. Click OK to resume");

		stats.showAndWait();
	}

}
