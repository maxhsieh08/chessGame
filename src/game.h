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

bool movePiece(Piece *board[8][8], enum PlayerColor pColor, enum PlayerColor p1Color, unsigned int startFile, unsigned int startRank, unsigned int endFile, unsigned int endRank);
bool isValidMove(Piece *board[8][8], enum PlayerColor pColor, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
bool validPawnMove(Piece *board[8][8], enum PlayerColor pColor, enum PlayerColor p1Color, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);