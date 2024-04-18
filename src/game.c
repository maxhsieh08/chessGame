#include "game.h"
#include <stdio.h>
#include <stdbool.h>
static unsigned int fileToIndex (unsigned char File);

void movePiece(Piece *board[8][8], enum PlayerColor pColor, unsigned int startFile, unsigned int startRank, unsigned int endFile, unsigned int endRank) {
    unsigned int fileIndex1 = fileToIndex(startFile);
    unsigned int fileIndex2 = fileToIndex(endFile);
    unsigned int rankIndex1 = 8 - startRank;
    unsigned int rankIndex2 = 8 - endRank;
    if (isValidMove(board, pColor, fileIndex1, rankIndex1, fileIndex2, rankIndex2)) {
        Piece *temp = board[rankIndex1][fileIndex1];
        board[rankIndex2][fileIndex2] = temp;
        board[rankIndex1][fileIndex1] = NULL;
    } else printf("not valid \n");
}

bool isValidMove(Piece *board[8][8], enum PlayerColor pColor, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    int isValid = 1; // Variable to track if any errors are found

    /*check if there is a piece and if there is, check if it is the player's piece*/
    Piece *testPiece = board[startRankIndex][startFileIndex];
    if (testPiece == NULL) {
        printf("no piece here!\n");
        isValid = 0;
    } else if (testPiece->color != pColor) {
        printf("attempting to move enemy piece\n");
        isValid = 0;
    }


    // Check the start file index
    if (startFileIndex < 0 || startFileIndex > 8) {
        printf("Invalid start file index: %d\n", startFileIndex);
        isValid = 0; // Mark that an error was found
    }

    // Check the end file index
    if (endFileIndex < 0 || endFileIndex > 8) {
        printf("Invalid end file index: %d\n", endFileIndex);
        isValid = 0; // Mark that an error was found
    }

    // Check the start rank index
    if (startRankIndex < 0 || startRankIndex > 8) {
        printf("Invalid start rank index: %d\n", startRankIndex);
        isValid = 0; // Mark that an error was found
    }

    // Check the end rank index
    if (endRankIndex < 0|| endRankIndex > 8) {
        printf("Invalid end rank index: %d\n", endRankIndex);
        isValid = 0; // Mark that an error was found
    }

    // Return 0 if any errors were found, otherwise return 1
    return isValid;
}

static unsigned int fileToIndex(unsigned char File) {
    unsigned int h = File - 'a';
    return h;
}
