
#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include "arena.h"
#include "robot.h"

typedef struct Robot Robot;
typedef struct Arena Arena;

int randomNumWithinRange(int lowerbound, int upperbound);

void randomiseArenaDimensions(Arena *arena);
void addRandomWalls(Arena *arena, int amount);
void addRandomRectangle(Arena *arena, int amount);
void addRandomColumnOfWalls(Arena *arena, int amount);
void addRandomRowOfWalls(Arena *arena, int amount);
void addMarkersInRandomPositions(Arena *arena);
void randomiseArena(Arena *arena);

Arena generateValidMap(Robot *robot);

void randomiseRobotStartPosition(Arena *arena, Robot *robot);
void randomiseRobotStartDirection(Robot *robot);

#endif