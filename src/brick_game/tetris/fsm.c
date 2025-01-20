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
  act = fsm_table[*parameters.state][action];
  if (parameters.game_info->pause && action == Terminate) {
    exitstate(&parameters);
  } else if ((parameters.game_info->pause == 1 ||
              parameters.game_info->pause == 4) &&
             action == Start) {
    if (parameters.game_info->pause == 4) *parameters.state = START;
    parameters.game_info->pause = 0;
  } else if (parameters.game_info->pause && action == Pause) {
    parameters.game_info->pause = 0;
  } else if (!parameters.game_info->pause && act) {
    act(&parameters);
  }
}

// Gathers all valuable resources for printint the game screen, creates and
// returns a static copy of GameInfo_t struct where field has both filled blocks
// and a falling piece
GameInfo_t updateCurrentState() {
  Params_t parameters = get_params();
  static GameInfo_t game_to_print = {0};
  if (game_to_print.field == NULL) {
    init_field(&game_to_print);
  }
  if (game_to_print.next == NULL) {
    game_to_print.next = (int **)calloc(5, sizeof(int *));
    for (int i = 0; i < 5; ++i) {
      game_to_print.next[i] = (int *)calloc(5, sizeof(int));
    }
  }
  copy_matrix(parameters.game_info->field, game_to_print.field, 20, 10);
  copy_matrix(parameters.game_info->next, game_to_print.next, 5, 5);
  game_to_print.high_score = parameters.game_info->high_score;
  game_to_print.level = parameters.game_info->level;
  game_to_print.pause = parameters.game_info->pause;
  game_to_print.score = parameters.game_info->score;
  game_to_print.speed = parameters.game_info->speed;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (get_block_type(parameters.current_figure->block_type,
                         parameters.current_figure->rotation, i, j) &&
          i + parameters.current_figure->vertical_coords - 2 >= 0) {
        int y = i + parameters.current_figure->vertical_coords - 2;
        int x = (j * 2 + parameters.current_figure->horizontal_coords - 2) / 2;
        game_to_print.field[y][x] = 2;
      }
    }
  }
  return game_to_print;
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
