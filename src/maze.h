#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_START 'P'
#define MAZE_END 'K'
#define MAZE_WALL 'X'
#define MAZE_PATH ' '

#define MAZE_SIZE_X 1030
#define MAZE_SIZE_Y 1030


int getCountOfVertices(char * fileName);

void printSolve(Graph filledGraph,char* destFileName);

void fillGraph(Graph graph, char* filename);

int isDeadEnd(char maze[][MAZE_SIZE_Y], int x, int y);

void writeMazeToFile(char maze[][MAZE_SIZE_Y], char *filename, int rows);

void readMazeFromFile(char maze[][MAZE_SIZE_Y], char *filename);

void removeDeadEnds(char maze[][MAZE_SIZE_Y], int rows, int cols);
