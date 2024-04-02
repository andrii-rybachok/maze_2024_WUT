
typedef struct  node{
    unsigned short countOfSteps: 14;
    unsigned short direction : 2;
    struct node* next;
} node;
typedef struct cords
{
    int x;
    int y;
} cords;
typedef struct listParams
{
    int* visitedVertices;
    cords * currentCords;
    int lastVerticeNumber;
} listParams;

void show(node *head);
void push_back(node **head, int steps,int direction);
void pop_back(node **head);
int getListSteps(node *head);
void printSolution(char* fileName, node *head);