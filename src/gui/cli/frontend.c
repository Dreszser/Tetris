#include "frontend.h"

#include "pieces.h"

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

void print_stats(WINDOW *next, WINDOW *score) {
  Params_t params = get_params();
  werase(next);
  for (int i = 0; i < 5 && params.current_figure->block_type != -1; ++i) {
    int tmp = 0;
    for (int j = 0; j < 5; ++j) {
      if (params.game_info->next[i][j] == 1 ||
          params.game_info->next[i][j] == 2) {
        mvwaddch(next, i, j + tmp++, ' ' | A_REVERSE);
        mvwaddch(next, i, j + tmp, ' ' | A_REVERSE);
      } else {
        tmp++;
      }
    }
  }
  werase(score);
  box(score, 0, 0);
  mvwprintw(score, 1, 1, "score: %d", params.game_info->score);
  mvwprintw(score, 4, 1, "best:  %d", params.game_info->high_score);
  mvwprintw(score, 7, 1, "level: %d", params.game_info->level);
  mvwprintw(score, 10, 1, "speed: %d", params.game_info->speed);

  // TODO: information for debugging, need to remove later
  // mvprintw(26, 2, "               ");
  /* switch (*params.state) {
    case 0:
      mvprintw(26, 2, "start");
      break;
    case 1:
      mvprintw(26, 2, "spawn");
      break;
    case 2:
      mvprintw(26, 2, "moving");
      break;
    case 3:
      mvprintw(26, 2, "shifting");
      break;
    case 4:
      mvprintw(26, 2, "attach");
      break;
    case 5:
      mvprintw(26, 2, "gameover");
      break;
    case 6:
      mvprintw(26, 2, "exit");
      break;
  } */

  // mvprintw(27, 2, "%d", params.current_figure->rotation);
  // mvprintw(28, 2, "%d", params.current_figure->block_type);
}

void print_field(WINDOW *board) {
  GameInfo_t ginfo = updateCurrentState();
  werase(board);
  for (int i = 0; i < 20; ++i) {
    int tmp = 0;
    for (int j = 0; j < 10; ++j) {
      if (ginfo.field[i][j] == 1) {
        mvwaddch(board, i, j + tmp++, ACS_CKBOARD /* ' ' | A_REVERSE */);
        mvwaddch(board, i, j + tmp, ACS_CKBOARD /* ' ' | A_REVERSE */);
      } else {
        mvwaddch(board, i, j + tmp++, ' ');
        mvwaddch(board, i, j + tmp, ' ');
      }
    }
  }
}

void print_piece(WINDOW *board) {
  Params_t params = get_params();
  for (int i = 0; i < 5 && params.current_figure->block_type != -1; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (get_block_type(params.current_figure->block_type,
                         params.current_figure->rotation, i, j) == 1) {
        mvwaddch(board, i + params.current_figure->vertical_coords - 2,
                 j * 2 + params.current_figure->horizontal_coords - 2,
                 ' ' | A_REVERSE);
        mvwaddch(board, i + params.current_figure->vertical_coords - 2,
                 j * 2 + params.current_figure->horizontal_coords - 1,
                 ' ' | A_REVERSE);
      }
    }
  }
}

void print_game(WINDOW *board, WINDOW *next, WINDOW *score, WINDOW *message) {
  refresh();
  GameInfo_t game = updateCurrentState();
  switch (game.pause) {
    case 2:
      print_pause(message);
      break;
    case 4:
      print_game_over(message);
    default:
      print_stats(next, score);
      print_field(board);
      print_piece(board);
      break;
  }
  wrefresh(board);
  wrefresh(next);
  wrefresh(score);
}

void print_start(WINDOW *message) {
  Params_t prms = get_params();
  while (prms.game_info->pause == 1) {
    print_starting_message(message);
    wrefresh(message);
    UserAction_t key = 7;
    get_action(&key);
    switch (key) {
      case Start:
        prms.game_info->pause = 0;
        break;
      case Terminate:
        prms.game_info->pause = 3;
        break;
      default:
        break;
    }
    napms(20);
  }
  werase(message);
}

void print_pause(WINDOW *message) {
  Params_t prms = get_params();
  while (prms.game_info->pause == 2) {
    print_pause_message(message);
    wrefresh(message);
    UserAction_t key = 7;
    get_action(&key);
    switch (key) {
      case Pause:
        prms.game_info->pause = 0;
        break;
      case Terminate:
        prms.game_info->pause = 3;
        break;
      default:
        break;
    }
    napms(20);
  }
  werase(message);
}

void print_game_over(WINDOW *message) {
  Params_t prms = get_params();
  while (prms.game_info->pause == 4) {
    print_game_over_message(message);
    wrefresh(message);
    UserAction_t key = 7;
    get_action(&key);
    switch (key) {
      case Start:  // restart the game if user presses ENTER
        *prms.state = START;
        prms.game_info->pause = 0;
        break;
      case Terminate:
        prms.game_info->pause = 3;
        break;
      default:
        break;
    }
    napms(20);
  }
  werase(message);
}

// Get user input
bool get_action(UserAction_t *key) {
  bool input = false;
  int ch = getch();
  switch (ch) {
    case KEY_UP:
      *key = Up;
      input = true;
      break;
    case KEY_DOWN:
      *key = Down;
      input = true;
      break;
    case KEY_LEFT:
      *key = Left;
      input = true;
      break;
    case KEY_RIGHT:
      *key = Right;
      input = true;
      break;
    case ESCAPE:
      *key = Terminate;
      input = true;
      break;
    case ENTER_KEY:
      *key = Start;
      input = true;
      break;
    case ' ':
      *key = Action;
      input = true;
      break;
    case 'p':
    case 'P':
      *key = Pause;
      input = true;
      break;
    default:
      break;
  }

  return input;
}
