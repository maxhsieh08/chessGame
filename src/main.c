#include "Constants.h"
#include "ai.h"
#include "game.h"
#include "board.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));
    Piece *board[MAX_FILE][MAX_RANK];
    Moves *AImoveLog[218];
    Moves *input = createNewMove();
    Moves *bestMove;
    enum PlayerColor p1Color = noChar;
    enum PlayerColor p2Color = noChar;
    enum gameType gameMode = None;
    printf("Welcome to Chess Game\n");
    printf("choose game mode:\n");
    printf("1 for: Player v Player\n2 for: Player v Computer\n3 for: Computer v Computer\n");
    while(gameMode<PVP || gameMode > CVC)
    {
        
        printf("pick your choice: ");
        gameMode = getchar()-48;
        if(gameMode==PVP)
        {
            printf("You chose PVP!\n");
            p1Color = white;
            p2Color = black;
        }
        else if(gameMode==PVC)
        {
            printf("You chose PVC!\n");
            printf("1 for white\n2 for black\n");
            
            printf("pick player 1 Color: ");
            while(p1Color>black||p1Color<white)
            {
                p1Color = getchar()-48;
                if(p1Color == white)
                {
                    printf("You chose White!\n");
                }
                else if (p1Color == black)
                {
                    printf("You chose Black!\n");
                }
                else if(p1Color == noColor)
                {
                    p1Color = getchar()-48;
                }
            }
        }
        else if(gameMode==CVC)
        {
            printf("You chose CVC!\n");
        }
        else
        {
            printf("error please select a game mode!\n");
        }
    }
    p2Color = p1Color==white?black:white;

    initializeBoard(board);
    for (int i = 0; i < 100; i++) {
        do {
        displayBoard(board, p1Color);
        printf("white's move\n");
        if(gameMode==PVP || (gameMode==PVC && p1Color==white))
        {
            printf("Enter start position (e.g., a2): ");
            scanf(" %c%u", &input->startFile, &input->startRank);  // Read file as char and rank as unsigned int


            printf("Enter end position (e.g., b3): ");
            scanf(" %c%u", &input->endFile, &input->endRank);
        }
        else
        {
            int totalLegalMoves = generateLegalMoves(board,white,AImoveLog);
            printf("total legal moves: %d\n", totalLegalMoves);
            bestMove = findBestMove(AImoveLog,totalLegalMoves);
            input->startFile = bestMove->startFile;
            input->startRank = bestMove->startRank;
            input->endRank = bestMove->endRank;
            input->endFile = bestMove->endFile;
            
        }
            convertCoordinates(input);      // Read file as char and rank as unsigned int
            printf("best move is %c%d%c%d value: %d",input->startFile,input->startRank,input->endFile,input->endRank,input->moveValue);
        }
        
        while (!isValidMove(board, p1Color, input));
        movePiece(board, input,0);
        do {
        displayBoard(board, p1Color);
        //testing
        printf("black's move\n");
        if(gameMode==PVP || (gameMode==PVC && p1Color==black))
        {
            printf("Enter start position (e.g., a2): ");
            scanf(" %c%u", &input->startFile, &input->startRank);  // Read file as char and rank as unsigned int


            printf("Enter end position (e.g., b3): ");
            scanf(" %c%u", &input->endFile, &input->endRank);
        }
        else
        {
            int totalLegalMoves = generateLegalMoves(board,black,AImoveLog);
            printf("total legal moves: %d\n", totalLegalMoves);
            bestMove = findBestMove(AImoveLog,totalLegalMoves);
            input->startFile = bestMove->startFile;
            input->startRank = bestMove->startRank;
            input->endRank = bestMove->endRank;
            input->endFile = bestMove->endFile;
            
        }
            convertCoordinates(input);      // Read file as char and rank as unsigned int
        // Display the read values for verification
        }
        while (!isValidMove(board, p2Color, input));
        displayBoard(board, p1Color);
        movePiece(board, input,0);
    }
    return 0;
}