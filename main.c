#include <stdlib.h>
#include "board.h"
#include "display.h"

// Temporary test of the display: shows the empty board, plays 4 moves from the sample run, then shows the board again.
int main()
{
    Board board;

    initBoard(&board);
    printBoard(&board);

    applyMove(&board, 0, 4, 0, 3, 'A');
    applyMove(&board, 0, 4, 1, 4, 'B');
    applyMove(&board, 1, 3, 1, 4, 'B');
    applyMove(&board, 0, 3, 1, 3, 'A');

    printScores(&board);
    printBoard(&board);
    return EXIT_SUCCESS;
}
