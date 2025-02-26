#include "search.h"

// Using a linked list to implement a queue as it is easy to reverse (useful later)
Queue* createQueue()
{
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue -> tail = NULL;
    queue -> head = NULL;
    queue -> size = 0;

    return queue;
}

QueueNode* createQueueNode(Tile *tile)
{
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode -> tile = tile;
    newNode -> nextNode = NULL;

    return newNode;
}

bool isEmpty(Queue *queue)
{
    return (queue -> size == 0);
}

void enQueue(Queue* queue, Tile *newTile)
{
    QueueNode *newNode = createQueueNode(newTile);

    if (isEmpty(queue))
    {
        queue -> head = newNode;
        queue -> tail = newNode;
    } else {
        queue -> tail -> nextNode = newNode;
        queue -> tail = newNode;
    }

    queue -> size++;
}

QueueNode* deQueue(Queue* queue)
{
    if (isEmpty(queue)) 
    {
        return NULL;
    }

    QueueNode* dequeuedNode = queue -> head;
    queue -> head = queue -> head -> nextNode;

    queue -> size--;

    // If the queue is empty after dequeuing, tail needs to be re-initialised to NULL (head will already be NULL)
    if (isEmpty(queue))
    {
        queue -> tail = NULL;
    }

    return dequeuedNode;
}

void reverseQueue(Queue *queue)
{
    if (isEmpty(queue) || queue->size == 1)
    {
        return;
    }

    QueueNode *previousNode = NULL;      
    QueueNode *currentNode = queue -> head; 
    QueueNode *nextNode = NULL;         

    // Traverse the queue and reverse the direction of each node's next pointer. nextNode acts as a temp variable
    while (currentNode != NULL)
    {
        nextNode = currentNode -> nextNode; 
        currentNode -> nextNode = previousNode; 

        previousNode = currentNode;
        currentNode = nextNode;
    }

    queue -> tail = queue -> head;  
    queue -> head = previousNode; 

    queue -> tail -> nextNode = NULL;
}

void freeQueueMemory(Queue* queue)
{
    while (!isEmpty(queue))
    {
        free(deQueue(queue)); 
    }
    
    free(queue);
}

void enQueueIfNotWall(Queue *queue, Tile *tile, Tile *parentTile)
{
    if (tile -> type != WALL && tile -> visited == false)
    {
        tile -> visited = true;
        tile -> parentTile = parentTile;
        enQueue(queue, tile);
    }
}

void searchAdjacentTiles(Arena *arena, Queue *queue, Tile *currentTile)
{
    int x = currentTile -> x;
    int y = currentTile -> y;

    Tile *tileAbove = &arena -> tilemap[y-1][x];
    enQueueIfNotWall(queue, tileAbove, currentTile);

    Tile *tileBelow = &arena -> tilemap[y+1][x];
    enQueueIfNotWall(queue, tileBelow, currentTile);

    Tile *tileRight = &arena -> tilemap[y][x+1];
    enQueueIfNotWall(queue, tileRight, currentTile);

    Tile *tileLeft = &arena -> tilemap[y][x-1];
    enQueueIfNotWall(queue, tileLeft, currentTile);

}

Queue* breadthFirstSearchForTile(Arena *arena, Tile *startingTile, int targetTileType)
{
    Queue *queue = createQueue(); 

    startingTile -> visited = true;
    enQueue(queue, startingTile);

    while (!isEmpty(queue))
    {
        Tile *currentTile = deQueue(queue) -> tile;

        if (currentTile -> type == targetTileType) 
        {
            Tile *targetTile = currentTile;
            return tracePathFromTargetToStart(targetTile, startingTile);
        }
        searchAdjacentTiles(arena, queue, currentTile);
    } 
    return NULL;
}

// Flood fill BFS search to check if every marker can be reached from a given starting point
bool isEveryMarkerAccessible(Arena *arena, Tile *startingTile)
{
    int markersReached = 0;
    int totalMarkersOnMap = arena -> markerAmount;

    Queue *queue = createQueue(); 

    startingTile -> visited = true;
    enQueue(queue, startingTile);

    while (!isEmpty(queue))
    {
        Tile *currentTile = deQueue(queue) -> tile;
        if (currentTile -> type == MARKER) 
        {
            markersReached++;
            if (markersReached == totalMarkersOnMap) 
            {
            freeQueueMemory(queue);
            return true;
            }
        }
        searchAdjacentTiles(arena, queue, currentTile);
    } 

    freeQueueMemory(queue);
    return false;
}

void resetVisitedTiles(Arena *arena)
{
    for (int row = 0; row < arena -> height; row++)
    {
        for (int col = 0; col < arena -> width; col++)
        {
            arena->tilemap[row][col].visited = false;
            arena->tilemap[row][col].parentTile = NULL;
        }
    }
}

// Traces the path BFS used to get to the target tile via backtracking through the parent pointers
Queue* tracePathFromTargetToStart(Tile *targetTile, Tile *startingTile)
{
    Queue *pathQueue = createQueue();
    if (pathQueue == NULL) {
        return NULL;  
    }

    Tile *currentTile = targetTile;

    while (currentTile != startingTile)
    {
        enQueue(pathQueue, currentTile);
        currentTile = currentTile -> parentTile;
    }

    // Since the path is traced backwards (from end to start), it needs
    // to be reversed so that a path from start to end is returned rather than end to start
    reverseQueue(pathQueue);

    return pathQueue;
}
