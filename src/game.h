#ifndef GAME_H
#define GAME_H
#include "board.h"

//testing for ai
typedef struct 
{
    unsigned int startRank;
    unsigned char startFile;
    unsigned int endRank;
    unsigned char endFile;
    unsigned char moveValue;
    Piece *endPtr;
}Moves;


// end testing for ai

bool isValidMove(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor currentPlayer, Moves *input);
void movePiece (Piece *board[MAX_FILE][MAX_RANK], Moves *input, bool checking);
bool checkSpace(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor currentPlayer, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validPawnMove(Piece *board[MAX_FILE][MAX_RANK], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validRookMove(Piece *board[MAX_FILE][MAX_RANK], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validBishopMove (Piece *board[MAX_FILE][MAX_RANK], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validQueenMove (Piece *board[MAX_FILE][MAX_RANK], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validKnightMove (unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validKingMove(Piece *board[MAX_FILE][MAX_RANK], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex, bool canCastle);
bool isSafe(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor currentPlayer, unsigned int fileIndex, unsigned int rankIndex);
void convertCoordinates (Moves *input);
Moves *createNewMove();
// bool isCheck(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor playerOne, unsigned int fileIndex, unsigned int rankIndex);
#endif