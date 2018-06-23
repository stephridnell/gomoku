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
  int x, y;

	for(y = 0; y < BOARD_WIDTH; y++) {
		for(x = 0; x < BOARD_HEIGHT; x++) {
			theBoard[y][x] = C_EMPTY;
		}
	}
}
