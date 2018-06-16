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
  char menuInput[LINE_LENGTH + EXTRA_CHARS];
  int selection;
  /**
   * Display the menu
  **/

 do {

   print_menu();

   selection = get_menu_input(menuInput);

   switch (selection) {
     case PLAY_GAME:
      printf("play game\n");
      break;
     case EXIT_GAME:
      break;
     default: 
      error_print("invalid menu item selected\n");
      break;
 } 
  
} while (selection != EXIT_GAME);


  /* you should treat the comments in this function as a hint on how to 
   * get started. You should start by getting a menu working that behaves
   * the same as the sample executable. 
   */
  /* initialise the random number generator for your program */
  /* display the menu continuously until the user decided to quit the
   * program
   */
    /* display the menu and get the choice from the user */
      /* based on the choice the user made you should:
       */
        /* play the game */
        /* quit the program */
  return EXIT_SUCCESS;
}
