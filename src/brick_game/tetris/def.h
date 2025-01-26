#ifndef DEF_H_
#define DEF_H_

#include "lib_specification.h"

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACH,
  GAMEOVER,
  EXIT_STATE
} BrickState_t;

typedef struct {
  int block_type;
  int rotation;
  /* Actual coordinates of a piece on the screen */
  int vertical_coords;
  int horizontal_coords;
} BrickInfo_t;

typedef struct {
  GameInfo_t *game_info;
  BrickState_t *state;
  BrickInfo_t *current_figure;
  BrickInfo_t *next_figure;
} Params_t;

typedef void (*signals)(Params_t *prms);

#endif  // DEF_H_