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


void saveSolution(node *head,mazeParams params){
    FILE * fp;
    // robimy switch po typu rozwiązania
    switch (params.solutionType)
    {
    // w przypadku t , zapisujemy rozwiązanie jako plik tekstowy
    case 't': ;
        fp = fopen(params.solutionFileName,"w");
        if (fp == NULL) {
            printf("Error 1opening file.\n");
            return;
        }
        if(head!=NULL)
        {
            node *current=head;
                do {
                    char str[20];
                    // tworzenie stringu dla zapisania kroku
                    switch (current->direction)
                    {
                    case 0:
                        sprintf(str,"GO LEFT %d \n",current->countOfSteps);
                        break;
                    case 1:
                        sprintf(str,"GO RIGHT %d \n",current->countOfSteps);
                        break;
                    case 2:
                        sprintf(str,"GO BOT %d \n",current->countOfSteps);

                        break;
                    case 3:
                        sprintf(str,"GO TOP %d \n",current->countOfSteps);

                        break;
                    default:
                        break;
                    }
                    fputs(str,fp);
                current = current->next;
                }while (current != NULL);
    
        } 
        fclose(fp);
        break;
    // w przypadku t , zapisujemy rozwiązanie jako plik binarny
    case 'b': ;
        fp = fopen(params.solutionFileName,"wb");
        if (fp == NULL) {
            printf("Error opening binary final file.\n");
            return;
        }
        binHeader header = getFileHeader(params.originFileName); // pobieramy z pomocą zewnętrznej funkcji nagłówek pliku binarnego
        int countOfSteps = params.minSteps; // bierzemy iłość kroków   
        //zapisywanie nagłówku
        fwrite(&(header.file_id),sizeof(header.file_id),1,fp); // przypisujemy znaczenie id z nagłówku 
        fwrite(&(countOfSteps),sizeof(countOfSteps),1,fp); 
        // tworzenie charu na podstawie current direction
        if(head!=NULL)
        {
            node *current=head;
                do {
                    char direction;
                    switch (current->direction)
                    {
                    case 0:
                        direction = 'W';
                        break;
                    case 1:
                        direction = 'E';
                        break;
                    case 2:
                        direction = 'S';
                        break;
                    case 3:
                        direction = 'N';
                        break;
                    default:
                        break;
                    }
                // zapisywanie kroku
                fwrite(&(direction),sizeof(direction),1,fp); 
                char currentSteps= current->countOfSteps;
                fwrite(&currentSteps,sizeof(currentSteps),1,fp);          
                current = current->next;
                }while (current != NULL);   
        } 
        fclose(fp);
        break;
    default:
        break;
    }
   
}
