#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "time.h"
#include "constants.h"

enum TileTypes
{
    FLOOR,  // '#'
    WALL,   // ' '
    MARKER, // 'M'
    HOME    // 'H'
};

typedef struct Tile Tile;

typedef struct Tile
{
    int x;
    int y;
    int type;

    // Variables to be used later for breadth-first search
    int visited;
    Tile *parentTile;
} Tile;

typedef struct Arena
{
    Tile **tilemap;
    int height;
    int width;
    int markerAmount; 
} Arena;

void randomiseArenaDimensions(Arena *arena);
void addBordersToArena(Arena *arena);
Arena createArena(void);
void freeArenaFromMemory(Arena *arena);

#endif
