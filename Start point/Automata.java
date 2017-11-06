import java.io.*;
import java.util.Scanner;


public class Automata implements Serializable {
    public static final int WIDTH = 33;
    public static final int LENGTH = 75;
    public static final int FILL = 10;
    public static final int DELAY = 100;
    public static final String FILENAME = "test";
    public int[][] board;
    Rule rule;

    // Inicializar 'board'
    public Automata() {
	board = newMatrix();
	rule = new Life();
	plotRandom();
    }

    public static Automata menu() throws Error{
	Automata kill = new Automata();

	Scanner scanner = new Scanner(System.in);
	System.out.print("Random [1] Carregar salvo [2]: ");
	int opt = Integer.parseInt(scanner.nextLine());

	switch(opt){
	    case 1:
		kill.saveState();
		break;
	    case 2:
		kill = Automata.loadState();
		break;
	}
	return kill;
    }

    public static void main(String[] args) {
	Automata kill = Automata.menu();
	
	while(true){
	    try {
		kill.printBoard();
		kill.board = kill.rule.nextIteration(kill.board);
		Thread.sleep(DELAY);
	    } catch (InterruptedException ex) {
		System.out.println("INTERRUPTED");
	    }
	}	
    }

    public static int[][] newMatrix(){
	int[][] b = new int[Automata.WIDTH][Automata.LENGTH];
	return b;
    }

    // Fill representa porcentagem do board à preencher
    private void plotRandom(){
	int aux, row, col;
	int quantity = (int) ((Automata.WIDTH * Automata.LENGTH) 
		     * ((float) FILL/100));
	
	for(aux = 0; aux < quantity; aux++){
	    row = (int) (Math.random()*Automata.WIDTH);
	    col = (int) (Math.random()*Automata.LENGTH);

	    if(board[row][col] == 0)
		board[row][col] = 1;
	    else
		aux--;
	}
    }

    private void printBoard(){
	String clear = "\n\n\n\n\n";
	System.out.println(clear);
	for(int row = 0; row < Automata.WIDTH; row++){
	    for(int col = 0; col < Automata.LENGTH; col++)
		System.out.print(board[row][col] == 1 ? " ▀" : "  ");
	    System.out.println();
	}
    
	// System.out.println("\n\n");
    }

    private void saveState(){
	try {
	    FileOutputStream fs = new FileOutputStream(Automata.FILENAME);
	    ObjectOutputStream os = new ObjectOutputStream(fs);
	    os.writeObject(this);
	    os.close();
	} catch (Exception ex) {
	    ex.printStackTrace();
	}
    }

    private static Automata loadState() throws Error{
	try {
	    FileInputStream fs = new FileInputStream(Automata.FILENAME);
	    ObjectInputStream os = new ObjectInputStream(fs);
	    Automata obj = (Automata) os.readObject();
	    os.close();
	    return obj;
	} catch (Exception ex) {
	    System.out.println("Error, cannot load file '" + Automata.FILENAME + "'");
	    return null;
	}
    }
}
