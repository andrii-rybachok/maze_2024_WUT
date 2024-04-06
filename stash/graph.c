#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node *createNodeForList(int v,int countOfSteps, int direction, int type)
{
     node *newNode = malloc(sizeof(node));


    // newNode->vertexNumber = v;

    newNode->nextVertex = NULL;
    return newNode;
}

void addEdgeToGraph(Graph *graph, int source, int destination, int countOfSteps,int direction)
{

    node *newNode = createNodeForList(destination,1,1,1);

    newNode->nextVertex = graph->adjacencyLists[source];

    graph->adjacencyLists[source] = newNode;


    newNode = createNodeForList(source,1,1,1);
    newNode->nextVertex = graph->adjacencyLists[destination];
    graph->adjacencyLists[destination] = newNode;
}


 Graph *initializeGraph(int vertices)
{
    int i;

     Graph *graph = malloc(sizeof( Graph));

    graph->numberOfVertices = vertices;


    graph->adjacencyLists = malloc(vertices * sizeof(node *));

    graph->visitedRecord = malloc(vertices * sizeof(int));

    for (i = 0; i < vertices; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visitedRecord[i] = 0;
    }

    return graph;
}

void depthFirstSearch( Graph *graph, int vertexNumber)
{
     node *adjList = graph->adjacencyLists[vertexNumber];
     node *temp = adjList;

    graph->visitedRecord[vertexNumber] = 1;
    printf("%d ", vertexNumber);

    while (temp != NULL)
    {
        int connectedVertex = temp->vertexNumber;

        if (graph->visitedRecord[connectedVertex] == 0)
        {
            depthFirstSearch(graph, connectedVertex);
        }
        temp = temp->nextVertex;
    }
}