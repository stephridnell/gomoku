/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "rules.h"
#include "game.h"
#include "player.h"

/**
 * This file implements the functions that are part of implementing the game
 * rules. Note that there is no new data structures here other than the ones
 * elsewhere in the program
 **/

/**
 * check in the horizontal, vertical, left and right diagonal directions whether
 * there is a winning numinrow tokens that matches the player's token. If there
 * is, return TRUE
 **/
BOOLEAN is_winner(const struct player* currentPlayer) {
  return FALSE;
}

/**
 * check if a move is valid. It is valid if the cell specified is empty
 **/
BOOLEAN move_is_valid(const struct player* currentPlayer, const struct coordinate* curmove) {
  return TRUE;
}

/**
 * apply the move to the board - simply set the board coordinates specified by
 * themove to the toke specified.
 **/
BOOLEAN apply_move(board theboard, const struct coordinate* themove, enum cell token) {
  set_cell(theboard, themove->x, themove->y, token);
  return TRUE;
}
