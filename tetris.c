#include "tetris.h"

int main(void) {
  window_init();
  game_loop();
  endwin();
  return 0;
}

void game_loop() {
  Params_t parameters = get_params();
  initialize_game(&parameters);
  WINDOW *win_board, *win_next, *win_score, *win_message;  // game windows
  win_board = newwin(20, 20, 2, 2);
  win_next = newwin(5, 10, 4, 31);
  win_score = newwin(12, 18, 10, 26);
  win_message = newwin(2, 16, 11, 4);

  unsigned long last_tick = get_current_time_in_ms();

  // TODO: implement hold variable
  bool hold = false;

  while (*parameters.state != EXIT_STATE) {
    unsigned long current_time = get_current_time_in_ms();
    unsigned long elapsed_time = current_time - last_tick;

    if (elapsed_time >= calculate_tick_interval()) {
      down_shift();
      last_tick = current_time;
    }
    UserAction_t key = (parameters.game_info->pause ? 7 : 0);
    get_action(&key);
    userInput(key, hold);
    print_game(win_board, win_next, win_score, win_message);
    // update timer if game was paused, or user presses down button
    if (key == Down || parameters.game_info->pause)
      last_tick = get_current_time_in_ms();
    napms(20);
  }
  delwin(win_board);
  delwin(win_score);
  delwin(win_next);
  delwin(win_message);
  free_resources(&parameters);
}