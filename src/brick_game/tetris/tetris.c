#include "frontend.h"
#include "fsm.h"

int main(void) {
  window_init();
  game_loop();
  endwin();
  return 0;
}

void game_loop() {
  Params_t parameters = get_params();
  init_field(&parameters);
  init_piece(&parameters);
  bool break_flag = true;
  UserAction_t key = get_action();
  bool hold = false;
  while (break_flag) {
    if (*parameters.state == GAMEOVER || *parameters.state == EXIT_STATE)
      break_flag = false;
    userInput(key, hold);
    updateCurrentState();
    if (*parameters.state == MOVING || *parameters.state == START)
      key = get_action();
    // napms(100);
    
    /* else {
      parameters = get_params();
      shifting(&parameters);
    } */
    refresh();
  }
  free(*parameters.brick_pos->piece);
  free(parameters.brick_pos->piece);
  free(*parameters.game_info->field);
  free(parameters.game_info->field);
}
