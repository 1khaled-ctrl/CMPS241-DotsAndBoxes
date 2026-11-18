#include <stdio.h>
#include "display.h"

#define SEPARATOR "******************************************************************************"

// Shows the board: the dots, the lines drawn so far, and the letter of the player who owns each box.
void printBoard(const Board *b)
{
    int r, c;

    printf(" ");
    for (c = 0; c < DOT_COLS; c++)
    {
        printf(" %d", c);
    }
    printf("\n");

    for (r = 0; r < DOT_ROWS; r++)
    {
        printf("%d ", r);
        for (c = 0; c < DOT_COLS; c++)
        {
            printf(".");
            if (c < BOX_COLS)
            {
                if (b->hLines[r][c])
                {
                    printf("-");
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");

        if (r < BOX_ROWS)
        {
            printf("  ");
            for (c = 0; c < DOT_COLS; c++)
            {
                if (b->vLines[r][c])
                {
                    printf("|");
                }
                else
                {
                    printf(" ");
                }
                if (c < BOX_COLS)
                {
                    printf("%c", b->owner[r][c]);
                }
            }
            printf("\n");
        }
    }
}

// Shows the score of each player between two lines of stars.
void printScores(const Board *b)
{
    printf("%s\n", SEPARATOR);
    printf("Player A score: %d\n", b->scoreA);
    printf("Player B score: %d\n", b->scoreB);
    printf("%s\n", SEPARATOR);
}

// Announces the result at the end of the game: who won, or a tie.
void printWinner(const Board *b)
{
    printf("Game over! All %d boxes have been claimed.\n", TOTAL_BOXES);
    if (b->scoreA > b->scoreB)
    {
        printf("Player A wins %d to %d!\n", b->scoreA, b->scoreB);
    }
    else if (b->scoreB > b->scoreA)
    {
        printf("Player B wins %d to %d!\n", b->scoreB, b->scoreA);
    }
    else
    {
        printf("It's a tie: %d to %d!\n", b->scoreA, b->scoreB);
    }
}
