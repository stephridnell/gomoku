/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "board.h"
#include "io.h"

/**
 * This file contains the implementation of the functions that manipulates the
 * board type
 **/

/**
 * initialise the board to be an empty board
 **/
void init_board(board theBoard) {

	memset(theBoard, 0, sizeof(enum cell) * BOARD_WIDTH * BOARD_HEIGHT);

}

/**
 * set the value in a cell to the contents value specified
 * from paul miller sample solution for part a
 **/
BOOLEAN set_cell(board aboard, int x, int y, enum cell contents) {
  int map[BOARD_HEIGHT];
  int i;
  for (i = 0; i < BOARD_HEIGHT; i++ ) {
    map[i] = BOARD_HEIGHT - i;
  }

  normal_print("X: %d, Y: %d", x, y);

  if (x >= BOARD_WIDTH || y >= BOARD_HEIGHT || x < 0 || y < 0) {
    return FALSE;
  }

  aboard[map[y]][x - 1] = contents;

  return TRUE;

}

/**
 * gets the value stored in a cell. Note that I am returning a pointer for when
 * an invalid request is sents - int that case we should return NULL
 * from paul miller sample solution for part a
 **/
enum cell* get_cell(board aboard, int x, int y) {
  int map[BOARD_HEIGHT];
  int i;
  for (i = 0; i < BOARD_HEIGHT; i++ ) {
    map[i] = BOARD_HEIGHT - i;
  }

  if (x >= BOARD_WIDTH || y >= BOARD_HEIGHT || x < 0 || y < 0) {
    return NULL;
  }

	return &aboard[map[y]][x - 1];

}
