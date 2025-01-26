#include "score_and_time.h"

#include "backend.h"
#include "pieces.h"

bool store_piece(Params_t *prms) {
  bool success = 1;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      int y = prms->current_figure->vertical_coords;
      int x = prms->current_figure->horizontal_coords;
      if (get_block_type(prms->current_figure->block_type,
                         prms->current_figure->rotation, i, j)) {
        if (i + y - 2 < 0) {  // trying to store a piece higher than top border
          success = 0;
        } else {
          prms->game_info->field[i + y - 2][(j * 2 + x - 2) / 2] = 1;
        }
      }
    }
  }
  return success;
}

void delete_possible_lines(Params_t *prms) {
  int block_count = 0;
  int lines_count = 0;
  for (int i = 19; i >= 0; --i) {
    for (int j = 0; j < 10; ++j) {
      if (prms->game_info->field[i][j] == 1) {
        ++block_count;
      }
    }
    if (block_count == 10) {
      ++lines_count;
      clear_line(prms, i++);
    }
    block_count = 0;
  }
  prms->game_info->score += get_score(lines_count);
  update_level(prms);
  prms->game_info->speed = prms->game_info->level;
}

void update_level(Params_t *prms) {
  int new_level = prms->game_info->score / 600;
  if (new_level > prms->game_info->level && new_level < 11) {
    prms->game_info->level = new_level;
  }
}

int get_score(int lines) {
  int result = 0;
  switch (lines) {
    case 1:
      result = 100;
      break;
    case 2:
      result = 300;
      break;
      ;
    case 3:
      result = 700;
      break;
    case 4:
      result = 1500;
      break;
  }
  return result;
}

void clear_line(Params_t *prms, int v_coord) {
  for (int i = v_coord; i >= 0; --i) {
    for (int j = 0; j < 10; ++j) {
      if (i == 0) {
        prms->game_info->field[i][j] = 0;
      } else {
        prms->game_info->field[i][j] = prms->game_info->field[i - 1][j];
      }
    }
  }
}

unsigned calculate_tick_interval() {
  GameInfo_t game = *(get_params().game_info);
  return (unsigned)(1000 * pow(0.8, game.level));
}

unsigned long get_current_time_in_ms() {
  struct timespec spec;
  clock_gettime(CLOCK_MONOTONIC, &spec);
  return spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
}
