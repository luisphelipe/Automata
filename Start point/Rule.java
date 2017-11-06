import java.io.*;


public abstract class Rule implements Serializable {
    // representa os 18 estados possiveis
    // e o resultado.
    // int[][] state;

    // private int cellState(int[][] b, int r, int c);
    abstract public int[][] nextIteration(int[][] b);
}
