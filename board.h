/*
 * board.h - The Dots and Boxes board and the rules of the game.
 *
 * The board has 4 rows x 5 columns of BOXES, so it has
 * 5 rows x 6 columns of DOTS. Dot (0,0) is the top-left dot.
 *
 *       0 1 2 3 4 5      <- dot columns
 *     0 . . . . . .
 *     1 . . . . . .      a box is the square between 4 dots
 *     ...
 */
#ifndef BOARD_H_
#define BOARD_H_

#define BOX_ROWS 4                        // rows of boxes
#define BOX_COLS 5                        // columns of boxes
#define DOT_ROWS (BOX_ROWS + 1)           // rows of dots
#define DOT_COLS (BOX_COLS + 1)           // columns of dots
#define TOTAL_BOXES (BOX_ROWS * BOX_COLS) // 20 boxes in total

#define NO_OWNER ' '   // a box that nobody has completed yet

// The answer we get when we check a move before playing it.
typedef enum {
    MOVE_OK,            // the line can be drawn
    MOVE_OUT_OF_RANGE,  // one of the dots is outside the board
    MOVE_NOT_ADJACENT,  // the two dots are not next to each other
    MOVE_TAKEN          // this line is already drawn
} MoveStatus;

typedef struct {
    // hLines[r][c] is 1 when the line from dot (r,c) to dot (r,c+1) is drawn.
    int hLines[DOT_ROWS][BOX_COLS];
    // vLines[r][c] is 1 when the line from dot (r,c) to dot (r+1,c) is drawn.
    int vLines[BOX_ROWS][DOT_COLS];
    // owner[r][c] is 'A', 'B' or NO_OWNER for the box whose top-left dot is (r,c).
    char owner[BOX_ROWS][BOX_COLS];
    int scoreA;
    int scoreB;
    int boxesLeft;      // boxes nobody owns yet; the game ends when this is 0
} Board;

// Empties the board: no lines, no owners, both scores 0.
void initBoard(Board *b);

// Checks whether the line between dot (r1,c1) and dot (r2,c2) can be drawn.
MoveStatus checkMove(const Board *b, int r1, int c1, int r2, int c2);

// Draws the line between dot (r1,c1) and dot (r2,c2) (call checkMove first)
// and gives every box this line completes to player ('A' or 'B').
// Returns how many boxes were completed: 0, 1 or 2.
int applyMove(Board *b, int r1, int c1, int r2, int c2, char player);

// Returns 1 when all the boxes have an owner, 0 otherwise.
int isGameOver(const Board *b);

#endif  // BOARD_H_
