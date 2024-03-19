#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_START 'P'
#define MAZE_END 'K'
#define MAZE_WALL 'X'
#define MAZE_PATH ' '


int getCountOfVertices(char * fileName);

void printSolve(Graph filledGraph,char* destFileName);

void fillGraph(Graph graph, char* filename);