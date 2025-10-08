package view_controller;

import javafx.animation.TranslateTransition;
import javafx.application.Application;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;
import javafx.util.Duration;
import model.OurObserver;
import model.SudokuGame;

/**
 * The main Slaydoku GUI. Sets all of the elements, like LoginPane,
 * OptionButtons, and SudokuBoard onto a BorderPane. Also displays an animation
 * on startup
 * 
 * @author Josh Samadder, Jenny Yu, Ricky Su, Chang Chia En
 *
 */

public class SudokuGUI extends Application {

	private BorderPane everything = new BorderPane();
	private SudokuGame theGame;
	private OurObserver theBoard;
	private LoginPane login = new LoginPane();
	private OptionButtons options;
	private Scene game;
	private final int EASY = 40;
	//private final int EASY = 10;
	private Stage animation = new Stage();

	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage stage) throws Exception {
//		ArrayList<SudokuAccount> accounts = new ArrayList<SudokuAccount>();
//		Serialize serialized = new Serialize();
//		HashMap<String, String> users = new HashMap<String, String>();
//		serialized.serializeUsers(users);
//		serialized.serializeStats(accounts);

		playIntro();
		animation.showAndWait();

		initializeGameForTheFirstTime();
		theBoard = new SudokuBoard(theGame);
		options = new OptionButtons(theGame, login, (SudokuBoard) theBoard);

		theGame.addObserver(theBoard);
		everything.setTop(options);
		everything.setCenter((Node) theBoard);
		everything.setBottom(login);

		game = new Scene(everything, 700, 620);

		stage.setTitle("Slaydoku");
		stage.getIcons().add(new Image("file:src/documents/kaguya.png"));
		stage.setScene(game);
		stage.show();
	}

	private void initializeGameForTheFirstTime() {
		theGame = new SudokuGame(9, EASY);
	}

	private void playIntro() {
		Button butt = new Button("Slay");
		butt.setPrefSize(40, 20);
		butt.setLayoutX(235);
		butt.setLayoutY(350);

		butt.setOnAction(event -> {
			animation.close();
		});

		Rectangle r = new Rectangle();
		r.setHeight(70);
		r.setWidth(70);
		r.setRotate(45);
		r.setFill(Color.DEEPPINK);
		r.setLayoutX(220);
		r.setLayoutY(220);

		TranslateTransition t = new TranslateTransition();
		t.setDuration(Duration.seconds(1.5));
		t.setAutoReverse(true);
		t.setCycleCount(1);
		t.setToX(-320);
		t.setNode(r);
		t.play();

		Rectangle r2 = new Rectangle();
		r2.setHeight(70);
		r2.setWidth(70);
		r2.setRotate(45);
		r2.setFill(Color.DEEPPINK);
		r2.setLayoutX(220);
		r2.setLayoutY(220);

		TranslateTransition t2 = new TranslateTransition();
		t2.setDuration(Duration.seconds(1.5));
		t2.setAutoReverse(true);
		t2.setCycleCount(1);
		t2.setToX(320);
		t2.setNode(r2);
		t2.play();

		Label l = new Label("Welome to");
		l.setFont(Font.font("Calibri", 40));
		l.setLayoutX(165);
		l.setLayoutY(-100);

		TranslateTransition t3 = new TranslateTransition();
		t3.setDuration(Duration.seconds(1.5));
		t3.setAutoReverse(true);
		t3.setCycleCount(1);
		t3.setToY(220);
		t3.setNode(l);
		t3.play();

		Label l2 = new Label("Slaydoku!");
		l2.setFont(Font.font("Courier New", FontWeight.BOLD, 50));
		l2.setTextFill(Color.MEDIUMSLATEBLUE);
		l2.setLayoutX(130);
		l2.setLayoutY(220);

		Pane root = new Pane();
		root.setStyle("-fx-background-color: #b6bfc9");
		root.getChildren().add(l);
		root.getChildren().add(l2);
		root.getChildren().add(r);
		root.getChildren().add(r2);
		root.getChildren().add(butt);

		Scene sean = new Scene(root, 500, 500);
		animation.setScene(sean);
	}

}
