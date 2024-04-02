#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void push_back(node **head, int steps,int direction)
{
    if(*head==NULL)
    {
    *head = (node *)malloc(sizeof(node));
    (*head)->countOfSteps = steps;
    (*head)->direction = direction;

        (*head)->next = NULL;
    }else
    {
        node *current=*head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = (node *)malloc(sizeof(node));
        current->next->countOfSteps = steps;
        current->next->direction = direction;
        current->next->next = NULL;
    }
}


void pop_back(node **head)
{
    
    if((*head)->next==NULL)
    {
    *head=NULL;
    }else
    {
    node *current=*head;
    while (current->next->next!= NULL) {
            current = current->next;
        }
    free(current->next);
    current->next=NULL;
    }  
}


void show(node *head)
{
    printf("\n");
    if(head==NULL) printf("List is empty");
    else
    {
        node *current=head;
            do {
            switch (current->direction)
            {
            case 0:
                printf("GO LEFT");
                break;
            case 1:
                printf("GO RIGHT");
                break;
            case 2:
                printf("GO BOT");
                break;
            case 3:
                printf("GO TOP");
                break;
            default:
                break;
            }
            printf(", steps %d",current->countOfSteps);
            printf("\n");
            current = current->next;
            }while (current != NULL);
 
    }
    printf("\n");

}

int getListSteps(node *head)
{
    int stepsInList=0;
    if(head!=NULL){
        node *current=head;
            do {
            stepsInList+=current->countOfSteps;
            current = current->next;
            }while (current != NULL);
 
    }
    return stepsInList;
}