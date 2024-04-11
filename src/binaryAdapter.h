#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include "userCommunication.h"
#ifndef binaryAdapter
#define binaryAdapter
#pragma pack(push, 1)
typedef struct {
    unsigned int file_id;
    unsigned char escape;
    unsigned short columns;
    unsigned short lines;
    unsigned short entry_x;
    unsigned short entry_y;
    unsigned short exit_x;
    unsigned short exit_y;
    long int reserved;
    int reserve;
    int counter;
    int solution_offset;
    char separator;
    char wall;
    char path;
} binHeader; // 1 sekcja nagłówka


typedef struct {
    char separator;
    char value;
    unsigned char count;
} mazeKeys; // słowa kodowe


typedef struct {
    int solutionId;
    int steps;
} solutionHeader; // sekcja nagłówka rozwiązania

typedef struct {
    char direction;
    char counter;
} solutionStep; // krok rozwiązania

#pragma pack(pop)
binHeader getFileHeader(char* fileName); // czytanie nagłówka
void printBinSolution(char* fileName); // print rozwiązania pliku binarnego
void printBinHeader(const binHeader *header); // funkcja dla wyświetlania danych nagłówku
#endif

