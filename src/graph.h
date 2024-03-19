// 
typedef struct  node{
    int test;
    
    // int vertexNumber: 20;
    // int countOfSteps : 5;
    // int direction:2; // 0 - przód, 1 - tył, 2 - góra, 3 - dół 
    // int type:2; // 0- zwykły node, 1 - pozątek, 2-koniec 
   struct node * nextVertex;
} node;

typedef struct Graph
{
    int numberOfVertices;
    int currenAllocated;
    int *visitedRecord;

    struct node **adjacencyLists;
} Graph;

node *createNodeForList(int v,int countOfSteps, int direction, int type);

void addEdgeToGraph(struct Graph *graph, int source, int destination, int countOfSteps,int direction);

Graph *initializeGraph(int vertices);

void depthFirstSearch( Graph *graph, int vertexNumber);

