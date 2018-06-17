/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "gomoku.h"

/**
 * The main function - the main entry point into your program
 **/
int main(void) {

  int selection;

 do {

   print_menu();

   selection = get_menu_input();

   switch (selection) {
  
    case PLAY_GAME:
      play_game();
      break;
  
    case EXIT_GAME:
      break;
  
    default: 
      invalid_menu_selection_error();
      break;
  
 } 
  
} while (selection != EXIT_GAME);

  /* initialise the random number generator for your program */
  /* display the menu continuously until the user decided to quit the
   * program
   */

  return EXIT_SUCCESS;
}
