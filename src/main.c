#include "game.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    Piece *board[8][8];
    enum PlayerColor mux = white;
    unsigned char startFile = ' ';
    unsigned int startRank = ' ';
    unsigned char endFile = ' ';
    unsigned int endRank = ' ';


    initializeBoard(board, mux);
    displayBoard(board);
    printf("white's move\n");
    for (int i = 0; i < 4; i++) {
        enum PlayerColor otherPlayer = mux == white ? black : white;
        scanf(" %c", &startFile);
        scanf(" %d", &startRank);
        scanf(" %c", &endFile);
        scanf(" %d", &endRank);
        movePiece(board, mux, startFile, startRank, endFile, endRank);
        flipBoard(board);
        displayBoard(board);
        scanf(" %c", &startFile);
        scanf(" %d", &startRank);
        scanf(" %c", &endFile);
        scanf(" %d", &endRank);
        movePiece(board, otherPlayer, startFile, startRank, endFile, endRank);
        printf("piece moved\n");
        flipBoard(board);
        printf("board flipped\n");
        displayBoard(board);
    }


    //flipBoard(board);
    //displayBoard(board);
    return 0;
}
