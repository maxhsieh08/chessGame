#ifndef MOVELOG_H
#define MOVELOG_H
#include "game.h"
#include "board.h"

typedef struct {
    Node *prevNode;
    Node *nextNode;
    Moves *move;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} moveList;


#endif