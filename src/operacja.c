#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacja.h" 

void readMazeFromBinary(const char* filename, unsigned int maze[], mazeParams* params) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        // Handle error
        return;
    }

    FileHeader header;
    fread(&header, sizeof(FileHeader), 1, file);

    // Read code words
    for (int i = 0; i < header.counter; i++) {
        CodeWord codeWord;
        fread(&codeWord, sizeof(CodeWord), 1, file);
        // Process code word
    }

    // Read solution header if solution offset is non-zero
    if (header.solutionOffset != 0) {
        SolutionHeader solutionHeader;
        fread(&solutionHeader, sizeof(SolutionHeader), 1, file);
        // Process solution header

        // Read solution steps
        for (int i = 0; i < solutionHeader.steps; i++) {
            SolutionStep step;
            fread(&step, sizeof(SolutionStep), 1, file);
            // Process solution step
        }
    }

    fclose(file);
}

void writeMazeToBinary(const char* filename, unsigned int maze[], mazeParams params) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        // Handle error
        return;
    }

    FileHeader header;
    // Populate header fields
    fwrite(&header, sizeof(FileHeader), 1, file);

    // Write code words
    for (int i = 0; i < header.counter; i++) {
        CodeWord codeWord;
        // Populate code word fields
        fwrite(&codeWord, sizeof(CodeWord), 1, file);
    }

    // Write solution header if applicable
    if (header.solutionOffset != 0) {
        SolutionHeader solutionHeader;
        // Populate solution header fields
        fwrite(&solutionHeader, sizeof(SolutionHeader), 1, file);

        // Write solution steps
        for (int i = 0; i < solutionHeader.steps; i++) {
            SolutionStep step;
            // Populate solution step fields
            fwrite(&step, sizeof(SolutionStep), 1, file);
        }
    }

    fclose(file);
}
