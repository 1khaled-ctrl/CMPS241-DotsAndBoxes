#include <stdio.h>
#include <stdlib.h> //  EXIT_FAILURE = 1     EXIT_SUCCESS = 0
#include "board.h"
#include "display.h"
#include "input.h"

// Returns the player whose turn comes next.
static char otherPlayer(char player)
{
    if (player == 'A')
    {
        return 'B';
    }
    return 'A';
}

// Runs the game: players A and B take turns drawing lines until every box is taken, then the winner is announced.
// A player who closes a box plays again.
int main()
{
    Board board;
    char player = 'A';
    int r1, c1, r2, c2;

    initBoard(&board);
    printBoard(&board);

    while (!isGameOver(&board))
    {
        printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:\n", player);

        InputStatus input = readMove(&r1, &c1, &r2, &c2);
        if (input == INPUT_END)
        {
            printf("\nNo more input. The game was stopped.\n");
            return EXIT_FAILURE;
        }
        if (input == INPUT_BAD)
        {
            printf("Invalid input: type 4 numbers, for example: 0 0 0 1\n");
            continue;
        }

        MoveStatus status = checkMove(&board, r1, c1, r2, c2);
        if (status != MOVE_OK)
        {
            printMoveError(status);
            continue;
        }

        int completed = applyMove(&board, r1, c1, r2, c2, player);
        printScores(&board);
        printBoard(&board);

        if (completed == 0)
        {
            player = otherPlayer(player);
        }
    }

    printWinner(&board);
    return EXIT_SUCCESS;
}
