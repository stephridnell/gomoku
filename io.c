/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/
#include "io.h"
#include "error.h"
#include <limits.h>

/**
 * this file has the implementation functions for input / output. All ouput
 * should happen from this module so that it would be easy to rewrite output to
 * another format, such as a gui application.
 **/

/**
 * The values for the various game tokens as strings. These are in the same
 * order as the cell enumeration. In other works the 0th element is for empty,
 * the first is red and the second is white. The NULL pointer on the end is for
 * the C_INVALID constant
 **/
const char* game_tokens[NUM_TOKEN_TYPES] = {
  " ", RED_COLOR "o" RESET_COLOR, WHITE_COLOR "o" RESET_COLOR, NULL
};

/**
 * the read rest of line function - clears the buffer when there is buffer
 *  overflow
 **/
void read_rest_of_line(void) {
  int ch;
  /* read each char in the input buffer until we run out of chars to read
   */
  while (ch = getc(stdin), ch != '\n' && ch != EOF)
    ;
  /* clear the error status on the stdin FILE pointer */
  clearerr(stdin);
}

/**
 * print function provided to be able to print from outside this module
 **/
int error_print(const char* format, ...) {
  /* the number of chars printed by this function */
  int charsPrinted;
  va_list argvec;
  /* marshall the output for sending to vprintf */
  va_start(argvec, format);
  /* change the color to red and print the Error preambe for an error
   * message */
  charsPrinted = fprintf(stderr, RED_COLOR "Error: ");
  /* print the output required by the user */
  charsPrinted += vfprintf(stderr, format, argvec);
  /* reset back to the default colour */
  charsPrinted += fprintf(stderr, RESET_COLOR);
  /* stop using the stdarg library */
  va_end(argvec);
  return charsPrinted;
}

/**
 * print normal output - this function literally just calls printf.
 **/
int normal_print(const char* format, ...) {
  int charsPrinted;
  va_list argvec;
  va_start(argvec, format);
  charsPrinted = vprintf(format, argvec);
  va_end(argvec);
  return charsPrinted;
}

void print_menu(void) {
  normal_print("\n");
  normal_print("Welcome to Gomoku \n");
  normal_print("==================\n");
  normal_print("1) play the game\n");
  normal_print("2) quit\n");
  normal_print("Please enter your choice:\n");
}

void get_input(char* inputValue, int size) {
  fgets(inputValue, size, stdin);

  /**
  * Code courtesy of Paul Miller, week 3 sample material
  **/

  /**
  * test if the newline character was stored - if 
  * it was not then we have buffer overflow and therefore
  * must clear the buffer 
  **/
  if(inputValue[strlen(inputValue) - 1] != '\n') {
    read_rest_of_line();
  }

  /** 
  * remove the newline character as it is no longer needed
  **/
  inputValue[strlen(inputValue)-1] = 0;
}

int get_menu_input(void) {
  int inputLength = 0;
  char menuInput[LINE_LENGTH + EXTRA_CHARS];

  get_input(menuInput, sizeof(menuInput));

  /* error handling */
  if (menuInput[0] < 48 || menuInput[0] > 57) {
    return NON_INT;
  }
  inputLength = strlen(menuInput);
  if (inputLength > 1) {
    return TOO_LONG;
  }

  return menuInput[0];
}
