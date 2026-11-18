#include "board.h"

// Swaps the two dots if needed, so the first dot is always the top one or the left one.
static void orderDots(int *r1, int *c1, int *r2, int *c2)
{
    if (*r2 < *r1 || (*r2 == *r1 && *c2 < *c1))
    {
        int tmp = *r1;
        *r1 = *r2;
        *r2 = tmp;

        tmp = *c1;
        *c1 = *c2;
        *c2 = tmp;
    }
}

// Tells if a row and column is a real dot on the board.
static int isDot(int r, int c)
{
    return r >= 0 && r < DOT_ROWS && c >= 0 && c < DOT_COLS;
}

// Tells if all four sides of a box are drawn.
static int hasFourSides(const Board *b, int r, int c)
{
    return b->hLines[r][c] && b->hLines[r + 1][c] && b->vLines[r][c] && b->vLines[r][c + 1];
}

// Gives a box to the player if the box exists, has no owner yet and is now closed. Returns 1 if the player got it.
static int claimBox(Board *b, int r, int c, char player)
{
    if (r < 0 || r >= BOX_ROWS || c < 0 || c >= BOX_COLS)
    {
        return 0;
    }
    if (b->owner[r][c] != NO_OWNER || !hasFourSides(b, r, c))
    {
        return 0;
    }

    b->owner[r][c] = player;
    if (player == 'A')
    {
        b->scoreA++;
    }
    else
    {
        b->scoreB++;
    }
    b->boxesLeft--;
    return 1;
}

// Starts a new empty board: no lines, no owners, both scores at zero.
void initBoard(Board *b)
{
    int r, c;

    for (r = 0; r < DOT_ROWS; r++)
    {
        for (c = 0; c < BOX_COLS; c++)
        {
            b->hLines[r][c] = 0;
        }
    }
    for (r = 0; r < BOX_ROWS; r++)
    {
        for (c = 0; c < DOT_COLS; c++)
        {
            b->vLines[r][c] = 0;
        }
    }
    for (r = 0; r < BOX_ROWS; r++)
    {
        for (c = 0; c < BOX_COLS; c++)
        {
            b->owner[r][c] = NO_OWNER;
        }
    }
    b->scoreA = 0;
    b->scoreB = 0;
    b->boxesLeft = TOTAL_BOXES;
}

// Checks if a line can be drawn between the two dots. If not, it says why.
MoveStatus checkMove(const Board *b, int r1, int c1, int r2, int c2)
{
    if (!isDot(r1, c1) || !isDot(r2, c2))
    {
        return MOVE_OUT_OF_RANGE;
    }

    orderDots(&r1, &c1, &r2, &c2);

    if (r1 == r2 && c2 == c1 + 1)
    {
        if (b->hLines[r1][c1])
        {
            return MOVE_TAKEN;
        }
        return MOVE_OK;
    }
    if (c1 == c2 && r2 == r1 + 1)
    {
        if (b->vLines[r1][c1])
        {
            return MOVE_TAKEN;
        }
        return MOVE_OK;
    }
    return MOVE_NOT_ADJACENT;
}

// Draws the line, then checks the two boxes on each side of it and gives the player any box that is now closed.
// Returns how many boxes were closed: 0, 1 or 2.
int applyMove(Board *b, int r1, int c1, int r2, int c2, char player)
{
    int completed = 0;

    orderDots(&r1, &c1, &r2, &c2);

    if (r1 == r2)
    {
        b->hLines[r1][c1] = 1;
        completed += claimBox(b, r1 - 1, c1, player);
        completed += claimBox(b, r1, c1, player);
    }
    else
    {
        b->vLines[r1][c1] = 1;
        completed += claimBox(b, r1, c1 - 1, player);
        completed += claimBox(b, r1, c1, player);
    }
    return completed;
}

// Tells if the game is over: every box has an owner.
int isGameOver(const Board *b)
{
    return b->boxesLeft == 0;
}
