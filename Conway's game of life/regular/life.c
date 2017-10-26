#include <stdlib.h>
#include <stdio.h>
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
    free_matrix(board->matrix, board->rows);
    free(board); 
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

int __wrap(int max, int val){
    if (val < 0) val = max + val;
    if (val == max) val = val%max;
    return val;
}

void plot_pattern(Board *board, int pattern[][2], int row, int col){
    int aux, r, c, size = pattern[0][1];

    for(aux = 1; aux <= size; aux++){
	r = __wrap(board->rows, row+pattern[aux][0]);
	c = __wrap(board->columns, col+pattern[aux][1]);
	
	board->matrix[r][c] = 1;	    
    } 
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

void save_state(Board *board, char *filename){
    int row, col;
    FILE *arquivo = fopen(filename, "w");
    
    fprintf(arquivo, "%d %d\n", board->rows, board->columns);
    for(row = 0; row < board->rows; row++){
	for(col = 0; col < board->columns; col++)
	   fprintf(arquivo, "%d ", board->matrix[row][col]);
	fprintf(arquivo, "\n");	
    }

    fclose(arquivo);
}

void load_state(Board *board, char *filename){
    int rows, columns, row, col;
    free_board(board);

    FILE *arquivo = fopen(filename, "r");

    fscanf(arquivo, "%d %d", &rows, &columns);
    board = generate_board(columns, rows); 
    
    for(row = 0; row < rows; row++){
	for(col = 0; col < columns; col++)
	    fscanf(arquivo, "%d", &board->matrix[row][col]);
    }

    fclose(arquivo);
}
