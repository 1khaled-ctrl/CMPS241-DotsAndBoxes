#ifndef BOARD_H_
#define BOARD_H_
#define BOX_ROWS 4
#define BOX_COLS 5
#define DOT_ROWS (BOX_ROWS + 1)
#define DOT_COLS (BOX_COLS + 1)
#define TOTAL_BOXES (BOX_ROWS * BOX_COLS)
#define NO_OWNER ' '

// The possible answers when we check if a move is allowed.
enum moveStatus
{
    MOVE_OK,
    MOVE_OUT_OF_RANGE,
    MOVE_NOT_ADJACENT,
    MOVE_TAKEN
};

typedef enum moveStatus MoveStatus;

// The board: the horizontal lines (hLines) and vertical lines (vLines) drawn so far, who owns each box, and the scores.
struct board
{
    int hLines[DOT_ROWS][BOX_COLS];
    int vLines[BOX_ROWS][DOT_COLS];
    char owner[BOX_ROWS][BOX_COLS];
    int scoreA;
    int scoreB;
    int boxesLeft;
};

typedef struct board Board;

void initBoard(Board *b);
MoveStatus checkMove(const Board *b, int r1, int c1, int r2, int c2);
int applyMove(Board *b, int r1, int c1, int r2, int c2, char player);
int isGameOver(const Board *b);

#endif  // BOARD_H_
