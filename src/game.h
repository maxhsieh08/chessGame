#ifndef GAME_H
#define GAME_H
#endif
#include "board.h"

enum gameType 
{
    None,
    PVP,
    PVC,
    CVC
};

bool movePiece(Piece *board[8][8], enum PlayerColor currentPlayer, enum PlayerColor playerOne, unsigned int startFile, unsigned int startRank, unsigned int endFile, unsigned int endRank);
bool isValidMove(Piece *board[8][8], enum PlayerColor currentPlayer, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validPawnMove(Piece *board[8][8], enum PlayerColor currentPlayer, enum PlayerColor playerOne, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validRookMove(Piece *board[8][8], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validBishopMove (Piece *board[8][8], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validQueenMove (Piece *board[8][8], unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validKnightMove (unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);