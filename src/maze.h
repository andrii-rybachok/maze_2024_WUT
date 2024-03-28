#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_START 'P'
#define MAZE_END 'K'
#define MAZE_WALL 'X'
#define MAZE_PATH ' '

#define MAZE_SIZE_X 2049
#define MAZE_SIZE_Y 500


int getCountOfVertices(char * fileName);
int getCountOfDeadEnds(char * fileName);

void printSolve(Graph filledGraph,char* destFileName);

void fillGraph(Graph graph, char* filename);

void isDeadEnd(char maze[][MAZE_SIZE_X], int x, int y);

void writeMazeToFile(char maze[][MAZE_SIZE_X], char *filename, int startRowIndex,int fileRowSize);

int readMazeFromFile(char maze[][MAZE_SIZE_X], char *filename,int startRowIndex,char* firstLine,char* lastLine);

void removeDeadEnds(char maze[][MAZE_SIZE_X],char* firstLine,char* lastLine);

