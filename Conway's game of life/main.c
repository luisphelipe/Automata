#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "life.h"
#include "patterns.h"
#include "interface.h"

#define ROW 33
#define COL 75
#define DELAY 200000


void menu(Board *tabela){
    int opt;
    char aux[30];

    printf("1 [Random]\n2 Plot glider\n3 Load state\nChoice: ");
    scanf("%d", &opt);

    switch(opt){
	case 2:
	    plot_pattern(tabela, glider, 0, 0);
	    return;
	case 3:
	    printf("filename? ");
	    scanf("%s", aux);
	    load_state(tabela, aux);
	    return;
	default:
	    plot_random(tabela, 10);
	    save_state(tabela, "rename");
    }
}

int main(){
    srand(time(NULL));

    Board *tabela = generate_board(COL, ROW);
    menu(tabela);

    while(1) {
	print_board(tabela);
	next_iteration(tabela);
	usleep(DELAY);
    }
    
    free_board(tabela);
    return 0;
}
