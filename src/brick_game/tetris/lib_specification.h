#ifndef LIB_SPECIFICATION_H_
#define LIB_SPECIFICATION_H_

#include <stdbool.h>

typedef enum {
  Start = 0,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;  // 0 - default; 1 - start state pause; 2 - pause; 3 - exit state;
              // 4 - game over
} GameInfo_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

#endif  // LIB_SPECIFICATION_H_
