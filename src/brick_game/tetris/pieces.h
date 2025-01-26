#ifndef PIECES_H_
#define PIECES_H_

int get_block_type(int piece, int rotation, int vertical_coords,
                   int horizontal_coords);
int get_x_displacement(int piece, int rotation);

int get_block_type_square(int vertical_coords, int horizontal_coords);
int get_block_type_I(int rotation, int vertical_coords, int horizontal_coords);
int get_block_type_L(int rotation, int vertical_coords, int horizontal_coords);
int get_block_type_L_mirrorred(int rotation, int vertical_coords,
                               int horizontal_coords);
int get_block_type_N(int rotation, int vertical_coords, int horizontal_coords);
int get_block_type_N_mirrorred(int rotation, int vertical_coords,
                               int horizontal_coords);
int get_block_type_T(int rotation, int vertical_coords, int horizontal_coords);

#endif  // PIECES_H_