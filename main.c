#include <stdio.h>
#include <stdlib.h>

#define boardSize 3

char gameMode[] = "";
int unoccupiedPlaces[boardSize][2];
int plausibleMoves[boardSize*boardSize][2];

#include "algo.h"


int main() {

    generateBoard();
    printBoard();

    while (!checkDraw() && !checkWin('x') && !checkWin('o')) {
        int row, column;
        printf("Enter row and column: ");
        scanf("%d %d", &row, &column);
        placeX(row-1, column-1);
        printBoard();
        if (checkWin('x')) {
            printf("X wins!\n");
            break;
        }
        if (checkDraw()) {
            printf("Draw!\n");
            break;
        }
        findUnoccupiedPlaces();
        int offset = plausibleMoves_Rows(0);
        offset += plausibleMoves_Columns(offset);
        offset += plausibleMoves_Diagonals(offset);

        for (int i=0; i<offset; i++) {
            printf("Row %d, Column %d\n", plausibleMoves[i][0]+1, plausibleMoves[i][1]+1);
        }

        int move[2];

        if (offset == 0) {
            int unoccupiedLen = sizeof(unoccupiedPlaces)/sizeof(unoccupiedPlaces[0]);
            int random = rand() % unoccupiedLen;
            move[0] = unoccupiedPlaces[random][0];
            move[1] = unoccupiedPlaces[random][1];
        } else {
            int random = rand() % offset;
            move[0] = plausibleMoves[random][0];
            move[1] = plausibleMoves[random][1];
        }

        placeO(move[0], move[1]);
        printBoard();
        if (checkWin('o')) {
            printf("O wins!\n");
            break;
        }
        if (checkDraw()) {
            printf("Draw!\n");
            break;
        }
    }

//    placeX(0, 0);
//    placeX(0, 1);
//    placeX(0,2);
//    placeX(1,1);
//    printf("\n");
//    printBoard();
//    int win = checkWin('x');
//    printf("X Win: %d\n", win);
//    win = checkWin('o');
//    printf("O Win: %d\n", win);
//
//    findUnoccupiedPlaces();
//    for (int i=0; i<boardSize; i++) {
//        for (int j=0; j<boardSize; j++) {
//            printf("%d", unoccupiedPlaces[i][j]);
//        }
//        printf("\n");
//    }
}
