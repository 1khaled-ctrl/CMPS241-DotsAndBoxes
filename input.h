#ifndef INPUT_H_
#define INPUT_H_

// The possible answers when we read a move from the keyboard.
enum inputStatus
{
    INPUT_OK,
    INPUT_BAD,
    INPUT_END
};

typedef enum inputStatus InputStatus; // renaming it so that not everytime we write enum inputStatus

InputStatus readMove(int *r1, int *c1, int *r2, int *c2);

#endif  // INPUT_H_
