#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define boardSize 3

int unoccupiedPlaces[boardSize][2];
int plausibleMoves[boardSize*boardSize][2];
int winningMoves[boardSize*boardSize][2];

#include "algo.h"

int think() {
    printf("\rThinking...\n");
    sleep(1);
    return 0;
}

int main() {
    clearScreen();
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("You will now play against the computer.\n"
           "The grid size is %d, and the coordinates are from `1 1` to `%d %d`.\n"
           "The computer will be `O` and you will be `X`.\n"
           "You go first.\n"
           "Press enter to continue.", boardSize, boardSize, boardSize);
    getchar();
    clearScreen();

    printf("Sample Input: 1 1\n"
           "where 1 1 refers to the first row and first column.\n");
    printf("Press enter to continue.");
    getchar();
    clearScreen();

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
            printf("X wins! Congratulations!\n");
            break;
        }
        if (checkDraw()) {
            clearScreen();
            printBoard();
            printf("Draw!\n");
            break;
        }

        think();

        // the bot starts to think
        findUnoccupiedPlaces();
        int wOffset = winningMoves_Row(0);
        wOffset += winningMoves_Column(0);
        wOffset += winningMoves_Diagonals(0);
        if (wOffset > 0) {
            int move = rand() % wOffset;
            placeO(winningMoves[move][0], winningMoves[move][1]);
            clearScreen();
            printBoard();
            printf("O wins! Better luck next time :(\n");
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
            printf("O wins! Better luck next time :(\n");
            break;
        }
        if (checkDraw()) {
            printf("Draw!\n");
            break;
        }
    }

}
