#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <string.h>
#include <limits.h>
#include "maze.h"



int main()
{

    unsigned int maze[(MAZE_SIZE_X)*(MAZE_SIZE_Y)/32+1];
    for (int i = 0; i <(MAZE_SIZE_X)*(MAZE_SIZE_Y)/32+1; i++)
    {
        maze[i]=0;   
    }
    
   
    char ourFile[]="dane/maze_updated.txt";
    char mainFile[]="dane/maze.txt";

   

    mazeParams params=initializeParams(mainFile,ourFile);

    readMazeFromFile(maze, params);
     
    removeDeadEnds(maze,params);
    writeMazeToFile(maze,params);
    findSolution(maze,&params);

    //  for (int i = 0; i < 1; i++)
    //  {
    //     push_back(&head,10,1);
    //  }
     
    // int numberOfVertices, numberOfEdges, i;
    // int source, destination;
    // int startingVertex;

  
    // SetBit( visitedNodes, 0);
    // printf("is true %d", TestBit(visitedNodes,0));

    return 0;
}