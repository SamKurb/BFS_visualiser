#include <string.h>
#include "controller.h"
#include "display.h"
#include "randomgen.h"
#include "robot.h"
#include "search.h"
#include "arena.h"
#include "filegen.h"
#include "constants.h"

void processAndDisplayArena(Arena *arena, Robot * robot)
{
    drawArena(arena);
    drawRobot(robot);
    sleep(INITIAL_DELAY); 
    goToAllMarkersAndBack(arena, robot);
    freeArenaFromMemory(arena);
}

int main(int argc, char *argv[1])
{
    srand(time(NULL));
    Robot robot = initialiseRobot();
    Arena arena;

    if (strcmp(argv[1], "random") == 0)
    {
        arena = generateValidMap(&robot);
    } 
    else if (strcmp(argv[1], "file") == 0) 
    {
        FILE *file = fopen(ARENA_FILE, "r");
        arena = buildArenaFromFile(file);
        setRobotPositionToHome(&arena, &robot);
    }

    processAndDisplayArena(&arena, &robot);
    return 0;
}