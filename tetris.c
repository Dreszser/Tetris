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
  WINDOW *w_board, *w_next, *w_score, *w_message;  // game windows
  w_board = newwin(20, 20, 2, 2);
  w_next = newwin(5, 10, 4, 31);
  w_score = newwin(12, 18, 10, 26);
  w_message = newwin(2, 16, 11, 4);
  print_start(w_message);

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
    UserAction_t key = 0;
    get_action(&key);
    userInput(key, hold);
    print_game(w_board, w_next, w_score, w_message);
    // update timer if game was paused, or user presses down button
    if (key == Down || key == Pause || *get_params().state == START)
      last_tick = get_current_time_in_ms();
    napms(20);
  }
  delwin(w_board);
  delwin(w_score);
  delwin(w_next);
  delwin(w_message);
  free_field(&parameters);
  free_next(&parameters);
}