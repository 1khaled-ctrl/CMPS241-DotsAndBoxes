#include "bot.h"

// Counts how many sides a box already has drawn.
static int sidesOfBox(const Board *b, int r, int c)
{
    return b->hLines[r][c] + b->hLines[r + 1][c]
         + b->vLines[r][c] + b->vLines[r][c + 1];
}

// Returns 1 if drawing the line r1,c1->r2,c2 would give the opponent a box on the next turn.
// A line is dangerous if it completes a third side of any adjacent box (leaving it one side short).
static int isDangerous(const Board *b, int r1, int c1, int r2, int c2)
{
    int br, bc;

    if (r1 == r2)
    {
        // horizontal line: check box above (r1-1,c1) and box below (r1,c1)
        br = r1 - 1; bc = c1;
        if (br >= 0 && br < BOX_ROWS && bc >= 0 && bc < BOX_COLS)
        {
            if (sidesOfBox(b, br, bc) == 2)
            {
                return 1;
            }
        }
        br = r1; bc = c1;
        if (br >= 0 && br < BOX_ROWS && bc >= 0 && bc < BOX_COLS)
        {
            if (sidesOfBox(b, br, bc) == 2)
            {
                return 1;
            }
        }
    }
    else
    {
        // vertical line: check box to the left (r1,c1-1) and box to the right (r1,c1)
        br = r1; bc = c1 - 1;
        if (br >= 0 && br < BOX_ROWS && bc >= 0 && bc < BOX_COLS)
        {
            if (sidesOfBox(b, br, bc) == 2)
            {
                return 1;
            }
        }
        br = r1; bc = c1;
        if (br >= 0 && br < BOX_ROWS && bc >= 0 && bc < BOX_COLS)
        {
            if (sidesOfBox(b, br, bc) == 2)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Tries to store a move in *r1,*c1,*r2,*c2 and returns 1 if one was found, 0 if not.
// Priority 1: complete a box (3 sides already drawn).
// Priority 2: draw a safe line (does not give the opponent a 3-sided box).
// Priority 3: any remaining valid line (forced sacrifice).
static int tryFindMove(const Board *b, int *r1, int *c1, int *r2, int *c2)
{
    int r, c;
    int safeR1 = -1, safeC1, safeR2, safeC2;
    int anyR1  = -1, anyC1,  anyR2,  anyC2;

    // Check all horizontal lines.
    for (r = 0; r < DOT_ROWS; r++)
    {
        for (c = 0; c < BOX_COLS; c++)
        {
            if (b->hLines[r][c])
            {
                continue;
            }
            // Priority 1: this line closes a box right now.
            int above = (r > 0        && r - 1 < BOX_ROWS && sidesOfBox(b, r - 1, c) == 3);
            int below = (r < BOX_ROWS &&                     sidesOfBox(b, r,     c) == 3);
            if (above || below)
            {
                *r1 = r; *c1 = c; *r2 = r; *c2 = c + 1;
                return 1;
            }
            // Priority 2: safe.
            if (!isDangerous(b, r, c, r, c + 1) && safeR1 == -1)
            {
                safeR1 = r; safeC1 = c; safeR2 = r; safeC2 = c + 1;
            }
            // Priority 3: any.
            if (anyR1 == -1)
            {
                anyR1 = r; anyC1 = c; anyR2 = r; anyC2 = c + 1;
            }
        }
    }

    // Check all vertical lines.
    for (r = 0; r < BOX_ROWS; r++)
    {
        for (c = 0; c < DOT_COLS; c++)
        {
            if (b->vLines[r][c])
            {
                continue;
            }
            // Priority 1: this line closes a box right now.
            int left  = (c > 0        && c - 1 < BOX_COLS && sidesOfBox(b, r, c - 1) == 3);
            int right = (c < BOX_COLS &&                     sidesOfBox(b, r, c    ) == 3);
            if (left || right)
            {
                *r1 = r; *c1 = c; *r2 = r + 1; *c2 = c;
                return 1;
            }
            // Priority 2: safe.
            if (!isDangerous(b, r, c, r + 1, c) && safeR1 == -1)
            {
                safeR1 = r; safeC1 = c; safeR2 = r + 1; safeC2 = c;
            }
            // Priority 3: any.
            if (anyR1 == -1)
            {
                anyR1 = r; anyC1 = c; anyR2 = r + 1; anyC2 = c;
            }
        }
    }

    if (safeR1 != -1)
    {
        *r1 = safeR1; *c1 = safeC1; *r2 = safeR2; *c2 = safeC2;
        return 1;
    }
    if (anyR1 != -1)
    {
        *r1 = anyR1; *c1 = anyC1; *r2 = anyR2; *c2 = anyC2;
        return 1;
    }
    return 0;
}

// Picks the best move for the bot and stores it in r1, c1, r2, c2.
void botMove(const Board *b, int *r1, int *c1, int *r2, int *c2)
{
    tryFindMove(b, r1, c1, r2, c2);
}
