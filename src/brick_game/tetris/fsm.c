#include "fsm.h"

static signal fsm_table[7][8] = {
    {spawn, NULL, exitstate, NULL, NULL, NULL, NULL, NULL},
    {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
    {NULL, pause, exitstate, moveleft, moveright, NULL, movedown, rotate},
    {shifting, shifting, shifting, shifting, shifting, shifting, shifting,
     shifting},
    {attach, attach, attach, attach, attach, attach, attach, attach},
    {gameover, gameover, gameover, gameover, gameover, gameover, gameover,
     gameover},
    {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
     exitstate, exitstate}};

void userInput(UserAction_t action, bool hold) {
  signal act = NULL;
  Params_t parameters = get_params();

  act = fsm_table[*parameters.state][action];

  if (act) act(&parameters);
}

Params_t get_params() {
  static GameInfo_t ginfo = {NULL, NULL, 0, 0, 0, 0, 0};
  static BrickState_t state = {START};
  static PlayerPos_t pos = {NULL, 0, 0};
  static Params_t prms;
  prms.brick_pos = &pos;
  prms.game_info = &ginfo;
  prms.state = &state;

  return prms;
}

UserAction_t get_action() {
  UserAction_t rc = Start;
  int key = getch();

  if (key == KEY_UP)
    rc = Up;
  else if (key == KEY_DOWN)
    rc = Down;
  else if (key == KEY_LEFT)
    rc = Left;
  else if (key == KEY_RIGHT)
    rc = Right;
  else if (key == ESCAPE)
    rc = Terminate;
  else if (key == ENTER_KEY)
    rc = Start;
  else if (key == ' ')
    rc = Action;
  else if (key == 'p' || key == 'P')
    rc = Pause;

  return rc;
}

void spawn(Params_t *prms) { 
  mvprintw(5, 2, "spawn ");
  *prms->state = MOVING;
}
void movedown(Params_t *prms) {
  mvprintw(5, 2, "down  ");
  *prms->state = MOVING;
}
void moveright(Params_t *prms) {
  mvprintw(5, 2, "right ");
  *prms->state = MOVING;
}
void moveleft(Params_t *prms){
  mvprintw(5, 2, "left  ");
  *prms->state = MOVING;
}
void shifting(Params_t *prms) {
  mvprintw(5, 2, "shift ");
  *prms->state = MOVING;
}
void attach(Params_t *prms) {
  mvprintw(5, 2, "attach");
  *prms->state = SPAWN;
}
void gameover(Params_t *prms) {
  mvprintw(5, 2, "GAMEOVER");
  *prms->state = GAMEOVER;
}
void exitstate(Params_t *prms) {
  mvprintw(5, 2, "ABOBA");
  *prms->state = EXIT_STATE;
}
void pause(Params_t *prms) {
  mvprintw(5, 2, "pause ");
  *prms->state = MOVING;
}
void rotate(Params_t *prms) {
  mvprintw(5, 2, "rotate");
  *prms->state = MOVING;
}
