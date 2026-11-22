#ifndef BOT_H_
#define BOT_H_

#include "board.h"

// Picks the best move for the bot and stores it in r1, c1, r2, c2.
void botMove(const Board *b, int *r1, int *c1, int *r2, int *c2);

#endif  // BOT_H_
