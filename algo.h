//
// Created by mahas on 08-Dec-22.
//


#ifndef ALGORITHM
#define ALGORITHM
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #define os "windows"
#else
    #define os "unix"
#endif // defined

/*
pink = "\033[95m";
blue = "\033[94m";
cyan = "\033[96m";
green = "\033[92m";
yellow = "\033[93m";
red = "\033[91m";
bold = "\033[1m";
underline = "\033[4m";
end_formatting = "\033[0m";
*/

const char playerPiece = 'x';
const char botPiece = 'o';
const char space = ' ';

const char UtfPlayerPiece[] = "\033[96m\xEF\xBD\x98\033[0m";
const char UtfBotPiece[] = "\033[92m\xEF\xBD\x8F\033[0m";
const char UtfSpace[] = "\xE3\x80\x80";
const char UtfHyphen[] = "\xE3\x83\xBC";
const char UtfPipe[] = "\xEF\xBD\x9C";

char board[boardSize][boardSize];

void generateBoard () {
    for (int i=0; i<boardSize; i++) {
        for (int j=0; j<boardSize; j++) {
            board[i][j] = ' ';
        }
    }
}

int playerSwitch = 0;
// 0 is player1's turn, 1 is player2's turn

int printBoard () {
    int i, j;
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardSize; j++) {
            if (board[i][j] == ' ') {
                printf("%s", UtfSpace);
            } else if (board[i][j] == 'x') {
                printf("%s", UtfPlayerPiece);
            } else if (board[i][j] == 'o') {
                printf("%s", UtfBotPiece);
            } else {
                printf("%c", board[i][j]);
            }

            if (j < boardSize - 1) {
                printf("%s", UtfPipe);
            }
        }
        printf("\n");
        if (i < boardSize - 1) {
            for (j = 0; j < boardSize; j++) {
                printf("%s", UtfHyphen);
                if (j < boardSize - 1) {
                    printf("%s", UtfHyphen);
                }
            }
            printf("\n");
        }
    }
    return 0;
}

void findUnoccupiedPlaces () {
    int count = 0;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == space) {
                unoccupiedPlaces[count][0] = i;
                unoccupiedPlaces[count][1] = j;
                count++;
            }
        }
    }
}

int placeX (int x, int y) {
    if (board[x][y] != space) {
        return 1;
    }
    board[x][y] = playerPiece;
    findUnoccupiedPlaces();
    return 0;
}

int placeO (int x, int y) {
    if (board[x][y] != space) {
        return 1;
    }
    board[x][y] = botPiece;
    findUnoccupiedPlaces();
    return 0;
}

int place () {
    int x, y;
    if (playerSwitch == 0) {
        printf("Player 1's turn");
        printf("Enter your move - `x y`: ");
        scanf("%d %d", &x, &y);
        if (placeX(x, y) == 1) {
            printf("Invalid move, try again");
            place();
        } else {
            playerSwitch = 1;
        }
    } else if (playerSwitch == 1) {
        printf("Player 2's turn");
        printf("Enter your move (x y): ");
        scanf("%d %d", &x, &y);
        if (placeO(x, y) == 1) {
            printf("Invalid move, try again");
            place();
        } else {
            playerSwitch = 0;
        }
    }
    return 0;
}

int plausibleMoves_Rows(int offset) {
    // check each row, if the row has > n/2 player pieces and no bot pieces, then add the empty spaces to plausibleMoves
    int plausibleRows[boardSize*boardSize][2];
    int plausibleRowsCount = 0;
    for (int i = 0; i < boardSize; i++) {
        int playerPieces = 0;
        int botPieces = 0;
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == playerPiece) {
                playerPieces++;
            } else if (board[i][j] == botPiece) {
                botPieces++;
            }
        }
        if (playerPieces > boardSize/2 && botPieces == 0) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == space) {
                    plausibleRows[plausibleRowsCount][0] = i;
                    plausibleRows[plausibleRowsCount][1] = j;
                    plausibleRowsCount++;
                }
            }
        }
    }

    // add plausibleRows to plausibleMoves
    for (int i = 0; i < plausibleRowsCount; i++) {
        plausibleMoves[i+offset][0] = plausibleRows[i][0];
        plausibleMoves[i+offset][1] = plausibleRows[i][1];
    }
    return plausibleRowsCount;
}

int plausibleMoves_Columns(int offset) {
    // check each column, if the column has > n/2 player pieces and no bot pieces, then add the empty spaces to plausibleMoves
    int plausibleColumns[boardSize*boardSize][2];
    int plausibleColumnsCount = 0;
    for (int i = 0; i < boardSize; i++) {
        int playerPieces = 0;
        int botPieces = 0;
        for (int j = 0; j < boardSize; j++) {
            if (board[j][i] == playerPiece) {
                playerPieces++;
            } else if (board[j][i] == botPiece) {
                botPieces++;
            }
        }
        if (playerPieces > boardSize/2 && botPieces == 0) {
            for (int j = 0; j < boardSize; j++) {
                if (board[j][i] == space) {
                    plausibleColumns[plausibleColumnsCount][0] = j;
                    plausibleColumns[plausibleColumnsCount][1] = i;
                    plausibleColumnsCount++;
                }
            }
        }
    }

    // add plausibleColumns to plausibleMoves
    for (int i = 0; i < plausibleColumnsCount; i++) {
        plausibleMoves[i+offset][0] = plausibleColumns[i][0];
        plausibleMoves[i+offset][1] = plausibleColumns[i][1];
    }
    return plausibleColumnsCount;
}

int plausibleMoves_Diagonals (int offset) {
    // check the two diagonals, if the diagonals have > n/2 player pieces and no bot pieces, then add the empty spaces to plausibleMoves
    int plausibleDiagonals[boardSize*boardSize][2];
    int plausibleDiagonalsCount = 0;
    int playerPieces = 0;
    int botPieces = 0;

    // check the first diagonal
    for (int i = 0; i < boardSize; i++) {
        if (board[i][i] == playerPiece) {
            playerPieces++;
        } else if (board[i][i] == botPiece) {
            botPieces++;
        }
    }
    if (playerPieces > boardSize/2 && botPieces == 0) {
        for (int i = 0; i < boardSize; i++) {
            if (board[i][i] == space) {
                plausibleDiagonals[plausibleDiagonalsCount][0] = i;
                plausibleDiagonals[plausibleDiagonalsCount][1] = i;
                plausibleDiagonalsCount++;
            }
        }
    }

    playerPieces = 0; botPieces = 0;

    // check the second diagonal
    for (int i=0; i < boardSize; i++) {
        if (board[i][boardSize-i-1] == playerPiece) {
            playerPieces++;
        } else if (board[i][boardSize-i-1] == botPiece) {
            botPieces++;
        }
    }

    if (playerPieces > boardSize/2 && botPieces == 0) {
        for (int i = 0; i < boardSize; i++) {
            if (board[i][boardSize-i-1] == space) {
                plausibleDiagonals[plausibleDiagonalsCount][0] = i;
                plausibleDiagonals[plausibleDiagonalsCount][1] = boardSize-i-1;
                plausibleDiagonalsCount++;
            }
        }
    }

    for (int i = 0; i < plausibleDiagonalsCount; i++) {
        plausibleMoves[i+offset][0] = plausibleDiagonals[i][0];
        plausibleMoves[i+offset][1] = plausibleDiagonals[i][1];
    }

    return plausibleDiagonalsCount;
}

int checkWin_Row (char piece) {
    for (int i = 0; i < boardSize; i++) {
        int pieces = 0;
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == piece) {
                pieces++;
            }
        }
        if (pieces == boardSize) {
            return 1;
        }
    }
    return 0;
}

int checkWin_Column(char piece) {
    for (int i = 0; i < boardSize; i++) {
        int pieces = 0;
        for (int j = 0; j < boardSize; j++) {
            if (board[j][i] == piece) {
                pieces++;
            }
        }
        if (pieces == boardSize) {
            return 1;
        }
    }
    return 0;
}

int checkWin_Diagonals(char piece) {
    int pieces = 0;
    for (int i = 0; i < boardSize; i++) {
        if (board[i][i] == piece) {
            pieces++;
        }
    }
    if (pieces == boardSize) {
        return 1;
    }

    pieces = 0;
    for (int i = 0; i < boardSize; i++) {
        if (board[i][boardSize-i-1] == piece) {
            pieces++;
        }
    }
    if (pieces == boardSize) {
        return 1;
    }
    return 0;
}

int winningMoves_Row (int offset) {
    // check each row, if the row has n-1 pieces of the bot and one empty space, then add the empty space to winningMoves
    int winningRowsCount = 0;
    for (int i = 0; i < boardSize; i++) {
        int botPieces = 0;
        int emptySpaces = 0;
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == botPiece) {
                botPieces++;
            } else if (board[i][j] == space) {
                emptySpaces++;
            }
        }
        if (botPieces == boardSize-1 && emptySpaces == 1) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == space) {
                    winningMoves[offset+winningRowsCount][0] = i;
                    winningMoves[offset+winningRowsCount][1] = j;
                    winningRowsCount++;
                }
            }
        }
    }
    return winningRowsCount;
}

int winningMoves_Column (int offset) {
    // check each column, if the column has n-1 pieces of the bot and one empty space, then add the empty space to winningMoves
    int winningColumnsCount = 0;
    for (int i = 0; i < boardSize; i++) {
        int botPieces = 0;
        int emptySpaces = 0;
        for (int j = 0; j < boardSize; j++) {
            if (board[j][i] == botPiece) {
                botPieces++;
            } else if (board[j][i] == space) {
                emptySpaces++;
            }
        }
        if (botPieces == boardSize-1 && emptySpaces == 1) {
            for (int j = 0; j < boardSize; j++) {
                if (board[j][i] == space) {
                    winningMoves[offset+winningColumnsCount][0] = j;
                    winningMoves[offset+winningColumnsCount][1] = i;
                    winningColumnsCount++;
                }
            }
        }
    }
    return winningColumnsCount;
}

int winningMoves_Diagonals (int offset) {
    // check the two diagonals, if the diagonals have n-1 pieces of the bot and one empty space, then add the empty space to winningMoves
    int winningDiagonalsCount = 0;
    int botPieces = 0;
    int emptySpaces = 0;

    // check the first diagonal
    for (int i = 0; i < boardSize; i++) {
        if (board[i][i] == botPiece) {
            botPieces++;
        } else if (board[i][i] == space) {
            emptySpaces++;
        }
    }
    if (botPieces == boardSize-1 && emptySpaces == 1) {
        for (int i = 0; i < boardSize; i++) {
            if (board[i][i] == space) {
                winningMoves[offset+winningDiagonalsCount][0] = i;
                winningMoves[offset+winningDiagonalsCount][1] = i;
                winningDiagonalsCount++;
            }
        }
    }

    botPieces = 0; emptySpaces = 0;

    // check the second diagonal
    for (int i=0; i < boardSize; i++) {
        if (board[i][boardSize-i-1] == botPiece) {
            botPieces++;
        } else if (board[i][boardSize-i-1] == space) {
            emptySpaces++;
        }
    }

    if (botPieces == boardSize-1 && emptySpaces == 1) {
        for (int i = 0; i < boardSize; i++) {
            if (board[i][boardSize-i-1] == space) {
                winningMoves[offset+winningDiagonalsCount][0] = i;
                winningMoves[offset+winningDiagonalsCount][1] = boardSize-i-1;
                winningDiagonalsCount++;
            }
        }
    }

    return winningDiagonalsCount;
}

int checkWin (char piece) {
    if (checkWin_Row(piece) || checkWin_Column(piece) || checkWin_Diagonals(piece)) {
        return 1;
    }
    return 0;
}

int checkDraw () {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == space) {
                return 0;
            }
        }
    }
    return 1;
}

void clearScreen () {
    int result = strcmp(os, "windows");
    if (result == 1) {
        system("cls");
    } else {
        system("clear");
    }
}

#endif //ALGORITHM
