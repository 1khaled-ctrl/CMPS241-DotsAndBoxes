#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "display.h"
#include "input.h"
#include "bot.h"

// Returns the player whose turn comes next.
static char otherPlayer(char player)
{
    if (player == 'A')
    {
        return 'B';
    }
    return 'A';
}

// Asks the player to choose between human vs human or human vs bot. Returns 1 for bot mode, 0 for two players.
static int askMode()
{
    char line[8];
    char extra;

    printf("Select mode:\n");
    printf("  1 - Two players\n");
    printf("  2 - Play against bot\n");
    printf("Enter 1 or 2: ");

    while (1)
    {
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            return 0;
        }
        int choice;
        if (sscanf(line, "%d %c", &choice, &extra) == 1 && (choice == 1 || choice == 2))
        {
            return choice == 2;
        }
        printf("Please enter 1 or 2: ");
    }
}

// Runs the game: players take turns drawing lines until every box is taken, then the winner is announced.
// A player who closes a box plays again. In bot mode, Player B is the bot.
int main()
{
    Board board;
    char player = 'A';
    int r1, c1, r2, c2;

    int botMode = askMode();

    initBoard(&board);
    printBoard(&board);

    while (!isGameOver(&board))
    {
        if (botMode && player == 'B')
        {
            printf("Bot's turn.\n");
            botMove(&board, &r1, &c1, &r2, &c2);
            printf("Bot plays: %d %d -> %d %d\n", r1, c1, r2, c2);
        }
        else
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
