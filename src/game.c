#include "game.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
static unsigned int fileToIndex (unsigned char File);

bool movePiece(Piece *board[8][8], enum PlayerColor currentPlayer, enum PlayerColor playerOne, unsigned int startFile, unsigned int startRank, unsigned int endFile, unsigned int endRank) {
    unsigned int startFileIndex = fileToIndex(startFile);
    unsigned int endFileIndex = fileToIndex(endFile);
    unsigned int startRankIndex = 8 - startRank;
    unsigned int endRankIndex = 8 - endRank;
    //printf("starting file: %d\nstarting rank: %d\nend file: %d\nend rank: %d\n", startFileIndex, startRankIndex, endFileIndex, endRankIndex);
    if (isValidMove(board, currentPlayer, startFileIndex, startRankIndex, endFileIndex, endRankIndex)) {
        Piece *temp = board[startRankIndex][startFileIndex];
        bool isMoveValid = false;
        switch (temp->pieceType) {
            case Pawn:
                printf("testing Pawn!\n");
                isMoveValid = validPawnMove(board, currentPlayer, playerOne, startFileIndex, startRankIndex, endFileIndex, endRankIndex);
                break;
            case Rook:
                printf("testing Rook!\n");
                isMoveValid = validRookMove(board, startFileIndex, startRankIndex, endFileIndex, endRankIndex);
                break;
            default:
                printf("still implementing other piece types\n");
                break;
        }

        if (isMoveValid) {
            printf("valid %s move!\n", temp->pieceType == Pawn ? "pawn" : "rook"); // Adjusted dynamically for other types as implemented
            temp->hasMoved = 1;
            board[endRankIndex][endFileIndex] = temp;
            board[startRankIndex][startFileIndex] = NULL;
            return true;
        }
        return false;
    } else printf("not valid, try again! \n");
    return false;
}

/*checks if piece is NULL, then tests if matches player's color.*/
/*also tests if move is within bounds of board as well as if it is attempting to take a friendly piece*/
bool isValidMove(Piece *board[8][8], enum PlayerColor currentPlayer, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
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
    } else if (testPiece->color != currentPlayer) {
        printf("attempting to move enemy piece!\n");
        isValid = 0;
    }
    /*check if moving onto friendly piece*/
    if(board[endRankIndex][endFileIndex] != NULL && board[endRankIndex][endFileIndex]->color == currentPlayer) {
        printf("attempting to take friendly piece!\n");
        isValid = 0;
    }
    return isValid;
}

bool validPawnMove(Piece *board[8][8], enum PlayerColor currentPlayer, enum PlayerColor playerOne, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    enum PlayerColor opponentColor = (currentPlayer == white) ? black : white;
    Piece *movingPiece = board[startRankIndex][startFileIndex];
    Piece *destinationPiece = board[endRankIndex][endFileIndex];

    // Calculate rank difference considering the player's movement direction
    unsigned int rankDiff;
    if (currentPlayer == playerOne) {
        rankDiff = (startRankIndex >= endRankIndex) ? (startRankIndex - endRankIndex) : 0;
    } else {
        rankDiff = (endRankIndex >= startRankIndex) ? (endRankIndex - startRankIndex) : 0;
    }

    unsigned int fileDiff = abs((int)endFileIndex - (int)startFileIndex);
    
    // Ensure the pawn moves forward
    if (rankDiff == 0) return false;

    // Maximum rank difference based on whether the pawn has moved before
    unsigned int maxRankDiff = movingPiece->hasMoved ? 1 : 2;

    // Capture logic
    if (destinationPiece != NULL && destinationPiece->color == opponentColor) {
        return (rankDiff == 1 && fileDiff == 1);
    }

    // check that pawn is not jumping over pieces
    if (rankDiff == 2 && board[(startRankIndex + endRankIndex) / 2][startFileIndex] != NULL) {
        return false;
    }

    // Regular move forward
    return fileDiff == 0 && rankDiff > 0 && rankDiff <= maxRankDiff;
}

bool validRookMove(Piece *board[8][8], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    /*check if either rank or file is the same. if not, return false*/
    if (startFileIndex != endFileIndex && startRankIndex != endRankIndex) return false;
    // Determine the direction of the move
    int rankDirection = (endRankIndex > startRankIndex) ? 1 : (endRankIndex < startRankIndex) ? -1 : 0;
    int fileDirection = (endFileIndex > startFileIndex) ? 1 : (endFileIndex < startFileIndex) ? -1 : 0;

    // Check for blockages in the path
    unsigned int checkFile = startFileIndex + fileDirection;
    unsigned int checkRank = startRankIndex + rankDirection;
    while (checkFile != endFileIndex || checkRank != endRankIndex) {
        if (board[checkRank][checkFile] != NULL) {
            return false; // There is a blockage
        }
        checkFile += fileDirection;
        checkRank += rankDirection;
    }
    return true;
}

static unsigned int fileToIndex(unsigned char File) {
    unsigned int h = File - 'a';
    return h;
}
