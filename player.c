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
  char name[NAME_LENGTH + EXTRA_CHARS];
  enum input_result result = IR_FAILURE;

  /* associate the game with this player */
  currentPlayer->currentGame = theGame;
  /* associate the token with the player */
  currentPlayer->token = token;
  /* prompt the user for their name */
  while (result == IR_FAILURE) {
    normal_print("Please enter the name for player %d: ", playerNumber);
    result = get_input(name, NAME_LENGTH + EXTRA_CHARS);
    if (result == IR_RTM) {
      result = quit_game();
      if (result == IR_SUCCESS) {
        result = IR_FAILURE;
      } else if (result == IR_RTM) {
        return IR_RTM;
      }
    }
  }
  /* copy the name read from the keyboard into the player struct */
  strcpy(currentPlayer->name, name);
  return IR_SUCCESS;
}

/**
 * get input for a turn from the user, validate it as a move coordinate and if
 * it is valid, apply the move to the board. If the move is not valid then
 * display an error message but if it is valid return a IR_SUCCESS result. If a
 * user has chosen to quit the game, return IR_RTM.
 **/
enum input_result take_turn(struct player* currentPlayer) {
  struct coordinate coords;
  char location[NAME_LENGTH + EXTRA_CHARS];
  enum input_result result = IR_FAILURE;

  while (result == IR_FAILURE) {
    normal_print("Please enter your turn in a comma delimited format, eg: 15,13: ");
    result = get_input(location, 5 + EXTRA_CHARS);
    if (result == IR_RTM) {
      result = quit_game();
      if (result == IR_SUCCESS) {
        result = IR_FAILURE;
      } else if (result == IR_RTM) {
        return IR_RTM;
      }
    }
    if (result != IR_FAILURE) {
      if (!str_to_coord(location, &coords)) {
        result = IR_FAILURE;
      } else if (move_is_valid(currentPlayer, &coords)) {
        apply_move(currentPlayer->currentGame->gameBoard, &coords, currentPlayer->token);
      } else {
        result = IR_FAILURE;
        invalid_move_error(location);
      }
    }
  }
  return IR_FAILURE;
}
