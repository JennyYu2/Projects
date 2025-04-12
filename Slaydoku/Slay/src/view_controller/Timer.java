package view_controller;

import javafx.application.Platform;
import javafx.scene.control.Label;

/**
 * Keeps track of the time the player takes to complete the game. Allows for
 * pausing, resuming, and resetting the timer depending on what is needed
 * 
 * @author Josh Samadder, Jenny Yu, Ricky Su, Chang Chia En
 *
 */

public class Timer extends Label {

	private int hours = 0;
	private int minutes = 0;
	private int seconds = 0;
	private boolean isPaused;
	private Thread timerThread;

	public Timer() {

		resume();
	}

	/**
	 * Sets isPaused to True, causing the label to not update
	 */
	public void pause() {
		isPaused = true;
		//System.out.println("paused");
	}

	/**
	 * Unpauses/resets the timer by resetting the thread
	 */
	public void resume() {
		isPaused = false;
		timerThread = new Thread(() -> {
			while (!isPaused) {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {

				}

				seconds += 1;

				if (seconds == 60) {
					minutes += 1;
					seconds = 0;
				}

				if (minutes == 60) {
					hours += 1;
					minutes = 0;
				}
				Platform.runLater(() -> {
					this.setText(hours + " h " + minutes + " m " + seconds + " s");
				});
			}
		});
		timerThread.start();
		//System.out.println("unpaused");
	}

	/**
	 * Resets the value for hours, minutes, and seconds to 0 and resumes the timer
	 * from that point
	 */
	public void reset() {
		hours = 0;
		minutes = 0;
		seconds = 0;
		resume();
	}

	/**
	 * Retrieve the current time of the board in hours, minutes, and seconds
	 * 
	 * @return time - An array that contains the current values of hours, minutes,
	 *         and seconds
	 */
	public int[] getCurrentTime() {
		int[] time = { hours, minutes, seconds };
		return time;
	}
}
