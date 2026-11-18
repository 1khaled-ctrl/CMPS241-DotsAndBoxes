#ifndef INPUT_H_
#define INPUT_H_

// The possible answers when we read a move from the keyboard.
typedef enum inputStatus
{
    INPUT_OK,
    INPUT_BAD,
    INPUT_END
} InputStatus;

InputStatus readMove(int *r1, int *c1, int *r2, int *c2);

#endif  // INPUT_H_
