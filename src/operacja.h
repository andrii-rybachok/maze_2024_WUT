#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "maze.h"

typedef struct {
    uint32_t fileId;
    uint8_t escape;
    uint16_t columns;
    uint16_t lines;
    uint16_t entryX;
    uint16_t entryY;
    uint16_t exitX;
    uint16_t exitY;
    uint64_t reserved;
    uint32_t counter;
    uint32_t solutionOffset;
    uint8_t separator;
    uint8_t wall;
    uint8_t path;
} FileHeader;

typedef struct {
    uint8_t separator;
    uint8_t value;
    uint8_t count;
} CodeWord;

typedef struct {
    uint32_t direction;
    uint8_t steps;
} SolutionHeader;

typedef struct {
    uint8_t direction;
    uint8_t counter;
} SolutionStep;

// Function prototypes
void readMazeFromBinary(const char* filename, unsigned int maze[], mazeParams* params);
void writeMazeToBinary(const char* filename, unsigned int maze[], mazeParams params);