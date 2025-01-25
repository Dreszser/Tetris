#include "frontend.h"

void window_init() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);

  print_rectangle(SPACE, SPACE, HEIGHT, GAME_W);
  print_rectangle(SPACE, WIDTH - INDICATORS_W, HEIGHT, INDICATORS_W);
  print_rectangle(WIN_SPACE, WIDTH - WIN_W + 6 * SPACE, WIN_NEXT_H, WIN_W);

  mvprintw(WIN_SPACE + 1, WIDTH - WIN_W + 6 * SPACE + 1, "next:");
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
void print_starting_message(WINDOW *message) {
  mvwprintw(message, 0, 1, "start: ENTER");
  mvwprintw(message, 1, 1, " quit: ESCAPE");
}

void print_pause_message(WINDOW *message) {
  mvwprintw(message, 0, 1, "Game is paused");
  mvwprintw(message, 1, 1, "Continue: P");
}

void print_game_over_message(WINDOW *message) {
  mvwprintw(message, 0, 1, "Game over!");
  mvwprintw(message, 1, 1, "Restart: ENTER");
}

void print_stats(WINDOW *next, WINDOW *score, GameInfo_t game) {
  werase(next);
  for (int i = 0; i < 5 && game.next; ++i) {
    int tmp = 0;
    for (int j = 0; j < 5; ++j) {
      if (game.next[i][j] == 1 || game.next[i][j] == 2) {
        mvwaddch(next, i, j + tmp++, ' ' | A_REVERSE);
        mvwaddch(next, i, j + tmp, ' ' | A_REVERSE);
      } else {
        tmp++;
      }
    }
  }
  werase(score);
  box(score, 0, 0);
  mvwprintw(score, 1, 1, "score: %d", game.score);
  mvwprintw(score, 4, 1, "best:  %d", game.high_score);
  mvwprintw(score, 7, 1, "level: %d", game.level);
  mvwprintw(score, 10, 1, "speed: %d", game.speed);
}

void print_field(WINDOW *board, GameInfo_t game) {
  werase(board);
  for (int i = 0; i < 20; ++i) {
    int tmp = 0;
    for (int j = 0; j < 10; ++j) {
      if (game.field[i][j] == 1) {
        mvwaddch(board, i, j + tmp++, ACS_CKBOARD);
        mvwaddch(board, i, j + tmp, ACS_CKBOARD);
      } else if (game.field[i][j] == 2) {
        mvwaddch(board, i, j + tmp++, ' ' | A_REVERSE);
        mvwaddch(board, i, j + tmp, ' ' | A_REVERSE);
      } else if (game.field[i][j] == 3) {
        mvwaddch(board, i, j + tmp++, '[');
        mvwaddch(board, i, j + tmp, ']');
      } else {
        mvwaddch(board, i, j + tmp++, ' ');
        mvwaddch(board, i, j + tmp, ' ');
      }
    }
  }
}

void print_game(WINDOW *board, WINDOW *next, WINDOW *score, WINDOW *message) {
  refresh();
  GameInfo_t game = updateCurrentState();
  switch (game.pause) {
    case 1:
      print_start(message);
      break;
    case 2:
      print_pause(message);
      break;
    case 4:
      print_game_over(message);
      break;
    default:
      werase(message);
      print_stats(next, score, game);
      print_field(board, game);
      break;
  }
  wrefresh(board);
  wrefresh(next);
  wrefresh(score);
}

void print_start(WINDOW *message) {
  print_starting_message(message);
  wrefresh(message);
}

void print_pause(WINDOW *message) {
  print_pause_message(message);
  wrefresh(message);
}

void print_game_over(WINDOW *message) {
  print_game_over_message(message);
  wrefresh(message);
}

// Get user input
bool get_action(UserAction_t *key) {
  bool input = true;
  int ch = getch();
  switch (ch) {
    case KEY_UP:
      *key = Up;
      break;
    case KEY_DOWN:
      *key = Down;
      break;
    case KEY_LEFT:
      *key = Left;
      break;
    case KEY_RIGHT:
      *key = Right;
      break;
    case ESCAPE:
      *key = Terminate;
      break;
    case ENTER_KEY:
      *key = Start;
      break;
    case ' ':
      *key = Action;
      break;
    case 'p':
    case 'P':
      *key = Pause;
      break;
    default:
      input = false;
      break;
  }

  return input;
}
