package tests;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.util.concurrent.CountDownLatch;

import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import javafx.application.Platform;
import model.SudokuGame;

public class SudokuGameTest {

    private SudokuGame sudokuGame;
    
    @BeforeClass
    public static void setUpClass() {
    	Platform.startup(null);
    }
    
    @Before
    public void setUp() {
        sudokuGame = new SudokuGame(9, 40); 
    }

    @Test
    public void testBoardDimensions() {
        Assert.assertEquals("incorrect row", 9, sudokuGame.board.length);
        Assert.assertEquals("incorrect col", 9, sudokuGame.board[0].length);
    }
    
    @Test
    public void testMissingNumbers() {
        int missingCount = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (sudokuGame.board[i][j] == 0) {
                    missingCount++;
                }
            }
        }
        Assert.assertEquals("incorrect missing num", 40, missingCount);
    }
    

    @Test
    public void testChangeDifficulty() {
        sudokuGame.changeDifficulty(30); 
        int missingCount = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (sudokuGame.board[i][j] == 0) {
                    missingCount++;
                }
            }
        }
        Assert.assertEquals("incorrect missing count", 30, missingCount);
    }
    
    @Test
    public void testIsLoggedIn() {
        assertFalse(sudokuGame.getLoggedIn()); // assert that the initial value of loggedIn is false
        
        sudokuGame.isLoggedIn(); // call the isLoggedIn method
        assertTrue(sudokuGame.getLoggedIn()); // assert that the value of loggedIn is now true
    }
    
    @Test
    public  void testGetLoggedIn() {
        assertFalse(sudokuGame.getLoggedIn()); // assert that the initial value of loggedIn is false
        
        sudokuGame.isLoggedIn(); // call the isLoggedIn method
        assertTrue(sudokuGame.getLoggedIn()); // assert that the value of loggedIn is true
    }

    @Test
    public void testGetBoard() {
        int[][] board = sudokuGame.getBoard();
        assertNotNull(board);
        assertEquals("incorrect row", 9, board.length);
        assertEquals("incorrect col", 9, board[0].length);
    }
    
    @Test
    public void testClearChanges() {
        sudokuGame.clearChanges(); // call the clearChanges method
        int[][] board = sudokuGame.getBoard();
        assertNotNull(board);
        assertEquals("incorrect row", 9, board.length);
        assertEquals("incorrect col", 9, board[0].length);
    }

    @Test
    public void testSolveBoard() {
        SudokuGame sudokuGame = new SudokuGame(9, 40);
        sudokuGame.solveBoard();
        int[][] solvedBoard = sudokuGame.getSolvedBoard();
        assertNotNull(solvedBoard);
        assertEquals("incorrect row", 9, solvedBoard.length);
        assertEquals("incorrect col", 9, solvedBoard[0].length);
        assertTrue("board not solved", isBoardSolved(solvedBoard));
    }

    private boolean isBoardSolved(int[][] board) {
        // Check if all cells are filled
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j] == 0) {
                    return false;
                }
            }
        }

        // Check rows
        for (int i = 0; i < board.length; i++) {
            if (!isDistinct(board[i])) {
                return false;
            }
        }

        // Check columns
        for (int i = 0; i < board.length; i++) {
            int[] col = new int[board.length];
            for (int j = 0; j < board.length; j++) {
                col[j] = board[j][i];
            }
            if (!isDistinct(col)) {
                return false;
            }
        }

        // Check 3x3 boxes
        for (int i = 0; i < board.length; i += 3) {
            for (int j = 0; j < board.length; j += 3) {
                int[] box = new int[board.length];
                int k = 0;
                for (int x = i; x < i + 3; x++) {
                    for (int y = j; y < j + 3; y++) {
                        box[k++] = board[x][y];
                    }
                }
                if (!isDistinct(box)) {
                    return false;
                }
            }
        }

        return true;
    }

    private boolean isDistinct(int[] arr) {
        int[] counts = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == 0) {
                continue;
            }
            if (++counts[arr[i] - 1] > 1) {
                return false;
            }
        }
        return true;
    }

    @Test
    public void testDidGiveUp() {
        assertFalse(sudokuGame.getDidGiveUp()); // assert that the initial value of didGiveUp is false
        
        sudokuGame.setDidGiveUp(true); // call the setDidGiveUp method with true argument
        assertTrue(sudokuGame.getDidGiveUp()); // assert that the value of didGiveUp is now true
        
        sudokuGame.setDidGiveUp(false); // call the setDidGiveUp method with false argument
        assertFalse(sudokuGame.getDidGiveUp()); // assert that the value of didGiveUp is now false again
    }

    @Test
    public void testGetCurrentDifficulty() {
        SudokuGame sudokuGameEasy = new SudokuGame(9, 35);
        assertEquals(35, sudokuGameEasy.getCurrentDifficulty());
        
        SudokuGame sudokuGameMedium = new SudokuGame(9, 45);
        assertEquals(45, sudokuGameMedium.getCurrentDifficulty());
        
        SudokuGame sudokuGameHard = new SudokuGame(9, 55);
        assertEquals(55, sudokuGameHard.getCurrentDifficulty());
    }

    
}