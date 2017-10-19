#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define ROW 20
#define COL 75

// GOL

typedef struct board {
    int **board;
    int col;
    int row;
} Board;

int **start_matrix(int co, int ro){
    int **m = (int**) malloc(ro*sizeof(int*)), 
	r, c;

    for(r = 0; r < ro; r++)
	m[r] = (int*) malloc(co*sizeof(int));

    for(r = 0; r < ro; r++){
	for(c = 0; c < co; c++)
	    m[r][c] = 0;
    }

    return m;
}

void free_matrix(int **m, int rows){
    while(rows){
	rows--;
	free(m[rows]); 
    }
    free(m);
}

Board *start_board(int co, int ro){
    int r, c;
    
    Board *b = (Board*) malloc(sizeof(Board));
    b->board = start_matrix(co, ro);

    b->col = co;
    b->row = ro;
    return b;
}

void random_plot(Board *b){
    int t, r, c;
    
    //                                 | quantidade de celulas no estado inicial
    for(t = 0; t < ((b->row)*(b->col))/7; t++){
	r = rand()%b->row; 
	c = rand()%b->col; 

	b->board[r][c] = 1;
    }
}

int normalize(int max, int val){
    if (val < 0)
	val = max + val;
    else if (val == max)
	val = val%max;
    
    return val;
} 

int cell_state(Board *b, int x, int y){
    int sum = 0, x1, y1, x2, y2; 
    for(y1 = -1; y1 <= 1; y1++){
	for(x1 = -1; x1 <= 1; x1++){
	    if (y1 == 0 && x1 == 0)
		continue;
	    
	    x2 = normalize(b->col, x+x1);
	    y2 = normalize(b->row, y+y1);
	    
	    sum += b->board[y2][x2];
	}
    }

    // alive cases
    if (sum == 3 || (b->board[y][x] == 1 && sum == 2))
       return 1;	
    
    // dead cases
    else
	return 0;
}

void next_iteration(Board *b){
    int **m = start_matrix(b->col, b->row),
	r, c;

    for(r = 0; r < b->row; r++){
	for(c = 0; c < b->col; c++)
	    m[r][c] = cell_state(b, c, r);
    }
    
    free_matrix(b->board, b->row);
    b->board = m;
}


// UI

void print_board(Board* b){
    int r, c;

    // Centralizei para o meu monitor, ajustar essa configuração 
    for(r = 0; r < b->row/2; r++)
       printf("\n");	
    
    for(r = 0; r < b->row; r++){
	for(c = 0; c < b->col; c++)
	    printf(b->board[r][c] ? " ▀" : "  ");  
	printf("\n");
    }
    
    for(r = 0; r < b->row/3; r++)
       printf("\n");	
}


// MAIN

void plot_glider(Board *b){
    b->board[0][1] = 1;
    b->board[1][2] = 1;
    b->board[2][0] = 1;
    b->board[2][1] = 1;
    b->board[2][2] = 1;
}

int main(){
    srand(time(NULL));

    Board *tabela = start_board(COL, ROW);
    
    printf("['r'andom] or 'g'lide? ");
    if (getchar() == 'g')
	plot_glider(tabela);
    else
	random_plot(tabela);

    while(1) {
	print_board(tabela);
	next_iteration(tabela);
	usleep(100000);
    }

    return 0;
}
