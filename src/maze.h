
#include "userCommunication.h"
#include "list.h"
#include "binaryAdapter.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAZE_START 'P' // Symbol początku
#define MAZE_END 'K' //końca
#define MAZE_WALL 'X'// ściany
#define MAZE_PATH ' '//ścieżki


#define MAZE_SIZE_X 2051 //maksymalne rozmiary labiryntu
#define MAZE_SIZE_Y 2049



void findSolution(mazeParams* params); // znałezienie oraz zapisywanie najkr. ścieżki

mazeParams initializeParams(char* originFileName); // inicjalizacja parametrów dla labiryntu (txt)
mazeParams initializeParamsBin(char* originFileName); // inicjalizacja parametrów dla labiryntu (bin)

int readMazeFromFile(mazeParams* params); // wyczytanie labiryntu z pliku txt
void readMazeFromBinFile(mazeParams* params); // wyczytanie labiryntu z pliku bin

void removeDeadEnds(mazeParams* params); // usuwanie ślepych zaułków



