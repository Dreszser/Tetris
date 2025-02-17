#include "fsm.h"

/**
 * @file fsm.c
 *
 * @brief Implementation of functions that change the state of FSM.
 */

#include "backend.h"
#include "pieces.h"
#include "score_and_time.h"

void start(Params_t *prms) {
  reinitialize_game(prms);
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
  prms->current_figure->vertical_coords = get_lowest_position(prms);
  *prms->state = ATTACH;
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

void gameover(Params_t *prms) {
  if (prms->game_info->score > prms->game_info->high_score) {
    save_high_score(prms);
  }
  prms->game_info->pause = 4;
}
void exitstate(Params_t *prms) { *prms->state = EXIT_STATE; }

void pause(Params_t *prms) { prms->game_info->pause = 2; }

void rotate(Params_t *prms) {
  prms->current_figure->rotation = (prms->current_figure->rotation + 1) % 4;
  if (!check_collision(*prms->current_figure))
    prms->current_figure->rotation = (prms->current_figure->rotation + 3) % 4;
  *prms->state = MOVING;
}
