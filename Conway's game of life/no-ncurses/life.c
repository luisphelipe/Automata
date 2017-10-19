#include <stdlib.h>
#include "life.h"


int **generate_matrix(int columns, int rows){
    int **matrix = (int**) malloc(rows*sizeof(int*)),
	col, row, aux;

    for(row = 0; row < rows; row++){
	matrix[row] = (int*) malloc(columns*sizeof(int));
	
	for(aux = 0; aux < columns; aux++)
	    matrix[row][aux] = 0;
    }

    return matrix;
}

void free_matrix(int **matrix, int rows){
    int row;

    for(row = 0; row < rows; row++)
	free(matrix[row]);

    free(matrix);
}

Board *generate_board(int columns, int rows){
    Board *board = (Board*) malloc(sizeof(Board));
    board->matrix = generate_matrix(columns, rows);

    board->columns = columns;
    board->rows = rows;
    return board;
}

void free_board(Board *board){
    
    // TO DO
    
    return;
}

void plot_random(Board *board, int fill){
    int aux, col, row,
	quantity = (int) ((board->rows * board->columns) * (fill/100.));


    for(aux = 0; aux < quantity; aux++){
	
	col = rand()%board->columns;
	row = rand()%board->rows;
	
	board->matrix[row][col] = 1;
    } 
}

void plot_pattern(Board *board, int **patern, int row, int col){

    // TO DO

    return; 
}

int __wrap(int max, int val){
    if (val < 0) val = max + val;
    if (val == max) val = val%max;
    return val;
}

int cell_state(Board *board, int col, int row){
    int aux_r, aux_c, r, c, sum=0;

    for(aux_r = -1; aux_r <= 1; aux_r++){
	for(aux_c = -1; aux_c <= 1; aux_c++){
	    if(aux_r == 0 &&  aux_c == 0) continue;  

	    r = __wrap(board->rows, aux_r+row);
	    c = __wrap(board->columns, aux_c+col);

	    sum += board->matrix[r][c];
	}
    }

    // Is Alive
    if ((board->matrix[row][col] == 1 && sum == 2) || sum == 3)
	return 1;

    // Is Dead
    else
	return 0;
}

void next_iteration(Board *board){
    int **matrix = generate_matrix(board->columns, board->rows),
	row, col;

    for(row = 0; row < board->rows; row++){
	for(col = 0; col < board->columns; col++)
	    matrix[row][col] = cell_state(board, col, row);
    }

    free_matrix(board->matrix, board->rows);
    board->matrix = matrix;
}
