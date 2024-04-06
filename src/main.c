#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "maze.h"
#include "help.h"
#include "operacja.h"

int main(int argc, char** argv) {
    if (argc == 2 && (strcmp(argv[1], "-h") == 0)) {
        displayHelp();
        return 0; 
    }

    char *inputFileName = argv[2];
    char outputFileName[strlen(inputFileName) + strlen("_updated.txt") + 1];
    strcpy(outputFileName, inputFileName);
    strcat(outputFileName, "_updated.txt");

    char solutionFileName[strlen(inputFileName) + strlen("_solution.txt") + 1];
    strcpy(solutionFileName, inputFileName);
    strcat(solutionFileName, "_solution.txt");

    char binaryFileName[strlen(inputFileName) + strlen(".bit") + 1];
    strcpy(binaryFileName, inputFileName);
    strcat(binaryFileName, ".bit");

    unsigned int maze[(MAZE_SIZE_X) * (MAZE_SIZE_Y) / 32 + 1];
    for (int i = 0; i < (MAZE_SIZE_X) * (MAZE_SIZE_Y) / 32 + 1; i++) {
        maze[i] = 0;   
    }

    mazeParams params = initializeParams(inputFileName, outputFileName);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            if (readMazeFromFile(maze, params) == -1) {
                printf("Error: unable to open, use -h %s.\n", inputFileName);
                return -1;
            }
            readMazeFromFile(maze, params);
        } else if (strcmp(argv[i], "-w") == 0) {
            removeDeadEnds(maze, params);
            writeMazeToFile(maze, params);
        } else if (strcmp(argv[i], "-s") == 0) {
            removeDeadEnds(maze, params);
            writeMazeToFile(maze, params);
            findSolution(maze, &params);
        } 
        else if (strcmp(argv[i], "-rb") == 0) {
            readMazeFromBinary(binaryFileName, maze, &params);
        } else if (strcmp(argv[i], "-wb") == 0) {
            removeDeadEnds(maze, params);
           writeMazeToBinary(binaryFileName, maze, params);
        } else if (strcmp(argv[i], "-sb") == 0) {
            removeDeadEnds(maze, params);
            writeMazeToBinary(binaryFileName, maze, params);
            findSolution(maze, &params);
        }
    }

    return 0;
}
