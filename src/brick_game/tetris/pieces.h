#ifndef PIECES_H_
#define PIECES_H_

/**
 * @file pieces.h
 *
 * @brief Declaration of functions that help to initialize tetrominoes.
 *
 * Tetrominoes are hard-coded 5x5 matrices, to initialize one I use
 * get_block_type function, that has access to these hard-coded matrices.
 */

/**
 * @brief Get block type according to type of tetrominoe, its rotation and
 * actual coordinates of the block in 5x5 matrix.
 *
 * @return 1 if block is filled, 0 if block is empty.
 */
int get_block_type(int piece, int rotation, int vertical_coords,
                   int horizontal_coords);

/**
 * @brief Get starting horizontal displacement for the piece.
 *
 * @return Horizontal displacement.
 */
int get_x_displacement(int piece, int rotation);

/**
 * @brief Get block type for square piece.
 *
 * @return 1 if block is filled, 0 if block is empty.
 */
int get_block_type_square(int vertical_coords, int horizontal_coords);

/**
 * @brief Get block type for I piece.
 *
 * @return 1 if block is filled, 0 if block is empty.
 */
int get_block_type_I(int rotation, int vertical_coords, int horizontal_coords);

/**
 * @brief Get block type for L piece.
 *
 * @return 1 if block is filled, 0 if block is empty.
 */
int get_block_type_L(int rotation, int vertical_coords, int horizontal_coords);

/**
 * @brief Get block type for mirrorred L  piece.
 *
 * @return 1 if block is filled, 0 if block is empty.
 */
int get_block_type_L_mirrorred(int rotation, int vertical_coords,
                               int horizontal_coords);

/**
 * @brief Get block type for N piece.
 *
 * @return 1 if block is filled, 0 if block is empty.
 */
int get_block_type_N(int rotation, int vertical_coords, int horizontal_coords);

/**
 * @brief Get block type for mirrorred N piece.
 *
 * @return 1 if block is filled, 0 if block is empty.
 */
int get_block_type_N_mirrorred(int rotation, int vertical_coords,
                               int horizontal_coords);

/**
 * @brief Get block type for T piece.
 *
 * @return 1 if block is filled, 0 if block is empty.
 */
int get_block_type_T(int rotation, int vertical_coords, int horizontal_coords);

#endif  // PIECES_H_
