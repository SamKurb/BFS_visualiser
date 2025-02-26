#include "constants.h"

// Animation related constants
const int COOLDOWN = 100;  // Cooldown time between robot actions
const int INITIAL_DELAY = 500;

// Display related constants
const int MAX_TILE_SIZE = 15;
const int MID_TILE_SIZE = 10;
const int MIN_TILE_SIZE = 5;

const int MAX_WINDOW_WIDTH = 2500;
const int MAX_WINDOW_HEIGHT = 1500;

// Random arena generation related constants
const int MIN_ROWS = 20;
const int MIN_COLS = 20;

const int MAX_COLS = 40;
const int MAX_ROWS = 40;

const int MARKER_AMOUNT = 5;

// Random obstacle generation within arena related constants
const int NUM_RAND_WALLS = 50;
const int NUM_RAND_RECTS = 5;
const int NUM_RAND_WALL_ROWS = 10;
const int NUM_RAND_WALL_COLS = 10;

const int MAX_RAND_ROW_WIDTH = 10;
const int MAX_RAND_COL_HEIGHT = 10;

const int MIN_RAND_RECT_WIDTH = 2;
const int MIN_RAND_RECT_HEIGHT = 2;

const int MAX_RAND_RECT_WIDTH = 8;
const int MAX_RAND_RECT_HEIGHT = 8;

const char *ARENA_FILE = "arenafile.txt";