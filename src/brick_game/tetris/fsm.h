#ifndef FSM_H
#define FSM_H

#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ESCAPE 27
#define ENTER_KEY 10

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACH,
  GAMEOVER,
  EXIT_STATE
} BrickState_t;

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
  int pause;
} GameInfo_t;

typedef struct {
  int **piece;
  int x;
  int y;
} PlayerPos_t;

typedef struct game_params {
  GameInfo_t *game_info;
  BrickState_t *state;
  PlayerPos_t *brick_pos;
} Params_t;

typedef void (*signal)(Params_t *prms);

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();
void init_field(Params_t *prms);
void init_piece(Params_t *prms);

Params_t get_params();

UserAction_t get_action();

void game_loop();

void start(Params_t *prms);
void spawn(Params_t *prms);
void movedown(Params_t *prms);
void moveright(Params_t *prms);
void moveleft(Params_t *prms);
void shifting(Params_t *prms);
void attach(Params_t *prms);
void gameover(Params_t *prms);
void exitstate(Params_t *prms);
void pause(Params_t *prms);
void rotate(Params_t *prms);

#endif  // FSM_H