#include "binaryAdapter.h"

binHeader getFileHeader(char* fileName){
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        handleError(2);
        return;
    }
    binHeader header;
    fread(&header, sizeof(header), 1, file);
    return header;
}

void printBinSolution(char* fileName){
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    solutionHeader header;
    fread(&header, sizeof(header), 1, file);
    printf("Solution ID %d, kroki %d \n",header.solutionId,header.steps);
    solutionStep step;

    while (fread(&step, sizeof(step), 1, file) == 1) {
        printf("Kierunek: %c, kroki: %d\n", step.direction, step.counter);
    }
}
void printBinHeader(const binHeader *header) {
    printf("File ID: %u\n", header->file_id);
    printf("Escape: %c\n", header->escape);
    printf("Columns: %hu\n", header->columns);
    printf("Lines: %hu\n", header->lines);
    printf("Entry X: %hu\n", header->entry_x);
    printf("Entry Y: %hu\n", header->entry_y);
    printf("Exit X: %hu\n", header->exit_x);
    printf("Exit Y: %hu\n", header->exit_y);
    printf("Counter: %d\n", header->counter);
    printf("Solution Offset: %d\n", header->solution_offset);
    printf("Separator: %c\n", header->separator);
    printf("Wall: %c\n", header->wall);
    printf("Path: %c\n", header->path);
}
