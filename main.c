#include <stdio.h>

#define boardSize 3

char gameMode[] = "";
int unoccupiedPlaces[boardSize][boardSize];
int plausibleMoves[boardSize*boardSize][2];

#include "algo.h"


int main() {

    generateBoard();

    printBoard();

    placeX(0, 0);
    placeX(0, 1);
    placeX(0,2);
    placeX(1,1);
    printf("\n");
    printBoard();
    int win = checkWin('x');
    printf("X Win: %d\n", win);
    win = checkWin('o');
    printf("O Win: %d\n", win);

    findUnoccupiedPlaces();
//    for (int i=0; i<boardSize; i++) {
//        for (int j=0; j<boardSize; j++) {
//            printf("%d", unoccupiedPlaces[i][j]);
//        }
//        printf("\n");
//    }

    int offset = plausibleMoves_Rows(0);
    offset += plausibleMoves_Columns(offset);
    offset += plausibleMoves_Diagonals(offset);

    printf("Calculated moves for %c\n", botPiece);
    for (int i=0; i<offset; i++) {
        printf("Row %d, Column %d\n", plausibleMoves[i][0]+1, plausibleMoves[i][1]+1);
    }
}
