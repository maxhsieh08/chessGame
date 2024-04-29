#include "Constants.h"
#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef BOARD_C
#define BOARD_C


static Piece *createNewPiece();

/* for initially setting pieces */
void initializeBoard(Piece *board[MAX_FILE][MAX_RANK])
{
    //ternary that sets black to opposite color of white
    //enum PlayerColor black = white == black ? white : black;
    unsigned char idCount = 1;
    for(unsigned int i = 0; i < MAX_FILE; i++) {
        for(unsigned int j = 0; j < MAX_RANK; j++) {
            /*create a piece*/
            if(i <= 1 || i >=6) {
                board[i][j] = createNewPiece();
                board[i][j]->id = idCount;
                idCount++;
                board[i][j]->file = j + 'a';
                board[i][j]->rank = 8 - i;
            } else board[i][j] = NULL;
            /*add current rank and file*/

        }
    }

    // Initialize pawns for both black and white
    for (unsigned int i = 0; i < 8; i++) {
        board[1][i]->pieceType = Pawn;
        board[1][i]->color = black;
        board[6][i]->pieceType = Pawn;
        board[6][i]->color = white;
    }

    // Initialize rooks
    board[0][0]->pieceType = Rook;
    board[0][7]->pieceType = Rook;
    board[0][0]->color = board[0][7]->color = black;
    board[7][0]->pieceType = Rook;
    board[7][7]->pieceType = Rook;
    board[7][0]->color = board[7][7]->color = white;

    // Initialize knights
    board[0][1]->pieceType = Knight;
    board[0][6]->pieceType = Knight;
    board[0][1]->color = board[0][6]->color = black;
    board[7][1]->pieceType = Knight;
    board[7][6]->pieceType = Knight;
    board[7][1]->color = board[7][6]->color = white;

    // Initialize bishops
    board[0][2]->pieceType = Bishop;
    board[0][5]->pieceType = Bishop;
    board[0][2]->color = board[0][5]->color = black;
    board[7][2]->pieceType = Bishop;
    board[7][5]->pieceType = Bishop;
    board[7][2]->color = board[7][5]->color = white;

    // Initialize queens
    board[0][3]->pieceType = Queen;
    board[0][3]->color = black;
    board[7][3]->pieceType = Queen;
    board[7][3]->color = white;

    // Initialize kings
    board[0][4]->pieceType = King;
    board[0][4]->color = black;
    board[7][4]->pieceType = King;
    board[7][4]->color = white;
}

/* Create new pieces for initialization of board*/
static Piece *createNewPiece()
{
    Piece *e;
    e = malloc(sizeof(Piece));
    if(!e)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    e->pieceType = noChar;
    e->color = noColor;
    e->rank = 'N';
    e->file = 'N';
    e->prevRank = 'N';
    e->prevFile = 'N';
    e->enPassant = false;
    for (unsigned int i = 0; i < 16; i++) e->takeable[i] = 0;
    e->castle = false;
    e->id = 0;
    e->hasMoved = false;
    e->inCheck = false;
    return e;
}

void deletePiece(Piece *e)
{
    assert(e);
    free(e);
    e = NULL;
    
}


/*Displaying the board in the terminal*/
void displayBoard(Piece *board[MAX_RANK][MAX_FILE], enum PlayerColor currentPlayer)
{
    printf("format: playerColor pieceType\n");
    if(currentPlayer == white) {
    for (unsigned int i = 0; i < MAX_RANK; i++) {
        printf("\033[0m%d ", 8-i);
        for (unsigned int j = 0; j < MAX_FILE; j++) {
            // Ensure each field has a fixed width
            if (board[i][j] == NULL) {
                printf("|___");
            } else {
                printf("|\033[4m%c%2c", board[i][j]->color == white ? 'w' : 'b', board[i][j]->pieceType);
            }
        }
            printf("|\n");
    }
            printf("\033[0m    a   b   c   d   e   f   g   h\n");
    } else {
    for (int i = (int)MAX_RANK - 1; i >= 0; i--) {  // Start from the last rank, decrementing to the first
        printf("\033[0m%d ", 8 - i);  // Print rank numbers correctly
        for (int j = (int)MAX_FILE - 1; j >= 0; j--) {
            // Ensure each field has a fixed width
            if (board[i][j] == NULL) {
                printf("|___");
            } else {
                printf("|\033[4m%c%2c", board[i][j]->color == white ? 'w' : 'b', board[i][j]->pieceType);
            }
        }
        printf("|\n");
    }
    printf("\033[0m    h   g   f   e   d   c   b   a\n");
}

}


/*Flipping orentation of board for Human vs Human play*/
void flipBoard(Piece *board[MAX_FILE][MAX_RANK])
{
    Piece *temp = createNewPiece();
    for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < MAX_FILE; j++) {
            temp = board[i][j];
            board[i][j] = board[7-i][j];
            board[7-i][j] = temp;
        }
    }
    temp = NULL;
}
#endif