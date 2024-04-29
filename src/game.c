#include "Constants.h"
#include "game.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
static unsigned char fileToIndex (unsigned char File);
bool isValidMove(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor currentPlayer, Moves *input) {
    unsigned int startFileIndex = input->startFile;
    unsigned int startRankIndex = input->startRank;
    unsigned int endFileIndex = input->endFile;
    unsigned int endRankIndex = input->endRank;
    bool canCastle = true;
    if (checkSpace(board, currentPlayer, startFileIndex, startRankIndex, endFileIndex, endRankIndex)) {
        Piece *temp = board[startRankIndex][startFileIndex];
        bool isMoveValid = false;
        switch (temp->pieceType) {
            case Pawn:
                printf("testing Pawn!\n");
                isMoveValid = validPawnMove(board, startFileIndex, startRankIndex, endFileIndex, endRankIndex);
                break;
            case Rook:
                printf("testing Rook!\n");
                isMoveValid = validRookMove(board, startFileIndex, startRankIndex, endFileIndex, endRankIndex);
                break;
            /*other piece type moevements*/
            case Bishop:
                printf("testing Bishop!\n");
                isMoveValid = validBishopMove(board, startFileIndex, startRankIndex, endFileIndex, endRankIndex);
                break;
            case Knight:
                printf("testing Knight!\n");
                isMoveValid = validKnightMove(startFileIndex, startRankIndex, endFileIndex, endRankIndex);
                break;
            case Queen:
                printf("testing Queen!\n");
                isMoveValid = validQueenMove(board, startFileIndex, startRankIndex, endFileIndex, endRankIndex);
                break;
            case King:
                printf("testing King!\n");
                if (temp->hasMoved != 0) canCastle = false;
                isMoveValid = validKingMove(board, startFileIndex, startRankIndex, endFileIndex, endRankIndex, canCastle);
                break;
            default:
                printf("error: no piece type detected.\n");
                break;
        }

        if (isMoveValid) {
            printf("valid %s move!\n", temp->pieceType == Pawn ? "pawn" : (temp->pieceType == Rook ? "rook" : (temp->pieceType == Bishop) ? "bishop" : (temp->pieceType == Queen) ? "queen" : (temp->pieceType == Knight) ? "knight" : "king"));
            return true;
        }
    } else printf("move not valid!\n");
    return false;
}

/*checks if piece is NULL, then tests if matches player's color.*/
/*also tests if move is within bounds of board as well as if it is attempting to take a friendly piece*/
bool checkSpace(Piece *board[MAX_RANK][MAX_FILE], enum PlayerColor currentPlayer, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    bool isValid = 1; // Variable to track if any errors are found
    // Check the start file index
    if (startFileIndex == endFileIndex && startRankIndex == endRankIndex){
        printf("attempting to move to the same square!\n");
        isValid = 0;
    }
    if (startFileIndex > MAX_FILE-1) {
        printf("Invalid start file index: %d\n", startFileIndex);
        isValid = 0; // Mark that an error was found
    }

    // Check the end file index
    if (endFileIndex > MAX_FILE-1) {
        printf("Invalid end file index: %d\n", endFileIndex);
        isValid = 0; // Mark that an error was found
    }

    // Check the start rank index
    if (startRankIndex > MAX_RANK-1) {
        printf("Invalid start rank index: %d\n", startRankIndex);
        isValid = 0; // Mark that an error was found
    }

    // Check the end rank index
    if (endRankIndex > MAX_RANK-1) {
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

bool validPawnMove(Piece *board[MAX_FILE][MAX_RANK], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    enum PlayerColor currentPlayer= board[startRankIndex][startFileIndex]->color;
    enum PlayerColor opponentColor = (currentPlayer == white) ? black : white;
    Piece *movingPiece = board[startRankIndex][startFileIndex];
    Piece *destinationPiece = board[endRankIndex][endFileIndex];

    // Calculate rank difference considering the player's movement direction
    unsigned int rankDiff;
    if (currentPlayer == white) {
        rankDiff = (startRankIndex >= endRankIndex) ? (startRankIndex - endRankIndex) : 0;
    } else {
        rankDiff = (endRankIndex >= startRankIndex) ? (endRankIndex - startRankIndex) : 0;
    }

    unsigned int fileDiff = abs((int)endFileIndex - (int)startFileIndex);

    // Ensure the pawn moves forward
    if (rankDiff == 0) {
        return false;
    }

    // Maximum rank difference based on whether the pawn has moved before
    unsigned int maxRankDiff = movingPiece->hasMoved ? 1 : 2;

    // Capture logic
    if (destinationPiece != NULL && destinationPiece->color == opponentColor) {
        return (rankDiff == 1 && fileDiff == 1);
    }

    // check that pawn is not jumping over pieces
    if (rankDiff == 2 && board[(startRankIndex + endRankIndex) / 2][startFileIndex] != NULL) {
        printf("piece in the path of destination!\n");
        return false;
    }

    // Regular move forward
    return fileDiff == 0 && rankDiff > 0 && rankDiff <= maxRankDiff;
}

bool validRookMove(Piece *board[MAX_FILE][MAX_RANK], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    /*check if either rank or file is the same. if not, return false*/
    if (startFileIndex != endFileIndex && startRankIndex != endRankIndex) {
        printf("attempting to move in a manner not horizontally/vertically!\n");
        return false;
    }
    
    // Determine the direction of the move
    int rankDirection = (endRankIndex > startRankIndex) ? 1 : (endRankIndex < startRankIndex) ? -1 : 0;
    int fileDirection = (endFileIndex > startFileIndex) ? 1 : (endFileIndex < startFileIndex) ? -1 : 0;

    // Check for blockages in the path
    unsigned int checkFile = startFileIndex + fileDirection;
    unsigned int checkRank = startRankIndex + rankDirection;
    while (checkFile != endFileIndex || checkRank != endRankIndex) {
        if (board[checkRank][checkFile] != NULL) {
            printf("pieces in the path of destination!\n");
            return false; // There is a blockage
        }
        checkFile += fileDirection;
        checkRank += rankDirection;
    }
    return true;
}

bool validBishopMove (Piece *board[MAX_FILE][MAX_RANK], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    if (startFileIndex == endFileIndex || startRankIndex == endRankIndex) return false;

    /* check if ranke and file difference are the same, if not return false*/
    int fileDiff = abs((int)endFileIndex - (int)startFileIndex);
    int rankDiff = abs((int)endRankIndex - (int)startRankIndex);

    if(rankDiff != fileDiff) return false;

    int rankDirection = (endRankIndex > startRankIndex) ? 1 : (endRankIndex < startRankIndex) ? -1 : 0;
    int fileDirection = (endFileIndex > startFileIndex) ? 1 : (endFileIndex < startFileIndex) ? -1 : 0;

    // Check for blockages in the path
    unsigned int checkFile = startFileIndex + fileDirection;
    unsigned int checkRank = startRankIndex + rankDirection;
    while (checkFile != endFileIndex || checkRank != endRankIndex) {
        if (board[checkRank][checkFile] != NULL) {
            printf("pieces in the path of destination!\n");
            return false; // There is a blockage
        }
        checkFile += fileDirection;
        checkRank += rankDirection;
    }
    return true;
}


bool validQueenMove (Piece *board[MAX_FILE][MAX_RANK], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {

    /* check if ranke and file difference are the same, if not return false*/
    int fileDiff = abs((int)endFileIndex - (int)startFileIndex);
    int rankDiff = abs((int)endRankIndex - (int)startRankIndex);

    /*first check if attempting to move diagonally, then if not check if attempting to move horizontally or vertically*/
    if(fileDiff != rankDiff && ((startRankIndex != endRankIndex) && (startFileIndex != endFileIndex))) {
        printf("attempting to move in a manner not diagonally/horizontally/vertically!\n");
        return false;
    }
    int rankDirection = (endRankIndex > startRankIndex) ? 1 : (endRankIndex < startRankIndex) ? -1 : 0;
    int fileDirection = (endFileIndex > startFileIndex) ? 1 : (endFileIndex < startFileIndex) ? -1 : 0;

    // Check for blockages in the path
    unsigned int checkFile = startFileIndex + fileDirection;
    unsigned int checkRank = startRankIndex + rankDirection;
    while (checkFile != endFileIndex || checkRank != endRankIndex) {
        if (board[checkRank][checkFile] != NULL) {
            printf("pieces in the path of destination!\n");
            return false; // There is a blockage
        }
        checkFile += fileDirection;
        checkRank += rankDirection;
    }
    return true;
}

bool validKnightMove (unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex) {
    int fileDiff = abs((int)endFileIndex - (int)startFileIndex);
    int rankDiff = abs((int)endRankIndex - (int)startRankIndex);
    return ((rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2));
}
bool validKingMove(Piece *board[MAX_RANK][MAX_FILE], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex, bool canCastle) {
    enum PlayerColor currentPlayer = board[startRankIndex][startFileIndex]->color;
    int fileDiff = (int)endFileIndex - (int)startFileIndex;
    int rankDiff = abs((int)endRankIndex - (int)startRankIndex);
    // Normal king movement check
    if (abs(fileDiff) <= 1 && rankDiff <= 1) {
        return true;
    }

    // Castling move check
    printf("checking castling conditions!\n");
    if (canCastle && rankDiff == 0 && abs(fileDiff) == 2) {
        // Determine direction of castling (kingside or queenside)
        int fileDirection = (fileDiff > 0) ? 1 : -1;

        // Check if the king is in check or moving through check
        if ((!isSafe(board, currentPlayer,  startFileIndex, startRankIndex)) ||
            (!isSafe(board, currentPlayer, startFileIndex + fileDirection, startRankIndex)) ||
            (!isSafe(board, currentPlayer, endFileIndex, startRankIndex))) {
                printf("king is in check/moving through check!\n");
            return false;
        }
        printf("king is not moving through check!\n");

        // Check if the king and rook have not moved and there are no pieces in between
        unsigned int rookFileIndex = (fileDirection > 0) ? MAX_FILE - 1 : 0;  // Kingside rook is on the last file, queenside rook on the first
        if (board[startRankIndex][rookFileIndex] == NULL) {
            printf("no rook here!\n");
            return false;
        }
        Piece* rook = board[startRankIndex][rookFileIndex];
        if (!rook || rook->hasMoved > 0 || rook->pieceType != Rook) {
            printf("rook has moved/no rook here\n");
            return false;
        }
        printf("checking for blockages\n");
        unsigned int checkFile = startFileIndex + fileDirection;
        while (checkFile != rookFileIndex) {
            if (board[startRankIndex][checkFile] != NULL) {
                printf("piece in the way!\n");
                return false;  // Found a piece in the way
            }
            checkFile += fileDirection;
        }
        return true;  // All castling conditions met
    }
    return false;  // Not a valid move
}

static unsigned char fileToIndex(unsigned char File) {
    unsigned char h = File - 'a';
    return h;
}

Moves *createNewMove()
{
    Moves *e;
    e = malloc(sizeof(Moves));
    if(!e)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    e->startFile = 0;
    e->startFile = 0;
    e->endFile = 0;
    e->endRank = 0;
    e->moveValue = 0;
    e->endPtr = NULL;
    return e;
}
// end testing for ai
void convertCoordinates (Moves *input) {
    input->startFile = fileToIndex(input->startFile);
    input->endFile = fileToIndex(input->endFile);
    input->startRank = 8 - input->startRank;
    input->endRank = 8 - input->endRank;
}

void movePiece(Piece *board[MAX_FILE][MAX_RANK], Moves *input, bool checking) {
    unsigned int startFileIndex = input->startFile;
    unsigned int startRankIndex = input->startRank;
    unsigned int endFileIndex = input->endFile;
    unsigned int endRankIndex = input->endRank;
    int fileDiff = (int)input->endFile - (int)input->startFile;
    int fileDirection = (fileDiff > 0) ? 1 : -1;
    unsigned int rookFileIndex = (fileDirection > 0) ? MAX_FILE - 1 : 0;
    Piece *temp = board[startRankIndex][startFileIndex];
    switch(temp->pieceType) {
        case King:
            if(abs(fileDiff) == 2) {
                Piece *rook = board[startRankIndex][rookFileIndex];
                if(!checking) rook->hasMoved++;
                board[startRankIndex][endFileIndex - fileDirection] = rook;
                board[startRankIndex][rookFileIndex] = NULL;
            }
        default:
            input->endPtr = board[endRankIndex][endFileIndex];
            if(!checking)temp->hasMoved++;
            board[endRankIndex][endFileIndex] = temp;
            board[startRankIndex][startFileIndex] = NULL;

    }
}

bool isSafe(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor currentPlayer, unsigned int fileIndex, unsigned int rankIndex) {
    Moves *move = createNewMove();
    move->endFile = fileIndex;
    move->endRank = rankIndex;
    enum PlayerColor opponentColor = currentPlayer == white ? black : white;
    for(unsigned int i = 0; i < MAX_RANK; i++) {
        for(unsigned int j = 0; j < MAX_FILE; j++) {
            Piece *temp = board[i][j];
            if(temp == NULL || temp->color != opponentColor) continue;
            move->startFile = j;
            move->startRank = i;
            //specific check if pawn is just attempting to move forward
            switch(temp->pieceType) {
                case Pawn:
                    if (isValidMove(board, opponentColor, move) && (fileIndex != j)) {
                    printf("space is under attack from %c%d\n", j + 'a', 8-i);
                    return false;
                }
                    break;
            
                default: 
                    if (isValidMove(board, opponentColor, move)) {
                    printf("space is under attack from %c%d\n", j + 'a', 8-i);
                    return false;
            }
        }
    }
}
    printf("space is safe!\n");
    free(move);
    return true;
}

// bool isCheck(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor playerOne, unsigned int fileIndex, unsigned int rankIndex) {
//     Piece *temp = board[rankIndex][fileIndex];
//     enum PlayerColor currentPlayer = temp->color;
//     if (!isSafe(board, currentPlayer, fileIndex, rankIndex) && temp->pieceType == King) {
//         temp->inCheck = true;
//         printf("%s king in check!\n", currentPlayer == white ? "white" : "black");
//         return true;
//     }
//     return false;
// }