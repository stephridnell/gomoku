/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "player.h"
#include "game.h"
#include "error.h"

/**
 * this file contains the implementation of the functions for manipulation of
 * the player type
 **/

/**
 * initialises the player passed in so that it has the token specified. You
 * should also prompt the user for this name
 **/
enum input_result init_player(struct player* currentPlayer, enum cell token, struct game* theGame, int playerNumber) {
  enum input_result ioResult = IR_FAILURE;
  char playerName[NAME_LENGTH + EXTRA_CHARS];

  while (!ioResult) {
    normal_print("\n");
    normal_print("Enter name of player %d: ", playerNumber);

    ioResult = get_input(playerName, sizeof(playerName));
  
    if (!ioResult) {
      too_long_error();
    }

  }
  
  return ioResult;
}

/**
 * get input for a turn from the user, validate it as a move coordinate and if
 * it is valid, apply the move to the board. If the move is not valid then
 * display an error message but if it is valid return a IR_SUCCESS result. If a
 * user has chosen to quit the game, return IR_RTM.
 **/
enum input_result take_turn(struct player* currentPlayer) {
  return IR_FAILURE;
}
