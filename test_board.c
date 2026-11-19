#include <stdio.h>
#include <assert.h>
#include "board.h"

// Checks that a new board has no owners, all 20 boxes left and both scores at zero.
static void testNewBoardIsEmpty()
{
    Board b;
    int r, c;

    initBoard(&b);
    assert(b.scoreA == 0 && b.scoreB == 0);
    assert(b.boxesLeft == TOTAL_BOXES);
    for (r = 0; r < BOX_ROWS; r++)
    {
        for (c = 0; c < BOX_COLS; c++)
        {
            assert(b.owner[r][c] == NO_OWNER);
        }
    }
    assert(!isGameOver(&b));
    printf("PASS: a new board is empty\n");
}

// Checks that dots outside the board, diagonal lines, too-long lines and the same dot twice are refused.
static void testInvalidMovesAreRefused()
{
    Board b;

    initBoard(&b);
    assert(checkMove(&b, 0, 5, 0, 6) == MOVE_OUT_OF_RANGE);
    assert(checkMove(&b, 4, 0, 5, 0) == MOVE_OUT_OF_RANGE);
    assert(checkMove(&b, -1, 0, 0, 0) == MOVE_OUT_OF_RANGE);
    assert(checkMove(&b, 0, 0, 1, 1) == MOVE_NOT_ADJACENT);
    assert(checkMove(&b, 0, 0, 0, 2) == MOVE_NOT_ADJACENT);
    assert(checkMove(&b, 2, 2, 2, 2) == MOVE_NOT_ADJACENT);
    printf("PASS: invalid moves are refused\n");
}

// Checks that the same line cannot be drawn twice, whatever the order of the dots.
static void testLineCannotBeDrawnTwice()
{
    Board b;

    initBoard(&b);
    assert(checkMove(&b, 0, 4, 0, 3) == MOVE_OK);
    applyMove(&b, 0, 4, 0, 3, 'A');
    assert(checkMove(&b, 0, 4, 0, 3) == MOVE_TAKEN);
    assert(checkMove(&b, 0, 3, 0, 4) == MOVE_TAKEN);
    printf("PASS: a line cannot be drawn twice\n");
}

// Checks that closing a box gives it to the player, using the same moves as the sample run in the project PDF.
static void testCompletingOneBox()
{
    Board b;

    initBoard(&b);
    assert(applyMove(&b, 0, 4, 0, 3, 'A') == 0);
    assert(applyMove(&b, 0, 4, 1, 4, 'B') == 0);
    assert(applyMove(&b, 1, 3, 1, 4, 'B') == 0);
    assert(applyMove(&b, 0, 3, 1, 3, 'A') == 1);
    assert(b.owner[0][3] == 'A');
    assert(b.scoreA == 1 && b.scoreB == 0);
    assert(b.boxesLeft == TOTAL_BOXES - 1);
    printf("PASS: completing a box gives it to the player\n");
}

// Checks that one line can close two boxes at the same time.
static void testOneLineCompletesTwoBoxes()
{
    Board b;

    initBoard(&b);
    applyMove(&b, 0, 0, 0, 1, 'A');
    applyMove(&b, 0, 1, 0, 2, 'A');
    applyMove(&b, 1, 0, 1, 1, 'A');
    applyMove(&b, 1, 1, 1, 2, 'A');
    applyMove(&b, 0, 0, 1, 0, 'A');
    applyMove(&b, 0, 2, 1, 2, 'A');
    assert(b.scoreA == 0);

    assert(applyMove(&b, 0, 1, 1, 1, 'B') == 2);
    assert(b.owner[0][0] == 'B' && b.owner[0][1] == 'B');
    assert(b.scoreB == 2);
    printf("PASS: one line can complete two boxes\n");
}

// Checks that the game ends exactly when all 20 boxes have an owner.
static void testGameEndsWhenAllBoxesAreClaimed()
{
    Board b;
    int r, c;

    initBoard(&b);
    for (r = 0; r < DOT_ROWS; r++)
    {
        for (c = 0; c < BOX_COLS; c++)
        {
            applyMove(&b, r, c, r, c + 1, 'A');
        }
    }
    assert(b.scoreA == 0 && !isGameOver(&b));

    for (r = 0; r < BOX_ROWS; r++)
    {
        for (c = 0; c < DOT_COLS; c++)
        {
            applyMove(&b, r, c, r + 1, c, 'B');
        }
    }
    assert(isGameOver(&b));
    assert(b.scoreB == TOTAL_BOXES);
    printf("PASS: the game ends when all %d boxes are claimed\n", TOTAL_BOXES);
}

// Runs all the tests. If one check fails, the program stops and shows which line failed.
int main()
{
    testNewBoardIsEmpty();
    testInvalidMovesAreRefused();
    testLineCannotBeDrawnTwice();
    testCompletingOneBox();
    testOneLineCompletesTwoBoxes();
    testGameEndsWhenAllBoxesAreClaimed();
    printf("All tests passed.\n");
    return 0;
}
