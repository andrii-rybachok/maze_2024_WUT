
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


#define MAZE_SIZE_X 2049 //maksymalne rozmiary labiryntu
#define MAZE_SIZE_Y 2049



void findSolution(unsigned int maze[],mazeParams* params); // znałezienie oraz zapisywanie najkr. ścieżki

mazeParams initializeParams(char* originFileName); // inicjalizacja parametrów dla labiryntu (txt)
mazeParams initializeParamsBin(char* originFileName); // inicjalizacja parametrów dla labiryntu (bin)

int readMazeFromFile(unsigned int maze[], mazeParams params); // wyczytanie labiryntu z pliku txt
void readMazeFromBinFile(unsigned int maze[],mazeParams params); // wyczytanie labiryntu z pliku bin

void removeDeadEnds(unsigned int maze[],mazeParams params); // usuwanie ślepych zaułków



