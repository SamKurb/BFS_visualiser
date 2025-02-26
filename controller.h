#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "search.h"
#include "display.h"
#include "constants.h"
#include <stdio.h>

typedef struct Robot Robot;

int getDirectionToTile(Tile *currentTile, Tile *targetTile);
void followPathToTile(Arena *arena, Robot* robot, Queue *moveBuffer);
void turnToDirection(Robot *robot, int targetDirection);
void goToAllMarkersOnMap(Arena *arena, Robot *robot);
void goToHomeTile(Arena *arena, Robot *robot);
void goToAllMarkersAndBack(Arena *arena, Robot *robot);

#endif
