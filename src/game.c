#include "game.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
static unsigned int fileToIndex (unsigned char File);

bool movePiece(Piece *board[8][8], enum PlayerColor pColor, enum PlayerColor p1Color, unsigned int startFile, unsigned int startRank, unsigned int endFile, unsigned int endRank) {
    unsigned int fileIndex1 = fileToIndex(startFile);
    unsigned int fileIndex2 = fileToIndex(endFile);
    unsigned int rankIndex1 = 8 - startRank;
    unsigned int rankIndex2 = 8 - endRank;
    //printf("starting file: %d\nstarting rank: %d\nend file: %d\nend rank: %d\n", fileIndex1, rankIndex1, fileIndex2, rankIndex2);
    if (isValidMove(board, pColor, fileIndex1, rankIndex1, fileIndex2, rankIndex2)) {
        Piece *temp = board[rankIndex1][fileIndex1];
        switch(temp->pieceType) {
            case Pawn: 
                printf("testing Pawn!\n");
                if (validPawnMove(board, pColor, p1Color, fileIndex1, rankIndex1, fileIndex2, rankIndex2)) {
                    printf("valid pawn move!\n");
                    temp->hasMoved = 1;
                    board[rankIndex2][fileIndex2] = temp;
                    board[rankIndex1][fileIndex1] = NULL;
                     return true;
                }
            default: 
                printf("still implementing other piece types\n");
                break;
        }
    } else printf("not valid, try again! \n");
    return false;
}

/*checks if piece is NULL, then tests if matches player's color.*/
/*also tests if move is within bounds of board as well as if it is attempting to take a friendly piece*/
bool isValidMove(Piece *board[8][8], enum PlayerColor pColor, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    bool isValid = 1; // Variable to track if any errors are found
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
    if (isValid == 0) return isValid;

    /*check if there is a piece and if there is, check if it is the player's piece*/
    Piece *testPiece = board[startRankIndex][startFileIndex];
    if (testPiece == NULL) {
        printf("no piece here!\n");
        isValid = 0;
    } else if (testPiece->color != pColor) {
        printf("attempting to move enemy piece\n");
        isValid = 0;
    }
    /*check if moving onto friendly piece*/
    if(board[endRankIndex][endFileIndex] != NULL && board[endRankIndex][endFileIndex]->color == pColor) {
        printf("attempting to take friendly piece!\n");
        isValid = 0;
    }
    return isValid;
}

bool validPawnMove(Piece *board[8][8], enum PlayerColor pColor, enum PlayerColor p1Color, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    enum PlayerColor otherColor = pColor == white ? black : white;
    Piece *testPiece = board[startRankIndex][startFileIndex];
    Piece *destination = board[endRankIndex][endFileIndex];
    unsigned int rankDiff;
    /*calculate the difference in rank which takes into account how the board is oriented and wraparound of unsigned int*/
    if (pColor == p1Color) {
        if (startRankIndex >= endRankIndex) {
            rankDiff = startRankIndex - endRankIndex;
        } else rankDiff = 0;
    } else {
        if (endRankIndex >= startRankIndex) {
            rankDiff = endRankIndex - startRankIndex;
        } else rankDiff = 0;
    }
    unsigned int maxRankDiff = testPiece->hasMoved ? 1 : 2; // If moved, max diff is 1; if not, it's 2
    unsigned int fileDiff = startFileIndex > endFileIndex ? 
               startFileIndex - endFileIndex : 
               endFileIndex - startFileIndex;
    if(destination!= NULL && destination->color == otherColor) {
        if(otherColor && rankDiff == 1 && fileDiff == 1) {
            return true;
        } else return false;
    }
    /*check if pawn is attempting to jump over a piece*/
    if (rankDiff == 2 && board[(startRankIndex + endRankIndex)/2][startFileIndex] != NULL) return false;
    if (startFileIndex == endFileIndex && rankDiff > 0 && rankDiff <= maxRankDiff) return true;

    return false;

}

static unsigned int fileToIndex(unsigned char File) {
    unsigned int h = File - 'a';
    return h;
}
