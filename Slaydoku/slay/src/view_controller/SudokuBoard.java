package view_controller;

import java.util.ArrayList;

import javafx.geometry.Pos;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import model.*;

/**
 * The main Slaydoku board. Creates a 9x9 board of TextFields where the user can
 * enter their answers for the game. Also creates smaller TextFields (pencil
 * marks) where the user can enter their current guess for the blank space.
 * 
 * @author Josh Samadder, Jenny Yu, Ricky Su, Chang Chia En
 *
 */

public class SudokuBoard extends StackPane implements OurObserver {

	private ArrayList<TextField> grid;
	private ArrayList<GridPane> pencil;
	private ArrayList<StackPane> panes;
	private GridPane putPanes;
	private Canvas canvas;
	private GraphicsContext gc;
	private SudokuGame theGame;
	private int[][] theBoard;

	public SudokuBoard(SudokuGame game) {
		theGame = game;
		this.setStyle("-fx-background-color: #ceecfd");
		canvas = new Canvas(700, 440);
		this.getChildren().add(canvas);
		gc = canvas.getGraphicsContext2D();

		// Makes the ArrayList for board
		createTextFields();

		// Makes ArrayList of GridPanes
		createPencilMarks();

		// Makes the ArrayList of StackPanes
		createPanes();

		// Puts the board on the StackPanes
		setBoardOnPanes();

		// Puts pencil mark on the StackPanes
		setPencilOnPanes();

		// Puts the StackPanes on whole GUI
		setPanesOnPane();

		// Draws the grid lines and border
		createLines();
	}

	private void createPanes() {
		panes = new ArrayList<>();

		for (int i = 0; i < 81; i++) {
			StackPane newPane = new StackPane();
			newPane.setPrefSize(45, 45);
			panes.add(newPane);
		}
	}

	private void setPanesOnPane() {
		putPanes = new GridPane();
		putPanes.setHgap(2);
		putPanes.setVgap(2);

		int counter = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				putPanes.add(panes.get(counter), j + 70, i + 12);
				counter++;
			}
		}
		this.getChildren().add(putPanes);
	}

	private void setBoardOnPanes() {
		theBoard = theGame.getBoard();

		int counter = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (theBoard[i][j] != 0) {
					grid.get(counter).setText(Integer.toString(theBoard[i][j]));
					grid.get(counter).setStyle("-fx-text-fill: black");
					grid.get(counter).setEditable(false);
				}
				panes.get(counter).getChildren().add(grid.get(counter));
				counter++;
			}
		}
	}

	@SuppressWarnings("static-access")
	private void setPencilOnPanes() {
		int counter = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (theBoard[i][j] == 0) {
					TextField newCell = new TextField();
					newCell.setPrefSize(17, 17);
					newCell.setAlignment(Pos.CENTER);
					newCell.setFont(Font.font("Courier New", FontWeight.BOLD, 8));
					newCell.setStyle("-fx-background-radius: 0; -fx-text-fill: grey");

					pencil.get(counter).getChildren().add(newCell);

					panes.get(counter).getChildren().add(pencil.get(counter));
					panes.get(counter).setAlignment(pencil.get(counter), Pos.TOP_LEFT);
				}
				counter++;
			}
		}
	}

	private void clearPencils() {
		int counter = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (theBoard[i][j] == 0) {
					panes.get(counter).getChildren().remove(pencil.get(counter));
				}
				counter++;
			}
		}
	}

	private void createPencilMarks() {
		pencil = new ArrayList<>();

		for (int i = 0; i < 81; i++) {
			GridPane grid = new GridPane();
			grid.setPickOnBounds(false);
			pencil.add(grid);
		}

	}

	private void createTextFields() {
		grid = new ArrayList<>();

		for (int i = 0; i < 81; i++) {
			TextField newCell = new TextField();
			newCell.setPrefSize(45, 45);
			newCell.setAlignment(Pos.CENTER);
			newCell.setFont(Font.font("Courier New", FontWeight.BOLD, 18));
			newCell.setStyle("-fx-background-radius: 0; -fx-text-fill: blue");
			grid.add(newCell);
		}
	}

	private void createLines() {
		gc.setStroke(Color.BLACK);
		gc.setLineWidth(4);
		gc.strokeRect(139.5, 0.5, 425, 427.5);

		gc.setStroke(Color.DARKGRAY);
		gc.setLineWidth(3);
		gc.strokeLine(141.5, 145, 562, 145);
		gc.strokeLine(141.5, 287, 562, 287);
		gc.strokeLine(281, 4.2, 281, 426);
		gc.strokeLine(423, 4.2, 423, 426);
	}

	private void clearTextField() {
		for (TextField field : grid) {
			field.clear();
		}
	}

	/**
	 * Retrieves the current state of the Slaydoku game
	 * 
	 * @return grid - An ArrayList of TextFields that contains the original Slaydoku
	 *         board and the user's answers for the empty spaces
	 */
	public ArrayList<TextField> getSudokuBoard() {
		return grid;
	}

	/**
	 * Updates the view of the SudokuBoard based on the current Slaydoku board.
	 * Different effects are done based on whether or not the user gave up
	 */
	@Override
	public void update(Object theObserved) {
		//System.out.println("Updated");
		if (theGame.getDidGiveUp()) {
			clearPencils();
			theBoard = theGame.getBoard();
			int counter = 0;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (grid.get(counter).getText().equals("")
							|| Integer.parseInt(grid.get(counter).getText()) != theBoard[i][j]) {
						grid.get(counter).setText(Integer.toString(theBoard[i][j]));
						grid.get(counter).setStyle("-fx-text-fill: red");
					} else {
						grid.get(counter).setStyle("fx-text-fill: black");
					}
					grid.get(counter).setEditable(false);
					counter++;
				}
			}
			theGame.setDidGiveUp(false);
		}

		else {
			clearPencils();
			clearTextField();
			theBoard = theGame.getBoard();
			int counter = 0;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (theBoard[i][j] != 0) {
						grid.get(counter).setText(Integer.toString(theBoard[i][j]));
						grid.get(counter).setStyle("-fx-text-fill: black");
						grid.get(counter).setEditable(false);
					} else {
						grid.get(counter).setStyle("-fx-text-fill: blue");
						grid.get(counter).setEditable(true);
					}
					counter++;
				}
			}
			setPencilOnPanes();
		}
	}

}
