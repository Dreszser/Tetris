#include "pieces.h"

int get_x_displacement(int piece, int rotation) {
  int pieces_displacement[7 /*kind */][4 /* rotation */] = {
      /* Square */
      {-3, -3, -3, -3},
      /* I */
      {-3, -2, -2, -2},
      /* L */
      {-3, -2, -2, -2},
      /* L mirrored */
      {-2, -2, -3, -2},
      /* N */
      {-3, -2, -2, -2},
      /* N mirrored */
      {-3, -2, -2, -2},
      /* T */
      {-3, -2, -2, -2},
  };
  return pieces_displacement[piece][rotation];
}

int get_block_type_square(int vertical_coords, int horizontal_coords) {
  int piece[5 /* horizontal blocks */][5 /* vertical blocks */] = {
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}};

  return piece[vertical_coords][horizontal_coords];
}

int get_block_type_I(int rotation, int vertical_coords, int horizontal_coords) {
  int piece[4 /* rotation */][5 /* horizontal blocks */]
           [5 /* vertical blocks */] = {{{0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 1, 1, 1},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {1, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 0, 0, 0}}};
  return piece[rotation][vertical_coords][horizontal_coords];
}

int get_block_type_L(int rotation, int vertical_coords, int horizontal_coords) {
  int piece[4 /* rotation */][5 /* horizontal blocks */]
           [5 /* vertical blocks */] = {{{0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 1, 0, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 0, 1, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0}}};
  return piece[rotation][vertical_coords][horizontal_coords];
}

int get_block_type_L_mirrorred(int rotation, int vertical_coords,
                               int horizontal_coords) {
  int piece[4 /* rotation */][5 /* horizontal blocks */]
           [5 /* vertical blocks */] = {{{0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 1, 0, 0, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 1, 0},
                                         {0, 0, 0, 0, 0}}};
  return piece[rotation][vertical_coords][horizontal_coords];
}

int get_block_type_N(int rotation, int vertical_coords, int horizontal_coords) {
  int piece[4 /* rotation */][5 /* horizontal blocks */]
           [5 /* vertical blocks */] = {{{0, 0, 0, 0, 0},
                                         {0, 0, 0, 1, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 1, 0, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0}}};
  return piece[rotation][vertical_coords][horizontal_coords];
}

int get_block_type_N_mirrorred(int rotation, int vertical_coords,
                               int horizontal_coords) {
  int piece[4 /* rotation */][5 /* horizontal blocks */]
           [5 /* vertical blocks */] = {{{0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 0, 0, 1, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 1, 0, 0, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0}}};
  return piece[rotation][vertical_coords][horizontal_coords];
}

int get_block_type_T(int rotation, int vertical_coords, int horizontal_coords) {
  int piece[4 /* rotation */][5 /* horizontal blocks */]
           [5 /* vertical blocks */] = {{{0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 0, 0, 0}},
                                        {{0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0}}};
  return piece[rotation][vertical_coords][horizontal_coords];
}

int get_block_type(int piece, int rotation, int vertical_coords,
                   int horizontal_coords) {
  int result = 0;
  switch (piece) {
    case 0:
      result = get_block_type_square(vertical_coords, horizontal_coords);
      break;
    case 1:
      result = get_block_type_I(rotation, vertical_coords, horizontal_coords);
      break;
    case 2:
      result = get_block_type_L(rotation, vertical_coords, horizontal_coords);
      break;
    case 3:
      result = get_block_type_L_mirrorred(rotation, vertical_coords,
                                          horizontal_coords);
      break;
    case 4:
      result = get_block_type_N(rotation, vertical_coords, horizontal_coords);
      break;
    case 5:
      result = get_block_type_N_mirrorred(rotation, vertical_coords,
                                          horizontal_coords);
      break;
    case 6:
      result = get_block_type_T(rotation, vertical_coords, horizontal_coords);
      break;
  }
  return result;
}
