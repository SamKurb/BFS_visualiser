#include "filegen.h"

const int maxBufferLength = 300;

static const char validChars[4] = {'#',' ', 'M', 'H'};
static const int validCharAmount = sizeof(validChars) / sizeof(validChars[0]);

// On windows, text file lines are terminated by '\r\n' instead of just '\n'
void removeCarriageReturn(char *string)
{
    int length = strlen(string);
    if (length > 0 && string[length - 1] == '\n') 
    {
        string[length - 1] = '\0';  
    }
    if (length > 1 && string[length - 2] == '\r') 
    {
        string[length - 2] = '\0';  
    }
}

bool isValidCharacter(char character)
{
    for (int i = 0 ; i < validCharAmount ; i++)
    {
        if (character == validChars[i]) return true;
    }
    return false;
}

void checkForInvalidCharacters(FILE *file)
{

    char fileTextBuffer[maxBufferLength];

    if (file == NULL) 
    {
        printf("File could not be opened, make sure the file is in the correct directory");
        exit(1);
    }

     while (fgets(fileTextBuffer, sizeof(fileTextBuffer), file) != NULL)
    {
        removeCarriageReturn(fileTextBuffer);

        for (int i = 0; fileTextBuffer[i] != '\0'; i++) 
        {
            if (fileTextBuffer[i] == '\n') continue;
            
            if (!isValidCharacter(fileTextBuffer[i]))
            {
                printf("Arena text input contains invalid characters, make sure only valid characters are put into the input file\n");
                printf("Invalid character detected: '%c' with ASCII code: %d\n", fileTextBuffer[i], fileTextBuffer[i]);
                fclose(file); 
                exit(1);
            }
        }
    }
    rewind(file);
}

int getArenaWidthFromFile(FILE *file)
{
    char fileTextBuffer[maxBufferLength];

    while (fgets(fileTextBuffer, maxBufferLength, file) != NULL)
    {
        removeCarriageReturn(fileTextBuffer);

        // Skip empty/invalid lines
        if (fileTextBuffer[0] != '#')
        {
            continue;
        }
    }

    int width = strlen(fileTextBuffer); 

    rewind(file);
    return width; 
}

int getArenaHeightFromFile(FILE *file)
{
    int rowCount = 0;
    char fileTextBuffer[maxBufferLength];
    
    while (fgets(fileTextBuffer, maxBufferLength, file) != NULL)
    {
        removeCarriageReturn(fileTextBuffer);
        if (strlen(fileTextBuffer) > 0) 
        {
            rowCount++;
        }
    }
    rewind(file);
    return rowCount;
}

void setArenaDimensionsUsingFile(Arena *arena, FILE *file)
{
    arena -> height = getArenaHeightFromFile(file);
    arena -> width = getArenaWidthFromFile(file);
}

int convertCharToTileType(char character)
{
    if (character == '#') {
        return WALL;
    } else if (character == ' ') {
        return FLOOR;
    } else if (character == 'M') {
        return MARKER;
    } else if (character == 'H') {
        return HOME;
    } else {
        printf("Invalid character inputted to convertCharToTileType");
        exit(1);
    }
}

bool isArenaBorderedByWalls(Arena *arena) 
{
    int width = arena->width;
    int height = arena->height;

    for (int col = 0; col < width; col++) {
        Tile topRowTile = arena -> tilemap[0][col];
        Tile bottomRowTile = arena -> tilemap[height - 1][col];
        if (topRowTile.type != WALL || bottomRowTile.type != WALL)
        {
            return false;
        }
    }

    for (int row = 0; row < height; row++) {
        Tile leftColTile = arena -> tilemap[row][0];
        Tile rightColTile = arena -> tilemap[row][width - 1];
        if (leftColTile.type != WALL || rightColTile.type != WALL)
        {
            return false;
        }
    }
    return true;
}

Arena initialiseArenaFromFile(FILE *file)
{
    Arena arena;
    setArenaDimensionsUsingFile(&arena, file);

    if (arena.height <= 0 || arena.width <= 0) {
    printf("Invalid arena dimensions - Height: %d, Width: %d\n", arena.height, arena.width);
    exit(1);
    }

    arena.tilemap = (Tile**) malloc(sizeof(Tile*) * arena.height) ;
    if (arena.tilemap == NULL)
    {
        printf("Tilemap allocation failed in function initialiseArenaFromFile");
        exit(1);
    }
    for (int row = 0 ; row < arena.height ; row++ )
    {
        arena.tilemap[row] = (Tile*) malloc(sizeof(Tile) * arena.width); 

        if (arena.tilemap[row] == NULL)
        {
            printf("Row allocation failed in function initialiseArenaFromFile");
            exit(1);
        }
        for (int col = 0; col < arena.width; col++) 
        {
            arena.tilemap[row][col].y = row;
            arena.tilemap[row][col].x = col;
            arena.tilemap[row][col].parentTile = NULL;
        }
    }
    return arena;
}

void processFileInfoIntoArena(Arena *arena, FILE *file)
{
    char fileTextBuffer[maxBufferLength];

    int y = 0;
    int markerCount = 0;
    char currentChar;

    while (fgets(fileTextBuffer, maxBufferLength, file) != NULL)
    {
        removeCarriageReturn(fileTextBuffer);
        int lineLength = strlen(fileTextBuffer);
        if (lineLength > 0) 
        {
            for (int x = 0 ; x < lineLength ; x++) 
            {
                currentChar = fileTextBuffer[x];
                if (currentChar == '\0') break;
                if (currentChar == 'M') markerCount++;
                arena -> tilemap[y][x].type = convertCharToTileType(currentChar);
            }
            y++;
        }
    }
    arena -> markerAmount = markerCount;
}

Arena buildArenaFromFile(FILE *file)
{
    Arena arena = initialiseArenaFromFile(file);
    processFileInfoIntoArena(&arena, file);
    if (!isArenaBorderedByWalls(&arena))
    {
        printf("Arena is not bordered by walls, please ensure all outer walls and columns only contain walls");
        freeArenaFromMemory(&arena);
        exit(1);
    };
    return arena;
}

void setRobotPositionToHome(Arena *arena, Robot *robot)
{
    for (int y = 0 ; y < arena -> height ; y++)
    {
        for (int x = 0 ; x < arena -> width ; x++)
        {
            Tile currentTile = arena -> tilemap[y][x];
            if (currentTile.type == HOME)
            {
                robot -> y = y;
                robot -> x = x;

                if (!isEveryMarkerAccessible(arena, &currentTile))
                {
                    printf("Not all markers are accessible from home, reposition markers such that they are accessible");
                    exit(1);
                }
                resetVisitedTiles(arena);
                return;
            }
        }
    }
    printf("Input arena has no home tile, please add a 'H' tile into a valid space in the arena");
    exit(1);
}

