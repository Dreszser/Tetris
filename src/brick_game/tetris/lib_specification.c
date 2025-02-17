// #include "lib_specification.h"

/**
 * @file lib_specification.c
 *
 * @brief Implementation of functions from specification.
 */

#include "backend.h"
#include "fsm.h"
#include "pieces.h"

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
  int projection_coords = 0;
  if (parameters.current_figure->block_type != -1)
    projection_coords = get_lowest_position(&parameters);
  for (int i = 0; i < 5 && parameters.current_figure->block_type != -1; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (get_block_type(parameters.current_figure->block_type,
                         parameters.current_figure->rotation, i, j)) {
        int y = i + parameters.current_figure->vertical_coords - 2;
        int y_projection = i + projection_coords - 2;
        int x = (j * 2 + parameters.current_figure->horizontal_coords - 2) / 2;
        if (y_projection >= 0 && game_to_print.field[y_projection][x] != 1)
          game_to_print.field[y_projection][x] = 3;
        if (y >= 0) game_to_print.field[y][x] = 2;
      }
    }
  }
  return game_to_print;
}
