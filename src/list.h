

#include "mazeParams.h"
#include "binaryAdapter.h"

#define TMP_NAME "dane/test.txt"

#pragma pack(push, 1)
typedef struct  node{
    unsigned short countOfSteps: 14; // liczba kroków
    unsigned short direction : 2; // 0 - lewo, 1 - prawo, 2 - dół, 3 - góra 
    struct node* next;
} node;
#pragma pack(pop)



void clearCache(node ** head);
void show(node *head);
void push_back(node **head, int steps,int direction); // dodanie do końca listy
void pop_back(node **head,int count); // usuwanie z końca listy
int getSolutionSteps(); // suma wszystkich kroków
void saveSolution(mazeParams params); // zapisywanie rozwiązania binarnego lub tekstowego