#ifndef BACKEND_H_
#define BACKEND_H_

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "def.h"

#define SPAWN_PIXEL 12

void initialize_game(Params_t *parameters);
void init_field(GameInfo_t *game);
void init_piece(Params_t *prms);
void init_next_piece(Params_t *prms);
void transfer_next_piece();

void clear_field(Params_t *prms);

void free_next(GameInfo_t *game);
void free_field(GameInfo_t *game);

Params_t get_params();

void down_shift();

bool check_collision(BrickInfo_t piece);
bool check_borders_collision(int x, int y);
bool check_field_collision(int x, int y);

int get_random_number(int a, int b);

void copy_matrix(int **original_matrix, int **new_matrix, int rows, int cols);
void free_resources(Params_t *parameters);

int get_lowest_position(Params_t *prms);

void get_high_score(Params_t *prms);
void save_high_score(Params_t *prms);
void reinitialize_game(Params_t *prms);

#endif  // BACKEND_H_