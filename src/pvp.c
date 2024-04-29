#include "Constants.h"
#include "game.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Piece *board[MAX_FILE][MAX_RANK];
    enum PlayerColor p1Color = white;
    enum PlayerColor p2Color = p1Color == white ? black : white;
    Moves *input = createNewMove();
    printf("Welcome to Chess Game\n");
    initializeBoard(board, p1Color);
    for (int i = 0; i < 100; i++) {
        do {
            displayBoard(board);
            printf("white's move.\n");
            printf("Enter start position (e.g., a2): ");
            scanf(" %c%u", &input->startFile, &input->startRank);  // Read file as char and rank as unsigned int

            printf("Enter end position (e.g., b3): ");
            scanf(" %c%u", &input->endFile, &input->endRank);
            convertCoordinates(input);      // Read file as char and rank as unsigned int

        }
        
        while (!isValidMove(board, p1Color, input->startFile, input->startRank, input->endFile, input->endRank));
        movePiece(board, input->startFile, input->startRank, input->endFile, input->endRank);

        do {
            displayBoard(board);
        //testing
            printf("black's move\n");
            printf("Enter start position (e.g., a2): ");
            scanf(" %c%u", &input->startFile, &input->startRank);  // Read file as char and rank as unsigned int

            printf("Enter end position (e.g., b3): ");
            scanf(" %c%u", &input->endFile, &input->endRank);
            convertCoordinates(input);      // Read file as char and rank as unsigned int
        }
        while (!isValidMove(board, p1Color, input->startFile, input->startRank, input->endFile, input->endRank));
        displayBoard(board);
        movePiece(board, input->startFile, input->startRank, input->endFile, input->endRank);
    }


    return 0;
}