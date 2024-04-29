#include "Constants.h"
#include "ai.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//testing for ai
// edit here
int generateLegalMoves(Piece *board[MAX_FILE][MAX_RANK],  enum PlayerColor aiColor, Moves *AImoveLog[218])
{ //[a1a2]
    //k is the index in AImoveLog
    unsigned int k=0;
        int piecesLookedAt=0;
        for(unsigned int y=0;y<MAX_RANK;y++)
        {
            for(unsigned int x=0;x<MAX_FILE;x++)
            {
                if(board[y][x]==NULL)
                    {
                        #ifdef DEBUG
                            printf("trying to acces NULL pointer\n");
                        #endif
                        continue;
                    }
                //if color is the same as the ai color
                if(board[y][x]->color==aiColor)
                {
                    unsigned int j; // for checking diags for queen and bishop
                    Piece *temp = board[y][x];
                    bool isMoveValid = false;
                    float moveVal = 0;
                    switch (temp->pieceType) 
                    {
                        case Pawn:
                            printf("looking at Pawn moves!\n");
                            for(unsigned int j=y+1;j<((y+3<7)?(y+3):7);j++)
                                {
                                    unsigned int i = x;
                                    
                                        if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                        {
                                        // #ifdef DEBUG
                                        printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                        // #endif
                                            isMoveValid = validPawnMove(board, x, y, i, j); // check if move is allowed by the rules
                                            if(isMoveValid)
                                            {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                            }
                                        }
                                    
                                }
                            for(unsigned int j=y-1;j>(((int)y-3>0)?(y-3):0);j--)
                                {
                                    unsigned int i = x;
                                        
                                        if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                        {
                                        // #ifdef DEBUG
                                        printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                        // #endif
                                            isMoveValid = validPawnMove(board, x, y, i, j); // check if move is allowed by the rules
                                            if(isMoveValid)
                                            {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                            }
                                        }
                                    
                                }
                                piecesLookedAt++;
                            break;
                        case Rook:
                            printf("looking at Rook moves!\n");
                            // check vertically
                            for(unsigned int i=0;i<MAX_FILE;i++)
                                {
                                    unsigned int j = y;
                                    if((int)i!=(int)x) // skips the space that the piece is on
                                    {
                                        // #ifdef DEBUG
                                        printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                        // #endif
                                        if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                        {
                                            isMoveValid = validRookMove(board, x, y, i, j); // check if move is allowed by the rules
                                            if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                        }
                                    }
                                }
                            // check horizontally
                            for(unsigned int j=0;j<MAX_RANK;j++)
                                {
                                    unsigned int i = x;
                                    if((int)j!=(int)y) // skips the space that the piece is on
                                    {
                                        // #ifdef DEBUG
                                        printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                        // #endif
                                        if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                        {
                                            isMoveValid = validRookMove(board, x, y, i, j); // check if move is allowed by the rules
                                            if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                        }
                                    }
                                }
                                piecesLookedAt++;
                            break;
                        case Bishop:                      
                            printf("looking at Bishop moves!\n");
                            // check diag 1 (space to bottom right)
                                j = y;
                                for(int i=x;i<8;i++)
                                {
                                        if((int)j>7)break; // breaks out of loop when space is out of index (doesn't check out of bound indexes)
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                isMoveValid = validBishopMove(board, x, y, i, j); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                            }
                                        }                                      
                                        j++;
                                } 
                                // check diag 2 (space to top right)
                                j = y;
                            for(int i = x;i<8;i++)
                                {
                                        if((int)j<0)break; // breaks out of loop when space is out of index (doesn't check out of bound indexes)
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                isMoveValid = validBishopMove(board, x, y, i, j); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                            }
                                        }
                                        j--;
                                }
                                // check diag 3 (space to bottom left)
                                j =y;
                            for(int i=x;i>=0;i--)
                                {
                                        if((int)j>7)break; // breaks out of loop when space is out of index (doesn't check out of bound indexes)
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                isMoveValid = validBishopMove(board, x, y, i, j); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                            }
                                        }
                                        j++;
                                }
                            // check diag 4 (space to top left)
                            j=y;
                            for(int i=x;i>=0;i--)
                                {
                                    if((int)j<0)break; // breaks out of loop when space is out of index (doesn't check out of bound indexes)
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                isMoveValid = validBishopMove(board, x, y, i, j); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                            }
                                        }
                                        j--;
                                }          
                                piecesLookedAt++;             
                            break;
                        case Queen:
                            printf("looking at Queen moves!\n");
                            // check vertically
                            for(unsigned int i=0;i<MAX_FILE;i++)
                                {
                                    unsigned int j = y;
                                    if((int)i!=(int)x) // skips the space that the piece is on
                                    {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                        if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                        {
                                            isMoveValid = validQueenMove(board, x, y, i, j); // check if move is allowed by the rules
                                            if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                        }
                                    }
                                }
                            // check horizontally
                            for(unsigned int j=0;j<MAX_RANK;j++)
                                {
                                    unsigned int i = x;
                                    if((int)j!=(int)y) // skips the space that the piece is on
                                    {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                        if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                        {
                                            isMoveValid = validQueenMove(board, x, y, i, j); // check if move is allowed by the rules
                                            if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                        }
                                    }
                                }
                                // check diag 1 (space to bottom right)
                                j = y;
                                for(int i=x;i<8;i++)
                                {
                                        if((int)j>7)break; // breaks out of loop when space is out of index (doesn't check out of bound indexes)
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                isMoveValid = validQueenMove(board, x, y, i, j); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                            }
                                        }                                      
                                        j++;
                                } 
                                // check diag 2 (space to top right)
                                j = y;
                            for(int i = x;i<8;i++)
                                {
                                        if((int)j<0)break; // breaks out of loop when space is out of index (doesn't check out of bound indexes)
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                isMoveValid = validQueenMove(board, x, y, i, j); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                            }
                                        }
                                        j--;
                                }
                                // check diag 3 (space to bottom left)
                                j =y;
                            for(int i=x;i>=0;i--)
                                {
                                        if((int)j>7)break; // breaks out of loop when space is out of index (doesn't check out of bound indexes)
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                isMoveValid = validQueenMove(board, x, y, i, j); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                            }
                                        }
                                        j++;
                                }
                            // check diag 4 (space to top left)
                            j=y;
                            for(int i=x;i>=0;i--)
                                {
                                    if((int)j<0)break; // breaks out of loop when space is out of index (doesn't check out of bound indexes)
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                isMoveValid = validQueenMove(board, x, y, i, j); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                            }
                                        }
                                        j--;
                                }
                                piecesLookedAt++;
                            break;
                        case King:
                            printf("looking at King moves!\n");
                            for(int i=((int)x-1>0)?(int)x-1:0;i<(int)x+2;i++)
                                {
                                    for(int j=((int)y-1>0)?(int)y-1:0;j<(int)y+2;j++)
                                    {
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                
                                                isMoveValid = validKingMove(board, x, y, i, j, 0); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }                    
                                            }
                                        }
                                    }
                                }       
                                piecesLookedAt++;                 
                            break;
                        case Knight:
                            printf("looking at Knight moves!\n");
                            for(int i=((int)x-2>0)?(x-2):0;i<(int)x+3;i++)
                                {
                                    for(int j=((int)y-2>0)?(y-2):0;j<(int)y+3;j++)
                                    {
                                        if(i<0||i>7||j<0||j>7)continue; // skips spaces that are out of index
                                        if((int)i!=(int)x&&(int)j!=(int)y) // skips the space that the piece is on
                                        {
                                            // #ifdef DEBUG
                                            printf("testing: %c%d%c%d\n",x+97,8-y,i+97,8-j);
                                            // #endif
                                            if(checkSpace(board,aiColor,x,y,i,j)) // check if space is open
                                            {
                                                isMoveValid = validKnightMove(x, y, i, j); // check if move is allowed by the rules
                                                if(isMoveValid)
                                                {
                                                    moveVal = evaluateBoard(board,aiColor,x,y,i,j);
                                                    assignMoveLogValues(AImoveLog,x,y,i,j,k, moveVal); // append to AImoveLog
                                                    k++; // increment AImoveLog index
                                                }
                                            }
                                        }
                                    }
                                }             
                                piecesLookedAt++;
                            break;
                        case noChar:
                            printf("there is no piece here\n");
                            break;
                        default:
                            printf("there is no piece here\n");
                            return k;
                    }
                }
            }
        }
        return k;
    }   

//just for making code more clean
void assignMoveLogValues(Moves *AImoveLog[218],unsigned int x, unsigned int y, unsigned int i, unsigned int j, unsigned int k, float valueM)
{
    AImoveLog[k] = createNewMove();
    AImoveLog[k]->startRank = (8-y);
    AImoveLog[k]->endRank = (8-j);
    AImoveLog[k]->startFile = (x+97);
    AImoveLog[k]->endFile = (i+97);
    AImoveLog[k]->moveValue = valueM;
    printf("this is a move at %d: %c%d%c%d  %d\n",k, AImoveLog[k]->startFile,AImoveLog[k]->startRank,AImoveLog[k]->endFile,AImoveLog[k]->endRank, AImoveLog[k]->moveValue);
}

float evaluateBoard(Piece *board[MAX_FILE][MAX_RANK], enum PlayerColor aiColor, int startFileIndex, int startRankIndex, int endFileIndex, int endRankIndex)
{
    float valueOfThisMove = 0;
    Piece *endPiece = board[endRankIndex][endFileIndex];
    valueOfThisMove+= takeableValue(endPiece, aiColor);
    valueOfThisMove+= positionValue(board,startFileIndex,startRankIndex,endFileIndex,endRankIndex,aiColor);
    
    
    return valueOfThisMove;
}

float takeableValue(Piece *endPiece, enum PlayerColor aiColor)
{
    float value=0;
    if(endPiece==NULL)
    {
        return 0;
    }
    else if(endPiece!=NULL && endPiece->color != aiColor)
    {
        switch (endPiece->pieceType)
        {
        case Pawn:
                value+=1;
                printf("+PawnVaLTake 1\n");
            break;
        case Knight:
                value+=3;
                printf("+VaLTake 3\n");
            break;
        case Rook:
                value+=5;
                printf("+RookVaLTake 5\n");
            break;
        case Bishop:
                value+=3;
                printf("+BishopVaLTake 3\n");
            break;
        case Queen:
                value+=9;
                printf("+QueenVaLTake 9\n");
            break;
        case King:
                value+=100;
                printf("+KingVaLTake 100\n");
            break;
        case noChar:
                // this does nothing
            break;
        default:
                // this does nothing
            break;
        }
    }
    return value;
}



float blackPawnPosVal[] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10,-20,-20, 10, 10,  5,
    5, -5,-10,  0,  0,-10, -5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5,  5, 10, 25, 25, 10,  5,  5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
    0,  0,  0,  0,  0,  0,  0,  0
    };
float blackRookPosVal[] = {
    0,  0,  5,  10, 10, 5,  0,  0,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     5,  10, 10, 10, 10, 10, 10, 5,
     0,  0,  0,  0,  0,  0,  0,  0
    };
float blackBishopPosVal[] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
    };
float blackKnightPosVal[] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
    };
float blackQueenPosVal[] = {
    -20,-10,-10, -5, -5,-10,-10,-20
    -10,  0,  5,  0,  0,  0,  0,-10,
    -10,  5,  5,  5,  5,  5,  0,-10,
     0,  0,  5,  5,  5,  5,  0, -5,
    -5,  0,  5,  5,  5,  5,  0, -5,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
    };
float blackKingPosVal[] = {
    20,  30,  10,  0,   0,   10,  30,  20,
     20,  20,  0,   0,   0,   0,   20,  20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    };

float whitePawnPosVal[64];
float whiteRookPosVal[64];
float whiteKnightPosVal[64];
float whiteBishopPosVal[64];
float whiteQueenPosVal[64];
float whiteKingPosVal[64];
// moves the piece and checks who is in a winning position (more valuable pieces)
// FIX THIS
float positionValue(Piece *board[MAX_FILE][MAX_RANK],int startFileIndex, int startRankIndex, int endFileIndex, int endRankIndex, enum PlayerColor aiColor)
{
    // initialize white position values
    for(int i =0;i<64;i++)
    {
        whitePawnPosVal[i]=blackPawnPosVal[63-i];
        whiteRookPosVal[i]=blackRookPosVal[63-i];
        whiteKnightPosVal[i]=blackKnightPosVal[63-i];
        whiteBishopPosVal[i]=blackBishopPosVal[63-i];
        whiteQueenPosVal[i]=blackQueenPosVal[63-i];
        whiteKingPosVal[i]=blackKingPosVal[63-i];

    }
    Moves *temp = createNewMove();
    temp->startFile = startFileIndex;
    temp->startRank = startRankIndex;
    temp->endFile = endFileIndex;
    temp->endRank = endRankIndex;
    float value = 0;
    movePiece(board,temp,1);
    displayBoard(board,aiColor);
    for(int y = 0;y<(int)MAX_RANK;y++)
    {
        for(int x = 0;x<(int)MAX_FILE;x++)
        {
            if(board[y][x] == NULL)
            {
                continue;
            }
            else
            {
                Piece *temp = board[y][x];
                if(temp->color == aiColor)
                {
                    switch (temp->pieceType)
                    {
                        case Pawn:
                                value+=1;
                                if(temp->color == black)
                                {
                                    value+=0.01*blackPawnPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value+=0.01*whitePawnPosVal[x+y*8-1];
                                }
                                printf("value is %f at: %c%d%c%d\n",value,startFileIndex,startRankIndex,endFileIndex,endRankIndex);
                            break;
                        case Knight:
                                value+=3;
                                if(temp->color == black)
                                {
                                    value+=0.01*blackKnightPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value+=0.01*whiteKnightPosVal[x+y*8-1];
                                }
                            break;
                        case Rook:
                                value+=5;
                                if(temp->color == black)
                                {
                                    value+=0.01*blackRookPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value+=0.01*whiteRookPosVal[x+y*8-1];
                                }
                            break;
                        case Bishop:
                                value+=3;
                                if(temp->color == black)
                                {
                                    value+=0.01*blackBishopPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value+=0.01*whiteBishopPosVal[x+y*8-1];
                                }
                            break;
                        case Queen:
                                value+=9;
                                if(temp->color == black)
                                {
                                    value+=0.01*blackQueenPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value+=0.01*whiteQueenPosVal[x+y*8-1];
                                }
                            break;
                        case King:
                                if(temp->color == black)
                                {
                                    value+=0.01*blackKingPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value+=0.01*whiteKingPosVal[x+y*8-1];
                                }
                            break;
                        case noChar:
                                // this does nothing
                            break;
                        default:
                                // this does nothing
                            break;
                        
                    }
                }
                else if(temp->color != aiColor)
                {
                    switch (temp->pieceType)
                    {
                        case Pawn:
                                value-=1;
                                if(temp->color == black)
                                {
                                    value-=0.01*blackPawnPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value-=0.01*whitePawnPosVal[x+y*8-1];
                                }
                            break;
                        case Knight:
                                value-=3;
                                if(temp->color == black)
                                {
                                    value-=0.01*blackKnightPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value-=0.01*whiteKnightPosVal[x+y*8-1];
                                }
                            break;
                        case Rook:
                                value-=5;
                                if(temp->color == black)
                                {
                                    value-=0.01*blackRookPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value-=0.01*whiteRookPosVal[x+y*8-1];
                                }
                            break;
                        case Bishop:
                                value-=3;
                                if(temp->color == black)
                                {
                                    value-=0.01*blackBishopPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value-=0.01*whiteBishopPosVal[x+y*8-1];
                                }
                            break;
                        case Queen:
                                value-=9;
                                if(temp->color == black)
                                {
                                    value-=0.01*blackQueenPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value-=0.01*whiteQueenPosVal[x+y*8-1];
                                }
                            break;
                        case King:
                                if(temp->color == black)
                                {
                                    value-=0.01*blackKingPosVal[x+y*8-1];
                                }
                                else
                                {
                                    value-=0.01*whiteKingPosVal[x+y*8-1];
                                }
                            break;
                        case noChar:
                                // this does nothing
                            break;
                        default:
                                // this does nothing
                            break;
                        
                    }
                }
            }

        }
    }
    temp->startFile =endFileIndex;
    temp->startRank =endRankIndex;
    temp->endFile = startFileIndex;
    temp->endRank = startRankIndex;
    Piece *undoMove = temp->endPtr;
    movePiece(board,temp,1);
    board[endRankIndex][endFileIndex] = undoMove;
    displayBoard(board,aiColor);
    return value;
}
// go through every legal move and iterate until the end, placing the highest valued move into bestMove
Moves *findBestMove(Moves *AImoveLog[218], int totalLegalMoves)
{
    Moves *bestMove = AImoveLog[0];
    for(int i=0;i<totalLegalMoves;i++)
    {
        if(bestMove->moveValue < AImoveLog[i]->moveValue)
        {
            bestMove = AImoveLog[i];
        }
    }
    return bestMove;
}