#include <stdio.h>
#include <stdlib.h>
#include "maze.h"



int main()
{
    int n=getCountOfVertices("dane/maze.txt");
    
//     int numberOfVertices, numberOfEdges, i;
//     int source, destination;
//     int startingVertex;

//     printf("Enter Number of Vertices and Edges in the Graph: ");

    //  Graph *graph = initializeGraph(n);
    // printf("size %d",sizeof(node));
    char maze[MAZE_SIZE_Y][MAZE_SIZE_X];
    int rows = 0;
    readMazeFromFile(maze, "dane/maze.txt");

    while (maze[rows][0] != '\0')
        rows++;

    removeDeadEnds(maze, rows, MAZE_SIZE_Y);

    writeMazeToFile(maze, "dane/maze_updated.txt", rows);
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