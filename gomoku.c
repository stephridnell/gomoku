/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "gomoku.h"

int main(void) {
  char menuInput[LINE_LENGTH + EXTRA_CHARS];
  int selection;

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

  /* initialise the random number generator for your program */
  /* display the menu continuously until the user decided to quit the
   * program
   */

  return EXIT_SUCCESS;
}
