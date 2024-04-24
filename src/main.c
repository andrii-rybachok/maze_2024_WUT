
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

    char * mainFileName, *solutionFileName; // nazwa pliku wejściowego oraz wyjściowego (razem z rozszerzeniem)

    char solutionType='n'; // typ rozwiązania, n - nijaki, b- binarny, t- tekstowy
    
    if(argc<=1){
        handleError(1); 
    }
    while ((opt = getopt(argc, argv, "f:s:h")) != -1)  
        {  
            switch (opt)  
            {  
                case 's': //nazwa pliku rozwiązania
                    solutionFileName= malloc(sizeof(char)*strlen(optarg)+1);
                    strcpy( solutionFileName,optarg); 
                    break;  
                case 'f': //nazwa pliku labiryntu
                    mainFileName= malloc(sizeof(char)*strlen(optarg)+1);
                    strcpy( mainFileName,optarg); 
                    break;
                case 'h': // wywołanie help
                    printHelp();
                    exit(EXIT_SUCCESS);
                    break;
                case ':':
                    handleError(1); 
                    break;  
                default:  
                    handleError(1); 
                    break;  
        }  
    } 
    if(mainFileName==NULL || solutionFileName==NULL){
        handleError(1); 
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
        readMazeFromFile(&params); // wywołanie funkcji, jaka czyta plik .txt i zapisuje do tablicy 

    
    } else if (strcmp(mainFileExtension, "bin") == 0) {
        params=initializeParamsBin(mainFileName); // inicjalizacja parametrów labiryntu dla .bin
        readMazeFromBinFile(&params);
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
    removeDeadEnds(&params); // usuwanie ślepych zaułków

    findSolution(&params); // poszukiwanie ścieżki
    printf("Labirynt został prawidłowo rozwiązany! \n"); // komunikat końcowy
    return 0;
}