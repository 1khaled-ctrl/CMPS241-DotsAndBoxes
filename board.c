/*
 * board.c - The rules: checking a move, drawing a line, completing boxes.
 */
#include "board.h"

// Puts the two dots in order so that (r1,c1) is the top (or left) dot.
// It gets pointers so it can change the caller's variables (like swap in Lecture 3).
static void orderDots(int *r1, int *c1, int *r2, int *c2) {
    if (*r2 < *r1 || (*r2 == *r1 && *c2 < *c1)) {
        int tmp = *r1;
        *r1 = *r2;
        *r2 = tmp;

        tmp = *c1;
        *c1 = *c2;
        *c2 = tmp;
    }
}

// Returns 1 if (r,c) is a dot of the board, 0 otherwise.
static int isDot(int r, int c) {
    return r >= 0 && r < DOT_ROWS && c >= 0 && c < DOT_COLS;
}

// Returns 1 if the 4 sides of box (r,c) are drawn, 0 otherwise.
static int hasFourSides(const Board *b, int r, int c) {
    return b->hLines[r][c] && b->hLines[r + 1][c] &&   // top and bottom
           b->vLines[r][c] && b->vLines[r][c + 1];     // left and right
}

// Gives box (r,c) to player if the box exists, has no owner yet and is now closed.
// Returns 1 if the player got the box, 0 otherwise.
static int claimBox(Board *b, int r, int c, char player) {
    if (r < 0 || r >= BOX_ROWS || c < 0 || c >= BOX_COLS) {
        return 0;   // no box on this side of the line (edge of the board)
    }
    if (b->owner[r][c] != NO_OWNER || !hasFourSides(b, r, c)) {
        return 0;
    }

    b->owner[r][c] = player;
    if (player == 'A') {
        b->scoreA++;
    } else {
        b->scoreB++;
    }
    b->boxesLeft--;
    return 1;
}

void initBoard(Board *b) {
    int r, c;

    for (r = 0; r < DOT_ROWS; r++) {
        for (c = 0; c < BOX_COLS; c++) {
            b->hLines[r][c] = 0;
        }
    }
    for (r = 0; r < BOX_ROWS; r++) {
        for (c = 0; c < DOT_COLS; c++) {
            b->vLines[r][c] = 0;
        }
    }
    for (r = 0; r < BOX_ROWS; r++) {
        for (c = 0; c < BOX_COLS; c++) {
            b->owner[r][c] = NO_OWNER;
        }
    }
    b->scoreA = 0;
    b->scoreB = 0;
    b->boxesLeft = TOTAL_BOXES;
}

MoveStatus checkMove(const Board *b, int r1, int c1, int r2, int c2) {
    if (!isDot(r1, c1) || !isDot(r2, c2)) {
        return MOVE_OUT_OF_RANGE;
    }

    // r1, c1, r2, c2 are copies (pass-by-value), so this does not change the caller's numbers.
    orderDots(&r1, &c1, &r2, &c2);

    if (r1 == r2 && c2 == c1 + 1) {          // same row, next column: horizontal line
        if (b->hLines[r1][c1]) {
            return MOVE_TAKEN;
        }
        return MOVE_OK;
    }
    if (c1 == c2 && r2 == r1 + 1) {          // same column, next row: vertical line
        if (b->vLines[r1][c1]) {
            return MOVE_TAKEN;
        }
        return MOVE_OK;
    }
    return MOVE_NOT_ADJACENT;                // diagonal, too far, or the same dot twice
}

int applyMove(Board *b, int r1, int c1, int r2, int c2, char player) {
    int completed = 0;

    orderDots(&r1, &c1, &r2, &c2);

    // A new line can only complete the (at most) 2 boxes that touch it,
    // so we check those 2 boxes instead of the whole board: O(1) per move.
    if (r1 == r2) {
        // Horizontal line: the box above it and the box below it.
        b->hLines[r1][c1] = 1;
        completed += claimBox(b, r1 - 1, c1, player);
        completed += claimBox(b, r1, c1, player);
    } else {
        // Vertical line: the box on its left and the box on its right.
        b->vLines[r1][c1] = 1;
        completed += claimBox(b, r1, c1 - 1, player);
        completed += claimBox(b, r1, c1, player);
    }
    return completed;
}

int isGameOver(const Board *b) {
    return b->boxesLeft == 0;
}
