
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <string.h>
#include <limits.h>
#include "maze.h"
#include "binaryAdapter.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    int opt;
    unsigned int maze[(MAZE_SIZE_X)*(MAZE_SIZE_Y)/32+1]; // iniccjalizacja tablicy bitowej, która zawiera nasz labirynt
    char * mainFileName, *solutionFileName; // nazwa pliku wejściowego oraz wyjściowego (razem z rozszerzeniem)

    char solutionType='n'; // typ rozwiązania, n - nijaki, b- binarny, t- tekstowy
    for (int i = 0; i <(MAZE_SIZE_X)*(MAZE_SIZE_Y)/32+1; i++)
    {
        maze[i]=0;   // resetowanie wszystkich bitów
    }
    
    while ((opt = getopt(argc, argv, "f:s:h")) != -1)  
    {  
        switch (opt)  
        {  
            case 's': //nazwa pliku rozwiązania
                solutionFileName= malloc(sizeof(char)*strlen(optarg));
                strcpy( solutionFileName,optarg); 
                break;  
            case 'f': //nazwa pliku labiryntu
                mainFileName= malloc(sizeof(char)*strlen(optarg));
                strcpy( mainFileName,optarg); 
            break;
            case 'h': // wywołanie help
                printHelp();
                exit(EXIT_SUCCESS);
            case ':':  
                handleError(1); 
                break;  
        }  
    } 
    char * mainFileExtension = strrchr(mainFileName, '.'); 
    char * solutionFileExtension = strrchr(solutionFileName, '.');

    if(mainFileExtension==NULL){
        handleError(2);
    }
     if(solutionFileExtension==NULL){
        handleError(5);
    } // sprawdzania rozszerzeń plików 
    mainFileExtension+=1;
    solutionFileExtension+=1;
    mazeParams params;
    
    if (strcmp(mainFileExtension, "txt") == 0) 
    {
        params=initializeParams(mainFileName); // inicjalizacja parametrów labiryntu dla .txt
        readMazeFromFile(maze, params); // wywołanie funkcji, jaka czyta plik .txt i zapisuje do tablicy 
    } else if (strcmp(mainFileExtension, "bin") == 0) {
        params=initializeParamsBin(mainFileName); // inicjalizacja parametrów labiryntu dla .bin
        readMazeFromBinFile(maze,params);
    }
    else{
        handleError(7);
    }
    
    if (strcmp(solutionFileExtension, "txt") == 0) 
    {
        solutionType='t'; 
    } else if (strcmp(solutionFileExtension, "bin") == 0) {
        solutionType='b';
    }
    else{
        handleError(6);
    }

    params.solutionType=solutionType;
    params.solutionFileName = malloc(sizeof(char)*strlen(solutionFileName));
    strcpy(params.solutionFileName,solutionFileName);  // dopisywanie danych do parametrów
    removeDeadEnds(maze,params); // usuwanie ślepych zaułków

    findSolution(maze,&params); // poszukiwanie ścieżki
    printf("Labirynt został prawidłowo rozwiązany! \n"); // komunikat końcowy
    return 0;
}
