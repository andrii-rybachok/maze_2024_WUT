#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int count_lines(char* fileName)
{
     FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1; // Return -1 to indicate error
    }

    int count = 1;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }

    fclose(file);
    return count;
}

int copyFile(const char *sourceFile, const char *destinationFile) {
    FILE *source, *destination;
    char buffer[MAZE_SIZE_X];
    size_t bytesRead;

    // Open the source file for reading
    source = fopen(sourceFile, "rb");
    if (source == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file for writing
    destination = fopen(destinationFile, "wb");
    if (destination == NULL) {
        perror("Error opening destination file");
        fclose(source);
        return 1;
    }

    // Copy file contents
    while ((bytesRead = fread(buffer, 1, MAZE_SIZE_X, source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }

    // Close files
    fclose(source);
    fclose(destination);

    return 0;
}

int main()
{
    getCountOfVertices("dane/maze.txt");
    // printf("#1 %d",n);
//     int numberOfVertices, numberOfEdges, i;
//     int source, destination;
//     int startingVertex;

//     printf("Enter Number of Vertices and Edges in the Graph: ");

    //  Graph *graph = initializeGraph(n);
    // printf("size %d",sizeof(node));
    char maze[MAZE_SIZE_Y][MAZE_SIZE_X];

    char ourFile[]="dane/maze_updated.txt";
    char iterationFile[]="dane/tmp.txt";
    char mainFile[]="dane/maze.txt";

    char * firstLine = malloc(sizeof(char)* MAZE_SIZE_X);
    char * lastLine = malloc(sizeof(char)* MAZE_SIZE_X);

    int fileCountRows=count_lines(mainFile);

    int lastRowPosition=readMazeFromFile(maze, mainFile,1,firstLine,lastLine);
    removeDeadEnds(maze,firstLine,lastLine);
    writeMazeToFile(maze, ourFile, 1,fileCountRows);

    while ( lastRowPosition<fileCountRows)
    {
        int lrpTemp=lastRowPosition;
        lastRowPosition=readMazeFromFile(maze, mainFile,lastRowPosition,firstLine,lastLine);
        removeDeadEnds(maze,firstLine,lastLine);
        writeMazeToFile(maze,ourFile, lrpTemp,fileCountRows);
    }


    int lastIteration=0;
    copyFile(ourFile,iterationFile);
    while (getCountOfDeadEnds(ourFile)){
        lastRowPosition=readMazeFromFile(maze, iterationFile,1,firstLine,lastLine);
        removeDeadEnds(maze,firstLine,lastLine);
        writeMazeToFile(maze, ourFile, 1,fileCountRows);

        while ( lastRowPosition<fileCountRows)
        {
            int lrpTemp=lastRowPosition;
            lastRowPosition=readMazeFromFile(maze, iterationFile,lastRowPosition,firstLine,lastLine);
            removeDeadEnds(maze,firstLine,lastLine);
            writeMazeToFile(maze,ourFile, lrpTemp,fileCountRows);
        }
        copyFile(ourFile,iterationFile);
    }
        getCountOfVertices(ourFile);
    

    
    
    free(firstLine);
    free(lastLine);
    
    // while (maze[rows][0] != '\0')
    //     rows++;

    // removeDeadEnds(maze, rows, MAZE_SIZE_Y);

    // writeMazeToFile(maze, "dane/maze_updated.txt", rows);
    // addEdgeToGraph(graph, 0, 1,1,1);
    // addEdgeToGraph(graph, 0, 2,1,1);

    // addEdgeToGraph(graph, 0, 3,1,1);

//     printf("Add %d Edges of the Graph(Vertex numbering should be from 0 to %d)\n", numberOfEdges, numberOfVertices - 1);
//    //  for (i = 0; i < numberOfEdges; i++)
//    //  {
//    //      scanf("%d%d", &source, &destination);
//    //      addEdgeToGraph(graph, source, destination);
//    //  }
// addEdgeToGraph(graph, 0, 1);
// addEdgeToGraph(graph, 1, 2);
// addEdgeToGraph(graph, 0, 2);
// addEdgeToGraph(graph, 2, 3);
// addEdgeToGraph(graph, 4, 3);
// addEdgeToGraph(graph, 5, 3);
// addEdgeToGraph(graph, 5, 4);

//     printf("Enter Starting Vertex for DFS Traversal: ");


//     if (2 < 6)
//     {
//         printf("DFS Traversal: ");
//         depthFirstSearch(graph, 2);
//     }
     return 0;
}