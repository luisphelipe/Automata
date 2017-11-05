public class Automata {
    public static final int WIDTH = 33;
    public static final int LENGTH = 75;
    public static final int FILL = 10;
    public static final int DELAY = 100;
    public int[][] board;
    Rule rule;

    // Inicializar 'board'
    public Automata() {
	board = newMatrix();
	rule = new Life();
	plotRandom();
    }

    public static void main(String[] args) {
	Automata kill = new Automata();
	
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
}
