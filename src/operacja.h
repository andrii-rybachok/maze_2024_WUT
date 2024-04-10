#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 


typedef struct {
    uint32_t file_id;
    uint8_t escape;
    uint16_t columns;
    uint16_t lines;
    uint16_t entry_x;
    uint16_t entry_y;
    uint16_t exit_x;
    uint16_t exit_y;
    uint32_t counter;
    uint32_t solution_offset;
    uint8_t separator;
    uint8_t wall;
    uint8_t path;
} FileHeader;

typedef struct {
    uint32_t direction;
    uint8_t steps;
} SolutionHeader;

typedef struct {
    uint8_t direction;
    uint8_t counter;
} SolutionStep;

