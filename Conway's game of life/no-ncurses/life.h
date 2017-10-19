#ifndef LIFE_H
#define LIFE_H


typedef struct board {
    int **matrix;
    int columns;
    int rows;
} Board;

int **generate_matrix(int collumns, int rows);
void free_matrix(int **matrix, int rows);

Board *generate_board(int collumns, int rows);
void free_board(Board *board); // TO DO

void plot_random(Board *board, int fill);
void plot_pattern(Board *board, int **patern, int row, int col); // TO DO

int cell_state(Board *board, int col, int row);
void next_iteration(Board *board);

#endif
