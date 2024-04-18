#include <stdbool.h>

#ifndef BOARD_H
#define BOARD_H
#endif

enum PlayerColor
{
    noColor,
    black,
    white,

};

enum character
{
    noChar,
    King,
    Queen,
    Knight,
    Bishop,
    Rook,
    Pawn
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

}Piece;


/* for initially setting pieces */
void initializeBoard(Piece *board[8][8], enum PlayerColor p1Color);

/* Displaying the board in the terminal*/
void displayBoard(Piece *board[8][8]);

/* Flipping orientation of board for Human vs Human play*/
void flipBoard(Piece *board[8][8]);
