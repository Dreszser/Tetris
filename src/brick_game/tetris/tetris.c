#include "frontend.h"
#include "fsm.h"

int main(void) {
  window_init(50);
  game_loop();
  endwin();
  return 0;
}

void game_loop() {
  Params_t parameters = get_params();
  bool break_flag = true;
  UserAction_t key = 0;
  bool hold = false;
  while (break_flag) {
    if (*parameters.state == GAMEOVER || *parameters.state == EXIT_STATE)
      break_flag = false;
    userInput(key, hold);
    if (*parameters.state == MOVING || *parameters.state == START)
      key = get_action();
  }
}