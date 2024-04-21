#include "game.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    Piece *board[8][8];
    enum PlayerColor p1Color = white;
    enum PlayerColor p2Color = p1Color == white ? black : white;
    unsigned char startFile = ' ';
    unsigned int startRank = 0;
    unsigned char endFile = ' ';
    unsigned int endRank = 0;



    initializeBoard(board, p1Color);
    for (int i = 0; i < 100; i++) {
        do {
        displayBoard(board);
        printf("white's move\n");
        printf("Enter start position (e.g., a2): ");
        scanf(" %c%u", &startFile, &startRank);  // Read file as char and rank as unsigned int

        printf("Enter end position (e.g., b3): ");
        scanf(" %c%u", &endFile, &endRank);      // Read file as char and rank as unsigned int

        // Display the read values for verification
        printf("Moving from %c%u to %c%u\n", startFile, startRank, endFile, endRank);
        }
        while (!movePiece(board, p1Color, p1Color, startFile, startRank, endFile, endRank));
        
        do {
        displayBoard(board);
        printf("black's move\n");
        printf("Enter start position (e.g., a2): ");
        scanf(" %c%u", &startFile, &startRank);  // Read file as char and rank as unsigned int

        printf("Enter end position (e.g., b3): ");
        scanf(" %c%u", &endFile, &endRank);      // Read file as char and rank as unsigned int

        // Display the read values for verification
        printf("Moving from %c%u to %c%u\n", startFile, startRank, endFile, endRank);
        }
        while (!movePiece(board, p2Color, p1Color, startFile, startRank, endFile, endRank));
        displayBoard(board);
    }


    return 0;
}
