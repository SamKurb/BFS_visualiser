#ifndef ROBOT_H
#define ROBOT_H

#include "arena.h"
#include "display.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Arena Arena;  

enum Directions {
    UP, // 0
    RIGHT, // 1
    DOWN, // 2
    LEFT // 3
};

typedef struct Robot {
    int direction;
    int markerCount;
    int x;
    int y;
} Robot;

void left(Robot *robot);
void right(Robot *robot);
void forward(Robot *robot);
void turnToDirection(Robot *robot, int targetDirection);

int atMarker(Robot *robot, Arena *arena);
void pickUpMarker(Robot *robot, Arena *arena);

int markerCount(Robot *robot);
int isAtHome(Robot *robot, Arena *arena);
bool robotPickedUpAllMarkers(Arena *arena, Robot *robot);
Robot initialiseRobot(void);


#endif