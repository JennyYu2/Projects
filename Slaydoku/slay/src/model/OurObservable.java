package model;

import java.util.ArrayList;

/**
 * Allows us to update all observers that we might have
 * 
 * @author Rick Mercer
 *
 */

public class OurObservable {
	ArrayList<OurObserver> observers = new ArrayList<>();
	
	
	/**
	 * Adds an observer to the list of observers
	 * 
	 * @param anObserver - An observer that we want to add to our list of observers
	 */
	
	public void addObserver(OurObserver anObserver) {
		observers.add(anObserver);
	}
	
	/**
	 * Runs the update method of all observers in the list
	 * 
	 * @param theObservable - The list of observers
	 */
	
	public void notifyObservers(OurObservable theObservable) {
		for (OurObserver obs : observers) {
			obs.update(theObservable);
		}
	}
}
