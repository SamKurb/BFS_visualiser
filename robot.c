#include "robot.h"

void left(Robot *robot)
{
    switch (robot -> direction)
    {
        case UP:
            robot -> direction = LEFT;
            break;
        case RIGHT:
            robot -> direction = UP;
            break;
        case DOWN:
            robot -> direction = RIGHT;
            break;
        case LEFT:
            robot -> direction = DOWN;
            break;
    }
    drawRobot(robot);
    sleep(COOLDOWN);
}

void right(Robot *robot)
{
    switch (robot -> direction)
    {
        case UP:
            robot -> direction = RIGHT;
            break;
        case RIGHT:
            robot -> direction = DOWN;
            break;
        case DOWN:
            robot -> direction = LEFT;
            break;
        case LEFT:
            robot -> direction = UP;
            break;
    }
    drawRobot(robot);
    sleep(COOLDOWN);
}

void forward(Robot *robot)
{
    switch (robot -> direction)
    {
        case UP:
            robot -> y -= 1;
            break;
        case RIGHT:
            robot -> x += 1;
            break;
        case DOWN:
            robot -> y += 1;
            break;
        case LEFT:
            robot -> x -= 1;
            break;
    }
    drawRobot(robot);
    sleep(COOLDOWN);
}

int atMarker(Robot *robot, Arena *arena)
{
    int x = robot -> x;
    int y = robot -> y;
    Tile currentTile = arena -> tilemap[y][x];
    return (currentTile.type == MARKER); 
}

void pickUpMarker(Robot *robot, Arena *arena)
{
    robot -> markerCount++;
    arena -> tilemap[robot -> y][robot -> x].type = FLOOR; 
}

int markerCount(Robot *robot)
{
    return robot -> markerCount;
}

int isAtHome(Robot *robot, Arena *arena)
{
    Tile currentTile = arena -> tilemap[robot -> y][robot -> x];
    return (currentTile.type == HOME); 
}

bool robotPickedUpAllMarkers(Arena *arena, Robot *robot)
{
    return (robot -> markerCount == arena -> markerAmount);
}

Robot initialiseRobot(void)
{
    Robot robot = {.direction = UP, .markerCount = 0, .x = 0, .y = 0};
    return robot;
}

