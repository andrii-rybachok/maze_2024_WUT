#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "maze.h"
#include "help.h"
#include <time.h> 


int main(int argc, char *argv[])
{
    unsigned int maze[(MAZE_SIZE_X)*(MAZE_SIZE_Y)/32+1];
    for (int i = 0; i <(MAZE_SIZE_X)*(MAZE_SIZE_Y)/32+1; i++)
    {
        maze[i]=0;   
    }
    
   
    char ourFile[]="dane/maze_updated.txt";
    char mainFile[]="dane/maze.bin";

    convertBinaryToText(mainFile, ourFile);

    return 0;
}
