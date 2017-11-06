public class Life extends Rule {
    private int[][] state = {
	{0, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 0, 0}
    };


    int wrap(int max, int val){
	if (val < 0) val += max;
	else if (val >= max) val %= max;
	return val;
    }

    private int cellState(int[][] b, int r, int c){
	int xr, xc, yr, yc, sum=0;	
	for(xr = -1; xr <= 1; xr++){
	    for(xc = -1; xc <= 1; xc++){
		if(xr == 0 && xc == 0) continue;

		yr = wrap(Automata.WIDTH, r+xr);
		yc = wrap(Automata.LENGTH, c+xc);

		sum += b[yr][yc];
	    }
	}
	
	int cell = b[r][c];
	return state[cell][sum];
    }

    public int[][] nextIteration(int[][] b){
	int[][] nb = Automata.newMatrix();
	
	for(int r = 0; r < Automata.WIDTH; r++){
	    for(int c = 0; c < Automata.LENGTH; c++){
		nb[r][c] = cellState(b, r, c);
	    }
	}

	return nb;
    }

}
