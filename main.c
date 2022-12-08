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
        if (placeX(row-1, column-1) == 1) {
            printf("Invalid move, try again\n");
            continue;
        }
        if (checkWin('x')) {
            clearScreen();
            printBoard();
            printf("X wins!\n");
            break;
        }
        if (checkDraw()) {
            clearScreen();
            printBoard();
            printf("Draw!\n");
            break;
        }
        findUnoccupiedPlaces();
        int offset = plausibleMoves_Rows(0);
        offset += plausibleMoves_Columns(offset);
        offset += plausibleMoves_Diagonals(offset);

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
        clearScreen();
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

}
