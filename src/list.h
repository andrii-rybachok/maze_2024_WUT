#pragma pack(push, 1)
typedef struct  node{
    unsigned short countOfSteps: 14;
    unsigned short direction : 2;
    struct node* next;
} node;
#pragma pack(pop)
typedef struct cords
{
    int x;
    int y;
} cords;


void show(node *head);
void push_back(node **head, int steps,int direction);
void pop_back(node **head);
int getListSteps(node *head);
void printSolution(char* fileName, node *head);