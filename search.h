#ifndef QUEUE_H
#define QUEUE_H

#include "arena.h"  
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct QueueNode QueueNode;

typedef struct QueueNode
{
    Tile *tile;
    QueueNode *nextNode;
} QueueNode;

// Queue structure, used for BFS (Breadth-First Search)
typedef struct Queue
{
    QueueNode *tail;
    QueueNode *head;
    int size;
} Queue;

// Function declarations
QueueNode* createQueueNode(Tile *tile);
Queue* createQueue();
bool isEmpty(Queue* queue);
void enQueue(Queue* queue, Tile *newTile);
QueueNode* deQueue(Queue* queue);
void reverseQueue(Queue *queue);
void freeQueueMemory(Queue* queue);
void enQueueIfNotWall(Queue *queue, Tile *tile, Tile *parentTile);
void searchAdjacentTiles(Arena *arena, Queue *queue, Tile *currentTile);
Queue* breadthFirstSearchForTile(Arena *arena, Tile *startingTile, int targetTileType);
bool isEveryMarkerAccessible(Arena *arena, Tile *startingTile);
void resetVisitedTiles(Arena *arena);
Queue* tracePathFromTargetToStart(Tile *targetTile, Tile *startingTile);

#endif 