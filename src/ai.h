#ifndef AI_H
#define AI_H
#include "game.h"


int generateLegalMoves(Piece *board[MAX_FILE][MAX_RANK],  enum PlayerColor aiColor, Moves *AImoveLog[218]);
void assignMoveLogValues(Moves *AImoveLog[200],unsigned int x, unsigned int y, unsigned int i, unsigned int j, unsigned int k, float moveValue);
float evaluateBoard(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor aiColor, int startFileIndex, int startRankIndex, int endFileIndex, int endRankIndex);
float takeableValue(Piece *endPiece, enum PlayerColor aiColor);
float positionValue(Piece *board[MAX_FILE][MAX_RANK],int startFileIndex, int startRankIndex, int endFileIndex, int endRankIndex, enum PlayerColor aiColor);
Moves *findBestMove(Moves *AImoveLog[218], int totalLegalMoves);

#endif