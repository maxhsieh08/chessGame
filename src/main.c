#include "game.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    Piece *board[8][8];
    enum PlayerColor p1Color = white;
    enum PlayerColor otherPlayer = p1Color == white ? black : white;
    unsigned char startFile = ' ';
    unsigned int startRank = ' ';
    unsigned char endFile = ' ';
    unsigned int endRank = ' ';


    initializeBoard(board, p1Color);
    for (int i = 0; i < 4; i++) {
        do {
        displayBoard(board);
        printf("white's move\n");
        scanf(" %c", &startFile);
        scanf(" %d", &startRank);
        scanf(" %c", &endFile);
        scanf(" %d", &endRank);
        }
        while (!movePiece(board, p1Color, p1Color, startFile, startRank, endFile, endRank));

        do {
        displayBoard(board);
        printf("black's move\n");
        scanf(" %c", &startFile);
        scanf(" %d", &startRank);
        scanf(" %c", &endFile);
        scanf(" %d", &endRank);
        }
        while (!movePiece(board, otherPlayer, p1Color, startFile, startRank, endFile, endRank));
        displayBoard(board);
    }


    return 0;
}
