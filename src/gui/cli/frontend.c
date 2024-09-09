#include "frontend.h"

void window_init(int time) {
  initscr();
  noecho();
  curs_set(0);
  setlocale(LC_ALL, "");
  //   timeout(time);
  (void)time;

  print_rectangle(SPACE, SPACE, HEIGHT, GAME_W);
  print_rectangle(SPACE, WIDTH - INDICATORS_W, HEIGHT, INDICATORS_W);

  print_rectangle(WIN_SPACE, WIDTH - WIN_W + 6 * SPACE, WIN_NEXT_H, WIN_W);
  print_rectangle(WIN_SPACE + WIN_NEXT_INTERVAL, WIDTH - WIN_W + 6 * SPACE,
                  WIN_I_H, WIN_W);
  print_rectangle(WIN_SPACE + WIN_NEXT_INTERVAL + WIN_INTERVAL,
                  WIDTH - WIN_W + 6 * SPACE, WIN_I_H, WIN_W);
  print_rectangle(WIN_SPACE + WIN_NEXT_INTERVAL + 2 * WIN_INTERVAL,
                  WIDTH - WIN_W + 6 * SPACE, WIN_I_H, WIN_W);
  print_rectangle(WIN_SPACE + WIN_NEXT_INTERVAL + 3 * WIN_INTERVAL,
                  WIDTH - WIN_W + 6 * SPACE, WIN_I_H, WIN_W);

  mvprintw(WIN_SPACE + 1, WIDTH - WIN_W + 6 * SPACE + 1, "qwe");
  mvprintw(WIN_SPACE + WIN_NEXT_INTERVAL + 1, WIDTH - WIN_W + 6 * SPACE + 1,
           "qwe");
  mvprintw(WIN_SPACE + WIN_NEXT_INTERVAL + WIN_INTERVAL + 1,
           WIDTH - WIN_W + 6 * SPACE + 1, "qwe");
  mvprintw(WIN_SPACE + WIN_NEXT_INTERVAL + 2 * WIN_INTERVAL + 1,
           WIDTH - WIN_W + 6 * SPACE + 1, "qwe");
  mvprintw(WIN_SPACE + WIN_NEXT_INTERVAL + 3 * WIN_INTERVAL + 1,
           WIDTH - WIN_W + 6 * SPACE + 1, "qwe");

}

void print_rectangle(int x_begin, int y_begin, int x, int y) {
  for (int i = x_begin + 1; i < (x + x_begin); i++) {
    mvaddch(i, y_begin, ACS_VLINE);
    mvaddch(i, (y + y_begin - 1), ACS_VLINE);
  }

  for (int i = y_begin + 1; i < (y + y_begin); i++) {
    mvaddch(x_begin, i, ACS_HLINE);
    mvaddch((x + x_begin - 1), i, ACS_HLINE);
  }

  mvaddch(x_begin, y_begin, ACS_ULCORNER);
  mvaddch(x_begin, y + y_begin - 1, ACS_URCORNER);
  mvaddch(x + x_begin - 1, y_begin, ACS_LLCORNER);
  mvaddch(x + x_begin - 1, y + y_begin - 1, ACS_LRCORNER);
}
