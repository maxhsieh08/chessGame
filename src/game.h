#ifndef GAME_H
#define GAME_H
#endif
#include "board.h"
void movePiece(Piece *board[8][8], enum PlayerColor pColor, unsigned int startFile, unsigned int startRank, unsigned int endFile, unsigned int endRank);
bool isValidMove(Piece *board[8][8], enum PlayerColor pColor, unsigned int startFileIndex, unsigned int startRankIndex, unsigned char endFileIndex, unsigned int endRankIndex);
