#include "fsm.h"

#include "pieces.h"

// Calls a function based on last user input
void userInput(UserAction_t action, bool hold) {
  static signals fsm_table[7][8] = {
      {start, NULL, exitstate, NULL, NULL, NULL, NULL, NULL},
      {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
      {NULL, pause, exitstate, moveleft, moveright, NULL, movedown, rotate},
      {shifting, shifting, shifting, shifting, shifting, shifting, shifting,
       shifting},
      {attach, attach, attach, attach, attach, attach, attach, attach},
      {gameover, gameover, gameover, gameover, gameover, gameover, gameover,
       gameover},
      {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
       exitstate, exitstate}};

  signals act = NULL;
  Params_t parameters = get_params();
  if (parameters.game_info->pause == 3) *parameters.state = EXIT_STATE;
  if (action < 8) act = fsm_table[*parameters.state][action];

  if (act && !parameters.game_info->pause) act(&parameters);
}

// Probably will be responsible for game ticks and shifting a block one line
// down if no input was registered
GameInfo_t updateCurrentState() {
  Params_t parameters = get_params();
  return *parameters.game_info;
}

void start(Params_t *prms) {
  // TODO: game parameters should reinitialize, high score should be updated and
  // saved between runs
  clear_field(prms);
  *prms->state = SPAWN;
}

void spawn(Params_t *prms) {
  transfer_next_piece();
  init_next_piece(prms);
  if (!check_collision(*prms->current_figure)) {
    *prms->state = GAMEOVER;
  } else {
    *prms->state = MOVING;
  }
}

void movedown(Params_t *prms) {
  prms->current_figure->vertical_coords += 1;
  if (!check_collision(*prms->current_figure)) {
    prms->current_figure->vertical_coords -= 1;
    *prms->state = ATTACH;
  } else {
    *prms->state = MOVING;
  }
}
void moveright(Params_t *prms) {
  prms->current_figure->horizontal_coords += 2;
  if (!check_collision(*prms->current_figure))
    prms->current_figure->horizontal_coords -= 2;
  *prms->state = MOVING;
}
void moveleft(Params_t *prms) {
  prms->current_figure->horizontal_coords -= 2;
  if (!check_collision(*prms->current_figure))
    prms->current_figure->horizontal_coords += 2;
  *prms->state = MOVING;
}
void shifting(Params_t *prms) {
  prms->current_figure->vertical_coords += 1;
  if (!check_collision(*prms->current_figure)) {
    prms->current_figure->vertical_coords -= 1;
    *prms->state = ATTACH;
  } else {
    *prms->state = MOVING;
  }
}

void attach(Params_t *prms) {
  if (store_piece(prms)) {
    delete_possible_lines(prms);
    *prms->state = SPAWN;
  } else {
    *prms->state = GAMEOVER;
  }
}

void gameover(Params_t *prms) { prms->game_info->pause = 4; }
void exitstate(Params_t *prms) { *prms->state = EXIT_STATE; }

void pause(Params_t *prms) { prms->game_info->pause = 2; }

void rotate(Params_t *prms) {
  prms->current_figure->rotation = (prms->current_figure->rotation + 1) % 4;
  if (!check_collision(*prms->current_figure))
    prms->current_figure->rotation = (prms->current_figure->rotation + 3) % 4;
  *prms->state = MOVING;
}
