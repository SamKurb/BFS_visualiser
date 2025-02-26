#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arena.h"
#include "robot.h"

void removeCarriageReturn(char *string);
bool isValidCharacter(char character);
void checkForInvalidCharacters(FILE *file);

int getArenaWidthFromFile(FILE *file);
int getArenaHeightFromFile(FILE *file);
void setArenaDimensionsUsingFile(Arena *arena, FILE *file);

int convertCharToTileType(char character);
Arena initialiseArenaFromFile(FILE *file);
bool isArenaBorderedByWalls(Arena *arena);
void processFileInfoIntoArena(Arena *arena, FILE *file);
Arena buildArenaFromFile(FILE *file);
void setRobotPositionToHome(Arena *arena, Robot *robot);

#endif 