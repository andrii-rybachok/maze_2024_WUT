#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_START 'P'
#define MAZE_END 'K'
#define MAZE_WALL 'X'
#define MAZE_PATH ' '


#define MAZE_SIZE_X 2049
#define MAZE_SIZE_Y 2049




typedef struct mazeParams
{
    int cols;
    int rows;
    char* originFileName;
    char* ourFileName;
    cords endCords;
    cords startCords;
    int minSteps;
} mazeParams;


int getCountOfVertices(char * fileName);


void findSolution(unsigned int maze[],mazeParams* params);

mazeParams initializeParams(char* originFileName,char* ourFileName);

void writeMazeToFile(unsigned int maze[],mazeParams params);

int readMazeFromFile(unsigned int maze[], mazeParams params);

void removeDeadEnds(unsigned int maze[],mazeParams params);
