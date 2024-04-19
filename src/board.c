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
#endif

static Piece *createNewPiece();
static void  deletePiece(Piece *e);

/* for initially setting pieces */
void initializeBoard(Piece *board[8][8], enum PlayerColor p1Color)
{
    //ternary that sets p2Color to opposite color of white
    enum PlayerColor p2Color = p1Color == black ? white : black;
    unsigned char idCount = 1;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
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
    for (int i = 0; i < 8; i++) {
        board[1][i]->pieceType = Pawn;
        board[1][i]->color = p2Color;
        board[6][i]->pieceType = Pawn;
        board[6][i]->color = p1Color;
    }

    // Initialize rooks
    board[0][0]->pieceType = Rook;
    board[0][7]->pieceType = Rook;
    board[0][0]->color = board[0][7]->color = p2Color;
    board[7][0]->pieceType = Rook;
    board[7][7]->pieceType = Rook;
    board[7][0]->color = board[7][7]->color = p1Color;

    // Initialize knights
    board[0][1]->pieceType = Knight;
    board[0][6]->pieceType = Knight;
    board[0][1]->color = board[0][6]->color = p2Color;
    board[7][1]->pieceType = Knight;
    board[7][6]->pieceType = Knight;
    board[7][1]->color = board[7][6]->color = p1Color;

    // Initialize bishops
    board[0][2]->pieceType = Bishop;
    board[0][5]->pieceType = Bishop;
    board[0][2]->color = board[0][5]->color = p2Color;
    board[7][2]->pieceType = Bishop;
    board[7][5]->pieceType = Bishop;
    board[7][2]->color = board[7][5]->color = p1Color;

    // Initialize queens
    board[0][3]->pieceType = Queen;
    board[0][3]->color = p2Color;
    board[7][3]->pieceType = Queen;
    board[7][3]->color = p1Color;

    // Initialize kings
    board[0][4]->pieceType = King;
    board[0][4]->color = p2Color;
    board[7][4]->pieceType = King;
    board[7][4]->color = p1Color;
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
    for (int i = 0; i < 16; i++) e->takeable[i] = 0;
    e->castle = false;
    e->id = 0;
    e->hasMoved = false;
    return e;
}

static void deletePiece(Piece *e)
{
    assert(e);
    free(e);
    
}


/*Displaying the board in the terminal*/
void displayBoard(Piece *board[8][8])
{
    printf("format: playerColor pieceType\n");
    for (int i = 0; i < 8; i++) {
                    printf("%d ", 8 - i);
        for (int j = 0; j < 8; j++) {
            // Ensure each field has a fixed width
            if (board[i][j] == NULL) {
                printf("|   ");
            } else {
                printf("|%c%2c", board[i][j]->color == white ? 'w' : 'b', board[i][j]->pieceType);
            }
        }
            printf("|\n");
    }
            printf("    a   b   c   d   e   f   g   h\n");
}


/*Flipping orentation of board for Human vs Human play*/
void flipBoard(Piece *board[8][8])
{
    Piece *temp = createNewPiece();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            temp = board[i][j];
            board[i][j] = board[7-i][j];
            board[7-i][j] = temp;
        }
    }
    temp = NULL;
}