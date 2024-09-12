#include "frontend.h"

void window_init() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, FALSE);
  curs_set(0);
  keypad(stdscr, TRUE);

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

  print_starting_message();
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
void print_starting_message() {
  mvprintw(HEIGHT / 2, GAME_W / 2 - 6, "Start: ENTER");
  mvprintw(HEIGHT / 2 + 1, GAME_W / 2 - 6, " Quit: ESCAPE");
}

void clear_field() {
  for (int i = 0; i < HEIGHT - 2; ++i) {
    mvprintw(i + WIN_SPACE, WIN_SPACE, "                    ");
  }
}

void print_stats(GameInfo_t ginfo) {
  mvprintw(WIN_SPACE + 1, WIDTH - WIN_W + 6 * SPACE + 5, "next");
  mvprintw(WIN_SPACE + WIN_NEXT_INTERVAL + 1, WIDTH - WIN_W + 6 * SPACE + 5,
           "%d", ginfo.score);
  mvprintw(WIN_SPACE + WIN_NEXT_INTERVAL + WIN_INTERVAL + 1,
           WIDTH - WIN_W + 6 * SPACE + 5, "%d", ginfo.high_score);
  mvprintw(WIN_SPACE + WIN_NEXT_INTERVAL + 2 * WIN_INTERVAL + 1,
           WIDTH - WIN_W + 6 * SPACE + 5, "%d", ginfo.level);
  mvprintw(WIN_SPACE + WIN_NEXT_INTERVAL + 3 * WIN_INTERVAL + 1,
           WIDTH - WIN_W + 6 * SPACE + 5, "%d", ginfo.speed);
}
void print_field(GameInfo_t ginfo) {
  for (int i = 2; i < HEIGHT; ++i) {
    int tmp = 0;
    for (int j = 2; j < 12; ++j) {
      if (ginfo.field[i - 2][j - 2] == 1) {
        mvaddch(i, j + tmp++, ' ' | A_REVERSE);
        mvaddch(i, j + tmp, ' ' | A_REVERSE);
      } else {
        mvaddch(i, j + tmp++, ' ');
        mvaddch(i, j + tmp, ' ');
      }
    }
  }
}
void print_piece(PlayerPos_t pos) {
  for (int i = 0; i < 1; ++i) {
    int tmp = 0;
    for (int j = 0; j < 1; ++j) {
      if (pos.piece[i][j] == 1) {
        mvaddch(i + pos.x, j + pos.y + tmp++, ' ' | A_REVERSE);
        mvaddch(i + pos.x, j + pos.y + tmp, ' ' | A_REVERSE);
      } else {
        mvaddch(i + pos.x, j + pos.y + tmp++, ' ');
        mvaddch(i + pos.x, j + pos.y + tmp, ' ');
      }
    }
  }
}