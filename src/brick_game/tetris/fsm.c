#include "fsm.h"

#include "frontend.h"

static signal fsm_table[7][8] = {
    {start, NULL, exitstate, NULL, NULL, NULL, NULL, NULL},
    {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
    {shifting, pause, exitstate, moveleft, moveright, NULL, movedown, rotate},
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

GameInfo_t updateCurrentState() {
  Params_t prms = get_params();
  print_stats(*prms.game_info);
  print_field(*prms.game_info);
  print_piece(*prms.brick_pos);
  return *prms.game_info;
}

void init_field(Params_t *prms) {
  prms->game_info->field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; ++i) {
    prms->game_info->field[i] = (int *)calloc(10, sizeof(int));
  }
}

void init_piece(Params_t *prms) {
  prms->brick_pos->piece = (int **)calloc(1, sizeof(int *));
  /* for (int i = 0; i < 4; ++i) { */
  prms->brick_pos->piece[0] = (int *)calloc(1, sizeof(int));
  /* } */
  prms->brick_pos->piece[0][0] = 1;
  prms->brick_pos->x = 0;
  prms->brick_pos->y = GAME_W / 2;
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

void start(Params_t *prms) {
  nodelay(stdscr, TRUE);
  timeout(500);
  clear_field();

  *prms->state = SPAWN;
}

void spawn(Params_t *prms) {
  mvprintw(5, 50, "spawn ");
  *prms->state = MOVING;
}
void movedown(Params_t *prms) {
  mvprintw(5, 50, "down  ");
  prms->brick_pos->x += 1;
  *prms->state = MOVING;
}
void moveright(Params_t *prms) {
  mvprintw(5, 50, "right ");
  prms->brick_pos->y += 2;
  *prms->state = MOVING;
}
void moveleft(Params_t *prms) {
  mvprintw(5, 50, "left  ");
  prms->brick_pos->y -= 2;
  *prms->state = MOVING;
}
void shifting(Params_t *prms) {
  mvprintw(5, 50, "shift ");
  prms->brick_pos->x += 1;
  *prms->state = MOVING;
}
void attach(Params_t *prms) {
  mvprintw(5, 50, "attach");
  *prms->state = SPAWN;
}
void gameover(Params_t *prms) {
  mvprintw(5, 50, "GAMEOVER");
  *prms->state = GAMEOVER;
}
void exitstate(Params_t *prms) {
  mvprintw(5, 50, "ABOBA");
  *prms->state = EXIT_STATE;
}
void pause(Params_t *prms) {
  mvprintw(5, 50, "pause ");
  nodelay(stdscr, FALSE);
  char ch = getch();
  if (ch == 'P' || ch == 'p') {
    *prms->state = MOVING;
    nodelay(stdscr, TRUE);
  } else if (ch == ESCAPE) {
    *prms->state = EXIT_STATE;
  } else {
    pause(prms);
  }
}
void rotate(Params_t *prms) {
  mvprintw(5, 50, "rotate");
  *prms->state = MOVING;
}
