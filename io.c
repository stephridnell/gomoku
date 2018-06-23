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
#include <ctype.h>

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

/**
 * print menu
 **/
void print_menu(void) {
  normal_print("\n");
  normal_print("Welcome to Gomoku \n");
  normal_print("==================\n");
  normal_print("1) play the game\n");
  normal_print("2) quit\n");
  normal_print("Please enter your choice:\n");
}

/* gets the user input and does buffer handling */
enum input_result get_input(char* inputValue, int size) {
  fgets(inputValue, size, stdin);
  
  /* if the user just pressed enter - return rtm */
  if (inputValue[0] == '\n') {
    return IR_RTM;
  }

  /* if crtl+D detected - read rest of line and return rtm */
  if (feof(stdin)) {
    read_rest_of_line();
    return IR_RTM;
  }

  /* Code courtesy of Paul Miller, week 3 sample material */

  /**
  * test if the newline character was stored - if 
  * it was not then we have buffer overflow and therefore
  * must clear the buffer and return IR FAILURE
  **/
  if(inputValue[strlen(inputValue) - 1] != '\n') {
    read_rest_of_line();
    return IR_FAILURE;
  }

  /** 
  * remove the newline character as it is no longer needed
  * then return IR SUCCESS
  **/
  inputValue[strlen(inputValue)-1] = 0;
  return IR_SUCCESS;
}

/* function to get the users menu selection and handle the input validation */
int get_menu_input(void) {
  enum input_result ioResult;
  char menuInput[MENU_SELECTION_LENGTH + EXTRA_CHARS];

  ioResult = get_input(menuInput, sizeof(menuInput));

  if (!ioResult) {
    too_long_error();
    return ioResult;
  } else if (!is_int(menuInput)) {
    non_int_error();
    return ioResult;
  }

  return menuInput[0];
}

/* is_int() function from Paul Miller - week 3 sample material */
BOOLEAN is_int(const char * s) {
  while(*s) {
    if(!isdigit(*s)) {
      return FALSE;
    }
    ++s;
  }
  return TRUE;
}

/* function to display the board */
void display_board(board gameBoard) {
  int x, y;

  /* print the space in the top left corner */
  normal_print("%-*s", CELL_WIDTH, "");
  
  /* print header */
  for (x = 1; x <= BOARD_WIDTH; x++) {
    normal_print("|%*d", CELL_WIDTH, x);
  }
  normal_print("|");

  /* print body */
  for (x = BOARD_HEIGHT - 1; x >= 0; x--) {
    print_bar("-");
    /* print row header */
    normal_print("%-*d", CELL_WIDTH, x + 1);
    /* print cells */
    for (y = BOARD_HEIGHT - 1; y >= 0; y--) {
      normal_print("|%*s", CELL_WIDTH, game_tokens[gameBoard[y][x]]);
    }
    normal_print("|");
  }
  print_bar("=");
}

/* function to print a new line */
void print_line(void) {
  normal_print("\n");
}

/* function to print a horizontal bar with a custom symbol */
void print_bar(char* symbol) {
  int i;
  print_line();
  for (i = 0; i < ((BOARD_WIDTH + 1) * (CELL_WIDTH + 1)); i++) {
    normal_print("%s", symbol);
  }
  print_line();
}
