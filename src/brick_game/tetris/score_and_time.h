#ifndef SCORE_AND_TIME_H_
#define SCORE_AND_TIME_H_

#define _POSIX_C_SOURCE 200809L

#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "def.h"

bool store_piece(Params_t *prms);
void delete_possible_lines(Params_t *prms);
void clear_line(Params_t *prms, int v_coord);
int get_score(int lines);
void update_level(Params_t *prms);

unsigned calculate_tick_interval();
unsigned long get_current_time_in_ms();

#endif  // SCORE_AND_TIME_H_