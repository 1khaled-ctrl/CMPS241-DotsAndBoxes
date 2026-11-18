# Dots and Boxes — CMPS 241 Project (Sprint 1)

A two-player Dots and Boxes game written in C. It runs in the terminal,
on Alpine Linux inside a virtual machine.

**Team:** Khaled Saber · leonardo Khayyt

## Build and run

```sh
make            # builds the game
./dotsandboxes  # plays the game
make test       # builds and runs the unit tests
make clean      # deletes the .o files and the programs
```

## How to play

- The board has 4 rows x 5 columns of boxes (5 rows x 6 columns of dots).
- Players A and B take turns. A move is 4 numbers: the row and column of the
  first dot, then the row and column of the second dot. Example: `0 3 1 3`
  draws a vertical line from dot (0,3) down to dot (1,3).
- The two dots must be next to each other, and the line must not be drawn yet.
- If your line completes a box, your letter goes inside it, you get 1 point
  and you play again.
- When all 20 boxes are claimed, the player with more boxes wins.

## Files

| File | What it does |
|---|---|
| `board.h`, `board.c` | Board data (lines, box owners, scores) and the rules: check a move, draw a line, complete boxes |
| `display.h`, `display.c` | Printing the board, the scores, error messages and the winner |
| `input.h`, `input.c` | Reading a move safely with `fgets` + `sscanf` |
| `main.c` | The game loop: turns, extra turn after completing a box, end of the game |
| `test_board.c` | Unit tests for the rules (uses `assert`) |
| `Makefile` | Builds the game and the tests |
| `docs/alpine_setup.md` | How we set up the Alpine VM so it starts the game at boot |

## Checking and debugging

```sh
valgrind --leak-check=full ./dotsandboxes   # memory errors and leaks
gdb ./dotsandboxes                          # step through the code
```

## Complexity of checking for a completed box

A new line can only complete the boxes that touch it: at most 2 boxes
(above and below a horizontal line, left and right of a vertical line).
`applyMove` checks only those 2 boxes, 4 sides each, so the check takes
constant time, **O(1)** per move, instead of scanning the whole board
(O(rows x columns)).
