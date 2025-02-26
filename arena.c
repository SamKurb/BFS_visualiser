#include "arena.h"

void addBordersToArena(Arena *arena)
{

    for (int x = 0 ; x < arena -> width ; x++)
    {
        // Fill the top and bottom rows with walls
        arena -> tilemap[0][x].type = WALL; 
        arena -> tilemap[arena -> height-1][x].type = WALL;
    }

    for (int y = 0 ; y < arena -> height ; y++)
    {
        // Fill the leftmost and rightmost columns with walls
        arena -> tilemap[y][0].type = WALL; 
        arena -> tilemap[y][arena -> width-1].type = WALL;
    }
}

void randomiseArenaDimensions(Arena *arena);

Arena createArena(void)
{
    Arena arena;

    randomiseArenaDimensions(&arena);
    arena.markerAmount = MARKER_AMOUNT;

    arena.tilemap = (Tile**) malloc(sizeof(Tile*) * arena.height) ;
    if (arena.tilemap == NULL)
    {
        printf("Tilemap allocation failed in function createArena");
        exit(1);
    }

    for (int row = 0 ; row < arena.height ; row++ )
    {
        // all tiles are initialised with type = 0, which represent floors
        arena.tilemap[row] = (Tile*) calloc(arena.width, sizeof(Tile)); 

        if (arena.tilemap[row] == NULL)
        {
            printf("Row allocation failed in function createArena");
            exit(1);
        }

        for (int col = 0; col < arena.width; col++) 
        {
            arena.tilemap[row][col].y = row;
            arena.tilemap[row][col].x = col;
            arena.tilemap[row][col].parentTile = NULL;
        }
    }

    addBordersToArena(&arena);
    return arena;
}

void freeArenaFromMemory(Arena *arena) 
{
    for (int row = 0; row < arena->height; row++) 
    {
        free(arena->tilemap[row]);
    }

    free(arena->tilemap);
}


