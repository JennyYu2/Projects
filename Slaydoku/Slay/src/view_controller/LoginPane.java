package view_controller;

import java.util.*;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import model.Serialize;
import model.SudokuAccount;

/**
 * Creates the login section of the GUI. Contains fields for the user to enter
 * their username and password. Attempting to log in makes sure that the
 * username and password is in the save file. If the username exists but the
 * password is different, we give an alert saying the password is wrong. If the
 * username does not exist in our save, then we create a new account.
 * 
 * @author Josh Samadder, Jenny Yu, Ricky Su, Chang Chia En
 *
 */

public class LoginPane extends GridPane {

	private GridPane everything = new GridPane();
	private BorderPane borderPane = new BorderPane();
	private Label userLB = new Label("Account Name");
	private TextField userfield = new TextField();
	private Button login = new Button("Login");
	private Label passwordLB = new Label("Password");
	private PasswordField passwordfield = new PasswordField();
	private Button logout = new Button("Log out");
	private Label statusLB = new Label("Login or Create Account");
	private Serialize serialized = new Serialize();
	private boolean loggedIn = false;
	private String name;

	// store username and password
	private HashMap<String, String> usersData = new HashMap<String, String>();

	// Constructor
	// when the obj be created, it will call the constructor
	// and printout the layout
	public LoginPane() {
		this.Layout();
		this.registerHandlers();
	}

	private void Layout() {
		everything.setHgap(10);
		everything.setVgap(10);

		everything.add(statusLB, 0, 0);

		everything.add(userLB, 0, 1);
		everything.add(userfield, 1, 1);
		everything.add(login, 2, 1);

		everything.add(passwordLB, 0, 2);
		everything.add(passwordfield, 1, 2);
		everything.add(logout, 2, 2);

		everything.setPadding(new Insets(10, 10, 10, 10));
		everything.setAlignment(Pos.CENTER);

		borderPane.setCenter(everything);
		borderPane.setPrefWidth(1000);
		borderPane.setStyle("-fx-border-color: black; -fx-border-width: 1px;");

		this.add(borderPane, 0, 0);
		this.add(everything, 0, 0);
		this.setAlignment(Pos.CENTER);
	}

	private void setLoggedIn() {
		if (loggedIn) {
			loggedIn = false;
		} else {
			loggedIn = true;
		}
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
	 * Retrieves the username of the current user
	 * 
	 * @return name - The username of the current user
	 */
	public String getCurName() {
		return name;
	}

	// verify the user's inputs
	// return boolean
	private boolean authenticated(String password) {
		if (!usersData.containsKey(name)) {
			// create a new account
			statusLB.setText("Account created");
			ArrayList<SudokuAccount> accounts = serialized.deserializeStats();
			SudokuAccount newAccount = new SudokuAccount(name);
			accounts.add(newAccount);
			serialized.serializeStats(accounts);
			return true;
		}

		else if (password.equals(usersData.get(name))) {
			// login the exist account
			statusLB.setText("Logged in successfully");
			ArrayList<SudokuAccount> accounts = serialized.deserializeStats();
			for (SudokuAccount account : accounts) {
				if (account.getName().equals(name)) {
					account.addGame();
					serialized.serializeStats(accounts);
				}
			}
			return true;
		}
		// username is correct but entered the weong password
		statusLB.setText("Please enter a correct password");
		return false;

	}

	private void registerHandlers() {
		login.setOnAction(new LoginHandler());
		logout.setOnAction(new LogoutHandler());
	}

	private class LoginHandler implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent arg0) {
			usersData = serialized.deserializeUsers();
			name = userfield.getText();
			String password = passwordfield.getText();

			if (authenticated(password)) {
				usersData.put(name, password);
				System.out.println("Users' Data: " + usersData);
				// no longer to let the user modify the button and textfield
				login.setDisable(true);
				userfield.setDisable(true);
				passwordfield.setDisable(true);
				setLoggedIn();
				System.out.println(getLoggedIn());
				serialized.serializeUsers(usersData);
			}
		}

	}

	private class LogoutHandler implements EventHandler<ActionEvent> {
		@Override
		public void handle(ActionEvent arg0) {
			statusLB.setText("Login or Create Account");
			// let the user modify the button and textfield
			login.setDisable(false);
			userfield.setDisable(false);
			passwordfield.setDisable(false);
			setLoggedIn();
			System.out.println(getLoggedIn());
		}
	}

}
