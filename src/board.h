#ifndef BOARD_H
#define BOARD_H
#include <stdbool.h>




enum PlayerColor
{
    noColor,
    white,
    black

};

enum character
{
    noChar,
    King = 'K',
    Queen = 'Q',
    Knight = 'N',
    Bishop = 'B',
    Rook = 'R',
    Pawn = 'P'
};

typedef struct
{
    enum character pieceType;
    enum PlayerColor color;
    unsigned char rank;
    unsigned char file;
    unsigned char prevRank;
    unsigned char prevFile;
    bool enPassant;
    bool castle;
    int takeable[16]; /*can determine which piece is attacking the concerning piece*/
    unsigned char id;
    unsigned int hasMoved;
    bool inCheck;

}Piece;

enum gameType 
{
    None,
    PVP,
    PVC,
    CVC
};

/* for initially setting pieces */
void initializeBoard(Piece *board[MAX_FILE][MAX_RANK]);

/* Displaying the board in the terminal*/
void displayBoard(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor currentPlayer);

/* Flipping orientation of board for Human vs Human play*/
void flipBoard(Piece *board[MAX_FILE][MAX_RANK]);

void  deletePiece(Piece *e);
#endif