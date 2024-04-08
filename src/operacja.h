#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


#define FILE_ID 0x52524243
#define ESCAPE_CHAR 0x1B

typedef struct {
    uint32_t fileId;
    uint8_t escape;
    uint16_t columns;
    uint16_t lines;
    uint16_t entryX;
    uint16_t entryY;
    uint16_t exitX;
    uint16_t exitY;
    uint32_t reserved;
    uint32_t counter;
    uint32_t solutionOffset;
    uint8_t separator;
    uint8_t wall;
    uint8_t path;
} BinaryMazeHeader;

typedef struct {
    uint8_t separator;
    uint8_t value;
    uint8_t count;
} BinaryWordHeader;

typedef struct {
    uint32_t direction;
    uint8_t steps;
} BinarySolutionHeader;

typedef struct {
    uint8_t direction;
    uint8_t counter;
} BinarySolutionStep;

