#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "display.h"

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

        if (scanf("%d %d %d %d", &r1, &c1, &r2, &c2) != 4)
        {
            printf("Could not read 4 numbers. The game was stopped.\n");
            return EXIT_FAILURE;
        }

        if (checkMove(&board, r1, c1, r2, c2) != MOVE_OK)
        {
            printf("Invalid move. Try again.\n");
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
