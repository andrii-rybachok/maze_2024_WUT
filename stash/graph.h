// 
typedef struct  node{

    
    unsigned int vertexNumber: 16;
    unsigned int countOfSteps : 5;
    unsigned int direction:2; // 0 - przód, 1 - tył, 2 - góra, 3 - dół 
    unsigned int type:2; // 0- zwykły node, 1 - pozątek, 2-koniec 
   struct node * nextVertex;
   
} node;

typedef struct Graph
{
    unsigned int numberOfVertices;
    int currenAllocated;
    int *visitedRecord;

} Graph;

node *createNodeForList(int v,int countOfSteps, int direction, int type);

void addEdgeToGraph(struct Graph *graph, int source, int destination, int countOfSteps,int direction);

Graph *initializeGraph(int vertices);

void depthFirstSearch( Graph *graph, int vertexNumber);

