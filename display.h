#ifndef DISPLAY_H
#define DISPLAY_H


#include "arena.h"
#include "graphics.h"
#include "randomgen.h"
#include "controller.h"
#include "robot.h"

void setTileSize(Arena *arena, int tileSize);
void drawWall(int x, int y);
void drawFloor(int x, int y);
void drawMarker(int x, int y);   
void drawHome(int x, int y);
int formatCoordinateForDisplay(int coordinate);
void setWindowSizeToArenaSize(Arena *arena);
void drawArena(Arena *arena);
void updateTileToFloor(Tile* Tile);
void drawTriangleFacingUp(int x, int y);
void drawTriangleFacingDown(int x, int y);
void drawTriangleFacingLeft(int x, int y);
void drawTriangleFacingRight(int x, int y);

void drawRobot(Robot *robot);

#endif 