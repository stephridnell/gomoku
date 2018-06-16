/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "shared.h"
#include <string.h>

/**
 * This file defines the board datatype which is just a 2-dimensional array. You
 * should define any functions (the prototype does in this file and the
 * implementation goes into the board.c file.
 **/

#ifndef BOARD_H /*include guard for the board module - ensures that this       \
                   module is only included once in any .c file */
#define BOARD_H
/* the gomoku board is a 19 x 19 cell board but we only use 15x15 of it so
 * that's all we'll keep track of*/
#define BOARD_HEIGHT 15
#define BOARD_WIDTH BOARD_HEIGHT

/* a cell on the board */
enum cell {
  C_EMPTY,
  C_RED,
  C_WHITE,
  C_INVALID
};

/* rename an array or arrays of type enum cell to be a board - note that under
 * the hood it is still an array of ints and will behave accordingly */
typedef enum cell board[BOARD_HEIGHT][BOARD_WIDTH];

/* public functions advertised for this module. You should add additional
 * functions for the managing of the game board */

void init_board(board);

#endif /* include guard for the board module */
