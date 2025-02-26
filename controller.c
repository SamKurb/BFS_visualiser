#include "controller.h"
#include "robot.h"

void turnToDirection(Robot *robot, int targetDirection)
{
    int rightTurnsRequired = ((targetDirection - robot->direction) + 4) % 4;
    int leftTurnsRequired = ((robot->direction - targetDirection) + 4) % 4;

    if (rightTurnsRequired <= leftTurnsRequired) 
    {
        for (int i = 0; i < rightTurnsRequired; i++) 
        {
            right(robot);
        }
    } else {
        for (int i = 0; i < leftTurnsRequired; i++) 
        {
            left(robot);
        }
    }
}

int getDirectionToTile(Tile *currentTile, Tile *targetTile)
{
    int dx = targetTile -> x - currentTile -> x;
    int dy = targetTile -> y - currentTile -> y;

    if (dx == 1) return RIGHT;

    if (dx == -1) return LEFT;

    if (dy == 1) return DOWN;

    if (dy == -1) return UP;

    printf("Error in processing tile in function getDirectionToTile");
    exit(1);
}

void followPathToTile(Arena *arena, Robot *robot, Queue *moveBuffer)
{
    while (!isEmpty(moveBuffer))
    {
        Tile *currentTile = &arena -> tilemap[robot -> y][robot -> x];
        Tile *nextTile = deQueue(moveBuffer) -> tile;
        
        int targetDirection = getDirectionToTile(currentTile, nextTile);
        turnToDirection(robot, targetDirection);
        forward(robot);
    }

    if (atMarker(robot, arena))
    {
        pickUpMarker(robot, arena);
        Tile *currentTile = &arena -> tilemap[robot -> y][robot -> x];
        updateTileToFloor(currentTile);
    }
}

void goToAllMarkersOnMap(Arena *arena, Robot *robot)
{
    Queue *pathToMarker;

    while (!robotPickedUpAllMarkers(arena, robot))  
    {
        Tile *currentTile = &arena -> tilemap[robot -> y][robot -> x];
        pathToMarker = breadthFirstSearchForTile(arena, currentTile, MARKER);
        followPathToTile(arena, robot, pathToMarker);
        freeQueueMemory(pathToMarker);
        resetVisitedTiles(arena);
    }  
}

void goToHomeTile(Arena *arena, Robot *robot)
{
    Tile *currentTile = &arena -> tilemap[robot -> y][robot -> x];
    Queue* pathToHome = breadthFirstSearchForTile(arena, currentTile, HOME);
    followPathToTile(arena, robot, pathToHome);
    freeQueueMemory(pathToHome);
    resetVisitedTiles(arena);
}

void goToAllMarkersAndBack(Arena *arena, Robot *robot)
{
    goToAllMarkersOnMap(arena, robot);
    goToHomeTile(arena, robot);
}