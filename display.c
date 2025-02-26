#include <stdlib.h>
#include <stdio.h>
#include "display.h"

int TILE_SIZE; 

void setTileSize(Arena *arena, int tileSize)
{
    int arenaHeight = arena -> height;
    int tileSizeNeeded = MAX_WINDOW_HEIGHT / arenaHeight;
    if (tileSizeNeeded >= MAX_TILE_SIZE) {
        TILE_SIZE = MAX_TILE_SIZE;
    } else if (tileSizeNeeded < MAX_TILE_SIZE && tileSizeNeeded >= MID_TILE_SIZE) {
        TILE_SIZE = MID_TILE_SIZE;
    } else {
        TILE_SIZE = MIN_TILE_SIZE;
    }
}

void drawWall(int x, int y)
{
    setColour(darkgray);
    x = formatCoordinateForDisplay(x);
    y = formatCoordinateForDisplay(y);
    fillRect(x, y, TILE_SIZE, TILE_SIZE);
}

void drawFloor(int x, int y)
{
    x = formatCoordinateForDisplay(x);
    y = formatCoordinateForDisplay(y);
    setColour(lightgray);
    fillRect(x, y, TILE_SIZE, TILE_SIZE);
    setColour(black);
    drawRect(x, y, TILE_SIZE, TILE_SIZE);
}

void drawMarker(int x, int y)
{
    x = formatCoordinateForDisplay(x);
    y = formatCoordinateForDisplay(y);
    setColour(red);
    fillRect(x, y, TILE_SIZE, TILE_SIZE);
}   

void drawHome(int x, int y)
{
    x = formatCoordinateForDisplay(x);
    y = formatCoordinateForDisplay(y);
    setColour(yellow);
    fillRect(x, y, TILE_SIZE, TILE_SIZE);
}

int formatCoordinateForDisplay(int coordinate)
{
    return coordinate * TILE_SIZE;
}

void setWindowSizeToArenaSize(Arena *arena)
{
    int width = formatCoordinateForDisplay(arena -> width);
    int height = formatCoordinateForDisplay(arena -> height);

    if (width > MAX_WINDOW_WIDTH || height > MAX_WINDOW_HEIGHT)
    {
        printf("Maximum window dimensions exceeded in function setWindowSizeToArenaSize\n");
        printf("Likely max rows/cols too high or tile size too large\n");
        exit(1);
    }

    setWindowSize(width, height);
}

void drawArena(Arena *arena)
{
    setTileSize(arena, TILE_SIZE);
    setWindowSizeToArenaSize(arena);
    background(); 

    for (int ycoord = 0 ; ycoord < arena -> height ; ycoord++)
    {
        for (int xcoord = 0 ; xcoord < arena -> width ; xcoord++)
        {
        Tile currentTile = arena -> tilemap[ycoord][xcoord];
        switch (currentTile.type)
        {
            case WALL: 
                drawWall(xcoord, ycoord);
                break;
            case FLOOR: 
                drawFloor(xcoord, ycoord);
                break;
            case MARKER: 
                drawMarker(xcoord, ycoord);
                break;
            case HOME: 
                drawHome(xcoord, ycoord);
                break;
        }
        }
    }
}

void updateTileToFloor(Tile* Tile)
{
    background();
    {
        drawFloor(Tile -> x, Tile -> y);
    }
}

void drawTriangleFacingUp(int x, int y)
{
    int xcoords[3] = {x + (TILE_SIZE / 2), x, x + TILE_SIZE}; 
    int ycoords[3] = {y, y + TILE_SIZE, y + TILE_SIZE};
    fillPolygon(3, xcoords, ycoords);
}

void drawTriangleFacingDown(int x, int y)
{
    int xcoords[3] = {x + (TILE_SIZE / 2), x, x + TILE_SIZE}; 
    int ycoords[3] = {y + TILE_SIZE , y, y};
    fillPolygon(3, xcoords, ycoords);
}

void drawTriangleFacingLeft(int x, int y)
{
    int xcoords[3] = {x, x + TILE_SIZE, x + TILE_SIZE}; 
    int ycoords[3] = {y + (TILE_SIZE/2), y, y + TILE_SIZE};
    fillPolygon(3, xcoords, ycoords);
}

void drawTriangleFacingRight(int x, int y)
{
    int xcoords[3] = {x + TILE_SIZE, x, x}; 
    int ycoords[3] = {y + (TILE_SIZE/2), y, y + TILE_SIZE};
    fillPolygon(3, xcoords, ycoords);
}

void drawRobot(Robot *robot)
{
    foreground();
    clear();
    setColour(green);

    int direction = robot -> direction;
    int x = robot -> x * TILE_SIZE;
    int y = robot -> y * TILE_SIZE;

    switch (direction)
    {
        case UP:
            drawTriangleFacingUp(x, y);
            break;
        case DOWN:
            drawTriangleFacingDown(x,y);
            break;
        case LEFT:
            drawTriangleFacingLeft(x,y);
            break;
        case RIGHT:
            drawTriangleFacingRight(x,y);
    }
}


       



