#include <stdio.h>
#include "interface.h"


void print_board(Board* board){
    int row, col;

    // Centralizei para o meu monitor, ajustar essa configuração 
    for(row = 0; row < 10; row++)
       printf("\n");
    
    for(row = 0; row < board->rows; row++){
	for(col = 0; col < board->columns; col++)
	    printf(board->matrix[row][col] ? " ▀" : "  ");  
	printf("\n");
    }
    
    /* Centralizei para o meu monitor, ajustar essa configuração 
    for(row = 0; row < 2; row++)
       printf("\n");
       */
    
    fflush(stdout);
}
