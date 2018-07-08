/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "game.h"
#include <math.h>

/**
 * this file contains the implementation of functions for the management of the
 * game
 **/

/**
 * initialises the game to a starting state. You should select a random token
 * for one player and ensure the second player has a different token. You should
 * call init_player() passing in the address of the player, its token, and a
 * pointer to this game. Finally you should initialise the pointers to each
 * player ensuring that a random player is selected to play the game. You should
 * also ensure the board is coorectly initialised through a call to
 * init_board().
 * 
 * some code taken from paul miller part a sample solution
 **/
enum input_result init_game(struct game* newGame) {

  int count;
  int token;
  int currentPlayer;

  /* select random tokens */
  token = rand() % NUM_PLAYERS + 1;

  /* initialise the board */
  init_board(newGame->gameBoard);

  /* initialise the players */
  for (count = 0; count < NUM_PLAYERS; ++count) {
    /* select a valid token for each player */
    ++token;
    if (token == C_INVALID) {
      token = C_RED;
    }

    /* 
    * call init_player to do the initialisation of the players.
    * Please note that as this is a function that calls i/o
    * functions it returns a enum indicating success / failure or
    * request to quit the game
    */
    if (init_player(&newGame->players[count], token, newGame, count + 1) == IR_RTM) {
      return IR_RTM;
    }
  }
  
  /* select the play order of the players */
  currentPlayer = rand() % NUM_PLAYERS;
  newGame->current = &newGame->players[currentPlayer];
  currentPlayer = (currentPlayer + 1 % NUM_PLAYERS);
  newGame->other = &newGame->players[currentPlayer % NUM_PLAYERS];
  return IR_SUCCESS;

}

/**
 * manages the main game loop - calls init_game to initialise the game and
 * then loops and calls take_turn for the current player and swaps players until
 * a player has won the game
 * 
 * some code taken from paul miller part a sample solution
 **/
void play_game(void) {
  /* the game struct that holds the data on the game state */
  struct game currentGame;
  BOOLEAN winner = FALSE;

  /* init the game struct */
  if (init_game(&currentGame) == IR_RTM) {
    normal_print("the game has been quit!\n");
    return;
  }

  normal_print("%s plays first.\n\n", currentGame.current->name);

  display_board(currentGame.gameBoard);

  if (first_round(&currentGame) == IR_RTM) {
    normal_print("the game has been quit!\n");
    return;
  }

  /* the game loop */
  while (!winner) {
    display_board(currentGame.gameBoard);
    normal_print("It is %s's turn and their colour is %s.\n", currentGame.current->name, color_strings[currentGame.current->token]);
    
    if (take_turn(currentGame.current) == IR_RTM) {
      normal_print("the game has been quit!\n");
      return;
    }

    winner = is_winner(currentGame.current);

    if (!winner) {
      swap_players(&currentGame.current, &currentGame.other);
    }
  }

  normal_print("%s is the winner.\n", currentGame.current->name);
  display_board(currentGame.gameBoard);
  return;
}

/**
 * swaps the two player pointers for the two players playing the current game
 * (it's a way for us to swap who the current player is). Please note that an
 * implementation that swaps values rather than pointers will not get full marks
 * for this. This function is only worth a few marks but the intellectual
 * content understanding is very important and thus it is worth substantially
 * more than a few lines of code are worth elsewhere in this assignment.
 **/
void swap_players(struct player** first, struct player** second) {
  /* create a temp player to store the first player while we switch the first player to be the second one */
  struct player* temp = *first;
  *first = *second;
  *second = temp;
}

/**
 * implements the rules for the first round of the game, the so-called
 * swap2 rules. Please see the assignment specification and game rules for
 * further details.
 **/
enum input_result first_round(struct game* theGame) {
  struct coordinate coords;
  /* enum cell *currentCell; */
  char location[NAME_LENGTH + EXTRA_CHARS];
  enum input_result result = IR_FAILURE;
  int turns = 0, turnsCopy = 0, colour = 0;

  /* first player goes twice */
  while (result == IR_FAILURE) {
    normal_print("Please enter a location for a %s token: ", color_strings[theGame->current->token]);
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
      } else {
        if (coords.x != ceil(BOARD_WIDTH / 2.0) || coords.y != ceil(BOARD_HEIGHT / 2.0)) {
          invalid_first_move();
          result = IR_FAILURE;
        } else {
          set_cell(theGame->gameBoard, coords.x, coords.y, theGame->current->token);
          display_board(theGame->gameBoard);
        }
      }
    }
  }

  result = IR_FAILURE;

  while (result == IR_FAILURE) {
    normal_print("Please enter a location for a %s token: ", color_strings[theGame->current->token]);
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
      } else {
        /* make sure next to another piece
        currentCell = get_cell(theGame->gameBoard, coords.x, coords.y); */
        set_cell(theGame->gameBoard, coords.x, coords.y, theGame->current->token);
        display_board(theGame->gameBoard);
      }
    }
  }

  /* place token of other colour */

  result = IR_FAILURE;

  while (result == IR_FAILURE) {
    normal_print("Please enter a location for a %s token: ", color_strings[theGame->other->token]);
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
      } else {
        set_cell(theGame->gameBoard, coords.x, coords.y, theGame->other->token);
        display_board(theGame->gameBoard);
      }
    }
  }

  result = IR_FAILURE;

  swap_players(&theGame->current, &theGame->other);

  normal_print("It is now %s's turn.\n", theGame->current->name);

  while (result == IR_FAILURE) {
    normal_print("Do you wish to enter one (1) or two (2) tokens (Please enter a digit) ? ");
    result = get_input(location, 2 + EXTRA_CHARS);
    if (str_to_int(location, &turns)) {
      if (turns != 1 && turns != 2) {
        result = IR_FAILURE;
      }
    } else {
      result = IR_FAILURE;
    }
    if (result == IR_RTM) {
      result = quit_game();
      if (result == IR_SUCCESS) {
        result = IR_FAILURE;
      } else if (result == IR_RTM) {
        return IR_RTM;
      }
    }
  }

  result = IR_FAILURE;

  while (result == IR_FAILURE) {
    normal_print("Please enter the colour of the token(s) to play: ");
    result = get_input(location, 6 + EXTRA_CHARS);
    if (strncmp(location, "red", 1) == 0) {
       colour = C_RED;
    } else if (strncmp(location, "white", 1) == 0) {
       colour = C_WHITE;
    } else {
      invalid_colour_error(location);
      result = IR_FAILURE;
    }
    if (result == IR_RTM) {
      result = quit_game();
      if (result == IR_SUCCESS) {
        result = IR_FAILURE;
      } else if (result == IR_RTM) {
        return IR_RTM;
      }
    }
  }

  turnsCopy = turns;

  while (turns > 0) {
    result = IR_FAILURE;
    while (result == IR_FAILURE) {
      normal_print("Please enter a location for a %s token: ", color_strings[colour]);
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
        } else {
          set_cell(theGame->gameBoard, coords.x, coords.y, colour);
          display_board(theGame->gameBoard);
        }
      }
    }
    turns--;
  }

  result = IR_FAILURE;

  swap_players(&theGame->current, &theGame->other);
  
  if (turnsCopy == 2) {
    while (result == IR_FAILURE) {
      normal_print("%s, Which colour do you wish to play for the rest of the game? \n", theGame->current->name);
      result = get_input(location, 6 + EXTRA_CHARS);
      if (strncmp(location, "red", 1) == 0) {
        theGame->current->token = C_RED;
        theGame->other->token = C_WHITE;
      } else if (strncmp(location, "white", 1) == 0) {
        theGame->current->token = C_WHITE;
        theGame->other->token = C_RED;
      } else {
        invalid_colour_error(location);
        result = IR_FAILURE;
      }
      if (result == IR_RTM) {
        result = quit_game();
        if (result == IR_SUCCESS) {
          result = IR_FAILURE;
        } else if (result == IR_RTM) {
          return IR_RTM;
        }
      }
    }
  }

  return IR_SUCCESS;
}
