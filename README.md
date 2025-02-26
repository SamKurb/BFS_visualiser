# BFS_visualiser

# General Info 
This program displays a robot pathfinding through an arena (2D tilemap grid) to collect all the markers on the map and return back home, using drawapp-4.0.jar
The program supports two modes when creating the arena - random generation and text file input. The mode is chosen through command line inputs from the user.

# Description of how the program itself works 
The arena itself contains obstacles (walls) that the robot must path around to reach the markers.
The robot, using a breadth first search pathfinding algorithm, always finds the shortest path from tile to tile. This means that the path it takes from its home
to the markers and back will always be the most optimal.
Randomly generated arenas contain randomly placed obstacles, and are between 20-40 in width and height (w/h are both randomly selected)

The pathfinding works as follows:
First, use BFS to "mentally" locate a path to the closest target (i.e marker) tile, keeping track of which tiles lead to which (parent tiles of each tile). When the target tile is reached,
trace the path back to the starting tile (by following the parent tiles of each tile). This path will be in reverse, as it is going backwards from the target to the start, so it must be reversed. 
The traced path is held in queue, which acts as a move buffer for the robot, as it can deduce which direction to turn to and go forward based on a tile's location relative
to itself. As such, it can follow the path of tiles held in the buffer until it reaches the target tile.

# Information on the different files 
arena.c - contains definitions for the arena and tile structs, as well as functions responsible for initialising the base of the arena
constants - contains constants responsible for different aspects of the program
controller - contains functions used to move the robot from tile to tile, by translating information obtained from BFS
display - contains functions responsible for drawing and updating everything on the screen
filegen - contains functions responsible for generating an arena based on text file input (the designated text file is "arenafile.txt"
randomgen - contains functions responsible for the random generation of the arena and robot's initial state, mainly with respect to obstacles/walls inside
robot - contains definitions of the robot struct as well as functions related to the base actions it can do (i.e turnleft) as well as other functions
search.c - contains functions related to breadth-first search and pathfinding, as well as the queue implementation used for it

# Instructions on use 
To compile the program, at least on windows, run "gcc -o [exe name] *c"
i.e "gcc -o project *c"

To run the program, run "./[exe name] [argv] | java drawapp-4.0.jar"

The program takes 1 command line argument, which can be one of two things. "random" or "file".

Passing in "random" as an argument makes the program randomly generate a valid (all markers accessible) map for the robot to path through.
i.e "./project random | java -jar drawapp-4.0.jar"

Passing in "file" makes the program generate the map by copying what is inputted into "arenafile.txt".
i.e "./project file | java -jar drawapp-4.0.jar"

#NOTES: 
**IMPORTANT** Depending on your screen size, larger arenas may have some of their tiles partly offscreen, due to how drawapp blocks out the bottom part of the window with the output window. The current tile size constants are set to accommodate my 1920x1080 24 inch monitor, if you are running this on something smaller and notice that some tiles do not fully appear in the window, change the max, mid, min tilesize constants in the constants file. By default these are set to 20,10,5. After testing on my laptop, 10,10,5 works well. Make sure to save and recompile! This should not be an issue on normal-sized monitors.

When using file to manually input arenas, '#' represents a wall, 'M' represents a marker, 'H' represents home (robot start tile) and ' ' represents a floor (empty tile)
Ensure that the arena passed in through the file is bordered by walls on all sides, and that the inputted lengths for each row are equal.
Also ensure that all markers are accessible.

If you would like the robot to move faster, lower the "cooldown" constant in the constants file

Thank you for reading!
