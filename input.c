#include <stdio.h>
#include "input.h"

#define LINE_SIZE 100

// Accepts an input only if it is exactly 4 numbers.
InputStatus readMove(int *r1, int *c1, int *r2, int *c2)
{
    char line[LINE_SIZE];
    char extra; //accounts for any other stuff typed after the correct input ex: 0 0 0 1 'ahdhdsdsh'

    if (fgets(line, LINE_SIZE, stdin) == NULL) //user closed input ex: Ctrl+D
    {
        return INPUT_END;
    }
    if (sscanf(line, "%d %d %d %d %c", r1, c1, r2, c2, &extra) != 4) // it return the number of chars it filled
    {                                                                //it transforms a letter '1' to the num '1'
        return INPUT_BAD;                                            //if not num ex: 'a' it will crash
    }                                                                
    return INPUT_OK;
}
