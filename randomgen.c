#include <stdlib.h>
#include "time.h"
#include "randomgen.h"

int randomNumWithinRange(int lowerbound, int upperbound)
{
    if (upperbound < lowerbound) 
    {
        printf("Invalid bounds inputted to function randomNumWithinRange\n");
        printf("Ensure that inputted lowerbound is LESS THAN upperbound");
        exit(1);
    }
    
    int randomNum = (rand() % (upperbound - lowerbound + 1)) + lowerbound; // Random number between lowerbound and upperbound (inclusive)
    return randomNum;
}

void randomiseArenaDimensions(Arena *arena)
{
    arena -> height = randomNumWithinRange(MIN_ROWS, MAX_ROWS);
    arena -> width = randomNumWithinRange(MIN_COLS, MAX_COLS);
}

void addRandomWalls(Arena *arena, int amount)
{
    int randomx;
    int randomy;

    for (int i = 0 ; i < amount ; i++)
    {
        // "1" and "-2" are to take into account the already placed walls bordering the arena
        randomx = randomNumWithinRange(1, arena -> width -2); 
        randomy = randomNumWithinRange(1, arena -> height -2);  

        arena -> tilemap[randomy][randomx].type = WALL;
    }
}

void addRandomRectangle(Arena *arena, int amount)
{
    int randomWidth;
    int randomHeight;
    
    int randomx;
    int randomy;

    for (int rectNum = 0 ; rectNum < amount ; rectNum++)
    {
        randomWidth = (randomNumWithinRange(MIN_RAND_RECT_WIDTH, MAX_RAND_RECT_WIDTH));
        randomHeight = (randomNumWithinRange(MIN_RAND_RECT_HEIGHT, MAX_RAND_RECT_HEIGHT));
        
        randomx = randomNumWithinRange(1, arena -> width - randomWidth -1);
        randomy = randomNumWithinRange(1, arena -> height - randomHeight -1);

        for (int y = randomy ; y < randomy + randomHeight ; y++)
        {
            for (int x = randomx ; x < randomx + randomWidth ; x++)
            {
                arena -> tilemap[y][x].type = WALL;
            }
        }
    }
}

void addRandomColumnOfWalls(Arena *arena, int amount)
{
    int randomHeight;
    
    int randomx;
    int randomy;

    for (int columnNum = 0 ; columnNum < amount ; columnNum++)
    {
        randomHeight = (randomNumWithinRange(1, MAX_RAND_COL_HEIGHT));
    
        randomx = randomNumWithinRange(1, arena -> width - 1);
        randomy = randomNumWithinRange(1, arena -> height - randomHeight -1);

        for (int y = randomy ; y < randomy + randomHeight ; y++)
        {
            arena -> tilemap[y][randomx].type = WALL;
        }
    }
}

void addRandomRowOfWalls(Arena *arena, int amount)
{
    int randomLength;

    int randomx;
    int randomy;

    for (int rowNum = 0 ; rowNum < amount ; rowNum++)
    {
        randomLength = (randomNumWithinRange(1, MAX_RAND_ROW_WIDTH));
        randomx = randomNumWithinRange(1, arena -> width - randomLength - 1);
        randomy = randomNumWithinRange(1, arena -> height-1);

        for (int x = randomx ; x < randomx + randomLength ; x++)
        {
            arena -> tilemap[randomy][x].type = WALL;
        }
    }
}

void addMarkersInRandomPositions(Arena *arena)
{
    int markerCount = 0;
    int targetAmount = arena -> markerAmount;
    int randomx;
    int randomy;
    int attempts = 0;
    int maxAttempts = 1000000;
    while (markerCount < targetAmount)
    {
        randomx = randomNumWithinRange(1, arena -> width -1);
        randomy = randomNumWithinRange(1, arena -> height -1);  

    // Markers should only ever replace floors
        if (arena -> tilemap[randomy][randomx].type == FLOOR)
        {
            arena -> tilemap[randomy][randomx].type = MARKER;
            markerCount++;
        }
        attempts++;
        if (attempts > maxAttempts) 
        {
            printf("Maximum marker placement attempts exceeded - not enough empty tiles available ");
            exit(1);
        }
    }
}

void randomiseArena(Arena *arena)
{
    addRandomWalls(arena, NUM_RAND_WALLS);
    addRandomRectangle(arena, NUM_RAND_RECTS);
    addRandomColumnOfWalls(arena, NUM_RAND_WALL_COLS);
    addRandomRowOfWalls(arena, NUM_RAND_WALL_ROWS);

    addMarkersInRandomPositions(arena);
}

// A valid map is one where all markers are accessible by the robot
Arena generateValidMap(Robot *robot)
{
    Arena arena = createArena();
    randomiseArena(&arena);
    randomiseRobotStartPosition(&arena, robot);
    randomiseRobotStartDirection(robot);

    while (!isEveryMarkerAccessible(&arena, &arena.tilemap[robot -> y][robot -> x]))
    {
        freeArenaFromMemory(&arena);
        arena = createArena();
        randomiseArena(&arena);
        randomiseRobotStartPosition(&arena, robot);
    }
    resetVisitedTiles(&arena); 
    return arena;
}

void randomiseRobotStartPosition(Arena *arena, Robot *robot)
{
    int maxRows = arena -> height; 
    int maxCols = arena -> width; 

    int x;
    int y;
    Tile spawnTile;

    do 
    {
        y = randomNumWithinRange(1, maxRows-2);
        x = randomNumWithinRange(1, maxCols-2);
        spawnTile = arena -> tilemap[y][x];
    } while (spawnTile.type != FLOOR);
    
    arena -> tilemap[y][x].type = HOME;
    robot -> x = x;
    robot -> y = y; 
}

void randomiseRobotStartDirection(Robot *robot)
{
    // There are only 4 directions possible, so range is 0 to 3 (these are not magic numbers)
    int direction = randomNumWithinRange(0, 3);
    robot -> direction = direction;
}

