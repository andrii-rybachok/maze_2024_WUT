#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// usunięcie wybranej iłości linji z końca pliku tymczasowego
void removeLastLines(const char *filename, int count) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        handleError(8);
    }
    fseek(file, 0, SEEK_END);
    long int filePos = ftell(file);
    int lines = 0;
    int chars = 0;
    while (filePos--) {
        fseek(file, filePos, SEEK_SET);
        char c = fgetc(file);
        if(chars==0 && c == '\n'){
            count++;
        }
        chars++;
        if (c == '\n') {
            lines++;
            if (lines == count) {
                break;
            }
        }
    }
    fseek(file, filePos, SEEK_SET);
    ftruncate(fileno(file), ftell(file));
    fclose(file);
}
// bierze pierwszą literkę kierunku
char getDirectionLetter(const char *input) {
    char firstLetter = '\0'; 
    char *space = strchr(input, ' ');
    firstLetter = *(space + 1);

    return firstLetter;
}
// zwraca iłość kroków w stepie
int getDirectionSteps(const char *line) {
    int number = 0;
    int scanned = sscanf(line, "%*s %*s %d", &number);
    if (scanned != 1) {
        fprintf(stderr, "Rozwiązanie ma nieprawidłowy format.\n");
        exit(1);
    }
    return number;
}
int copyFile(const char *sourcePath, const char *destinationPath) {
    FILE *sourceFile, *destinationFile;
    char ch;
    sourceFile = fopen(sourcePath, "r");
    if (sourceFile == NULL) {
        handleError(8);
    }
    destinationFile = fopen(destinationPath, "w");
    if (destinationFile == NULL) {
        handleError(5);
    }
    //usunięcie pierwszej pustej linijki
    char buff[100];
    fgets(buff,100,sourceFile);


    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);
    return 0;
}

// dodaje jeden element do listy, jeżeli lista ma >1000 elementów, to oczyszczamy listę i zapisujemy do pliku tmp
void push_back(node **head, int steps,int direction)
{
    int a=getCountOfItems(*head);
    if(a>1000){
        clearCache(head);
    }

        if(*head==NULL)
        {
            *head = (node *)malloc(sizeof(node));
            (*head)->countOfSteps = steps;
            (*head)->direction = direction;
            (*head)->next = NULL;
        }
        else
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
// wyczyszczanie listy
void clearCache(node ** head){
    saveToTmp(*head);
    freeLinkedList(head);
}
//usunięcie linji z pliku
void pop_back(node **head,int count)
{
    if(getCountOfItems(*head)>0){
        saveToTmp(*head);
        freeLinkedList(head);
    }
    removeLastLines(TMP_NAME,count);
}
// zapisywanie listy do pliku tymczasowego
void saveToTmp(node ** head){
    FILE *file = fopen(TMP_NAME, "a");
    
    if (file == NULL) {
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
                        sprintf(str,"\nGO LEFT %d ",current->countOfSteps);
                        break;
                    case 1:
                        sprintf(str,"\nGO RIGHT %d",current->countOfSteps);
                        break;
                    case 2:
                        sprintf(str,"\nGO BOT %d ",current->countOfSteps);
                        break;
                    case 3:
                        sprintf(str,"\nGO TOP %d ",current->countOfSteps);
                        break;
                    default:
                        break;
                    }
                    fprintf(file, "%s", str);

                current = current->next;
        }while (current != NULL);
    } 
    fclose(file);
}
void freeLinkedList(node** head) {

    node * tmp=NULL;
 
    while (*head!=NULL) {
        tmp=(*head)->next;
        free(*head);
        *head=tmp;
    }
}
int getCountOfItems(node * head){
    int count=0;
    if(head!=NULL){
        node *current=head;
        do {
            count++;
            current = current->next;
        }while (current != NULL);
    }
    return count;
}
//obliczanie iłości kroków w pliku tmp
int getSolutionSteps()
{
    FILE *file = fopen(TMP_NAME, "r");
    if (file == NULL) {
        handleError(8);
    }

    char line[100]; 
    int sum = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char *ptr = line;
        int num;
        while (sscanf(ptr, "%*s %*s %d", &num) == 1) {
            sum += num;
            while (*ptr && *ptr != '\n')
                ptr++;
            if (*ptr == '\n') 
                break;
        }
    }

    fclose(file);
    return sum;
}
//zapisywanie rozwiązania do pliku rozwiązania
void saveSolution(mazeParams params){
    FILE * fp;
    // robimy switch po typu rozwiązania
    switch (params.solutionType)
    {
    // w przypadku t , zapisujemy rozwiązanie jako plik tekstowy
    case 't': 
        //kopiowanie pliku tymczasowego do rozwiązania
        copyFile(TMP_NAME,params.solutionFileName);
        break;
    // w przypadku b , zapisujemy rozwiązanie jako plik binarny
    case 'b': ;
        fp = fopen(params.solutionFileName,"wb");
        if (fp == NULL) {
           handleError(5);
        }
        FILE * fr=fopen(TMP_NAME,"r");
        binHeader header = getFileHeader(params.originFileName); // pobieramy z pomocą zewnętrznej funkcji nagłówek pliku binarnego
        int countOfSteps = params.minSteps; // bierzemy iłość kroków   
        //zapisywanie nagłówku
        fwrite(&(header.file_id),sizeof(header.file_id),1,fp); // przypisujemy znaczenie id z nagłówku 
        fwrite(&(countOfSteps),sizeof(countOfSteps),1,fp); 
        //pominięcie pierwszej pustej linijki
        char buff[100];
        fgets(buff,100,fr);
        while (fgets(buff,100,fr))
        {
            char direction = getDirectionLetter(buff);
            char currentSteps= getDirectionSteps(buff);
            fwrite(&(direction),sizeof(direction),1,fp); 
            fwrite(&currentSteps,sizeof(currentSteps),1,fp);          

        }
        fclose(fr);
        fclose(fp);
        break;
    default:
        break;
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