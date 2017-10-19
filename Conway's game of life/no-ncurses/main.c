#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "life.h"
#include "interface.h"

#define ROW 20
#define COL 75

// MAIN

int main(){
    srand(time(NULL));

    Board *tabela = generate_board(COL, ROW);
    printf("['r'andom] or 'g'lide? ");

    switch (getchar()){
	case 'g':
	    // plot glider	    
	    break;

	default:
	    plot_random(tabela, 10);
    
    }

    while(1) {
	print_board(tabela);
	next_iteration(tabela);
	usleep(100000);
    }

    return 0;
}
