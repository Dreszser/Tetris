#include "backend.h"

#include <stdio.h>

#include "pieces.h"

// Initialize game field
void init_field(GameInfo_t *game) {
  game->field = (int **)calloc(20, sizeof(int *));
  for (int i = 0; i < 20; ++i) {
    game->field[i] = (int *)calloc(10, sizeof(int));
  }
}

void clear_field(Params_t *prms) {
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 10; ++j) {
      prms->game_info->field[i][j] = 0;
    }
  }
}

// Free memory allocated for field
void free_field(GameInfo_t *game) {
  for (int i = 0; i < 20; ++i) {
    free(game->field[i]);
  }
  free(game->field);
}

// Initialize current piece
void init_piece(Params_t *prms) {
  prms->current_figure->block_type = get_random_number(0, 6);
  prms->current_figure->rotation = get_random_number(0, 3);
  prms->current_figure->vertical_coords = 0;
  prms->current_figure->horizontal_coords =
      SPAWN_PIXEL + (get_x_displacement(prms->current_figure->block_type,
                                        prms->current_figure->rotation) *
                     2);
}

// Initialize next piece
void init_next_piece(Params_t *prms) {
  if (prms->game_info->next) free_next(prms->game_info);
  prms->next_figure->block_type = get_random_number(0, 6);
  prms->next_figure->rotation = get_random_number(0, 3);
  prms->next_figure->vertical_coords = 0;
  prms->next_figure->horizontal_coords =
      SPAWN_PIXEL + (get_x_displacement(prms->next_figure->block_type,
                                        prms->next_figure->rotation) *
                     2);
  prms->game_info->next = (int **)calloc(5, sizeof(int *));
  for (int i = 0; i < 5; ++i) {
    prms->game_info->next[i] = (int *)calloc(5, sizeof(int));
    for (int j = 0; j < 5; ++j) {
      prms->game_info->next[i][j] = get_block_type(
          prms->next_figure->block_type, prms->next_figure->rotation, i, j);
    }
  }
}

// Initialize all valuable information for new game
void initialize_game(Params_t *parameters) {
#if defined(__linux__)
  srand((unsigned int)time(NULL));
#else
  srandom((unsigned int)time(NULL));
#endif
  init_field(parameters->game_info);
  init_next_piece(parameters);
}

// transfer next piece to current
void transfer_next_piece() {
  Params_t params = get_params();
  params.current_figure->block_type = params.next_figure->block_type;
  params.current_figure->rotation = params.next_figure->rotation;
  params.current_figure->horizontal_coords =
      params.next_figure->horizontal_coords;
  params.current_figure->vertical_coords = params.next_figure->vertical_coords;
}

// Free memory allocated for next piece
void free_next(GameInfo_t *game) {
  for (int i = 0; i < 5; ++i) {
    free(game->next[i]);
  }
  free(game->next);
}

Params_t get_params() {
  static GameInfo_t ginfo = {NULL, NULL, 0, 0, 0, 0, 1};
  static BrickState_t state = {START};
  static BrickInfo_t current = {-1, 0, 0, 0};
  static BrickInfo_t next = {-1, 0, 0, 0};
  static Params_t prms;
  prms.current_figure = &current;
  prms.next_figure = &next;
  prms.game_info = &ginfo;
  prms.state = &state;

  return prms;
}

void reinitialize_game(Params_t *prms) {
  init_next_piece(prms);
  clear_field(prms);
  get_high_score(prms);
  prms->game_info->level = 0;
  prms->game_info->score = 0;
  prms->game_info->speed = 0;
}

void down_shift() {
  Params_t prms = get_params();
  *prms.state = SHIFTING;
  userInput(0, false);
}

// returns true if no collision is detected
bool check_collision(BrickInfo_t piece) {
  bool result = 1;
  for (int i = 0; i < 5 && result; ++i) {
    for (int j = 0; j < 5 && result; ++j) {
      if (get_block_type(piece.block_type, piece.rotation, i, j)) {
        if (!check_borders_collision(i + piece.vertical_coords,
                                     j * 2 + piece.horizontal_coords) ||
            !check_field_collision(i + piece.vertical_coords,
                                   j * 2 + piece.horizontal_coords)) {
          result = 0;
        }
      }
    }
  }
  return result;
}

// Checks for positioning a piece inside playing field
// returns true if no collision is detected
bool check_borders_collision(int y, int x) {
  return (y < 22 && x > 1 && x < 22);
}

// Checks for collision with blocks already on the field
bool check_field_collision(int y, int x) {
  Params_t params = get_params();
  bool result = 1;
  if ((y - 2) >= 0) result = (params.game_info->field[y - 2][(x - 2) / 2] == 0);
  return result;
}

// Get random number between a and b
int get_random_number(int a, int b) {
#if defined(__linux__)
  return rand() % (b - a + 1) + a;
#else
  return random() % (b - a + 1) + a;
#endif
}

void free_resources(Params_t *parameters) {
  GameInfo_t game = updateCurrentState();
  if (parameters->game_info->field) free_field(parameters->game_info);
  if (parameters->game_info->next) free_next(parameters->game_info);
  if (game.field) free_field(&game);
  if (game.next) free_next(&game);
}

void copy_matrix(int **original_matrix, int **new_matrix, int rows, int cols) {
  for (int i = 0; i < rows && original_matrix && new_matrix; ++i) {
    for (int j = 0; j < cols; ++j) {
      new_matrix[i][j] = original_matrix[i][j];
    }
  }
}

int get_lowest_position(Params_t *prms) {
  int temp = prms->current_figure->vertical_coords;
  while (check_collision(*prms->current_figure)) {
    prms->current_figure->vertical_coords += 1;
  }
  if (prms->current_figure->vertical_coords != temp)
    prms->current_figure->vertical_coords -= 1;
  int result = prms->current_figure->vertical_coords;
  prms->current_figure->vertical_coords = temp;
  return result;
}

void get_high_score(Params_t *prms) {
  FILE *high_score_f = fopen("/tmp/.s21", "r");
  if (high_score_f) {
    int high_score = 0;
    if (fscanf(high_score_f, "%d", &high_score)) {
      prms->game_info->high_score = high_score;
    }
    fclose(high_score_f);
  }
}

void save_high_score(Params_t *prms) {
  FILE *high_score_f = fopen("/tmp/.s21", "w");
  if (high_score_f) {
    fprintf(high_score_f, "%d", prms->game_info->score);
    fclose(high_score_f);
  }
}
