#include <stdio.h>
#include "input.h"

#define LINE_SIZE 100

// Reads the move typed by the player and accepts it only if it is exactly 4 numbers.
// Returns INPUT_OK if it was typed correctly, INPUT_BAD if not, and INPUT_END if there is no more input (Ctrl+D).
InputStatus readMove(int *r1, int *c1, int *r2, int *c2)
{
    char line[LINE_SIZE];
    char extra;

    if (fgets(line, LINE_SIZE, stdin) == NULL)
    {
        return INPUT_END;
    }
    if (sscanf(line, "%d %d %d %d %c", r1, c1, r2, c2, &extra) != 4)
    {
        return INPUT_BAD;
    }
    return INPUT_OK;
}
