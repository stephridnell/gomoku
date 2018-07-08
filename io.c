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
  " ", RED_COLOR "x" RESET_COLOR, WHITE_COLOR "o" RESET_COLOR, NULL
};

const char* color_strings[NUM_TOKEN_TYPES] = {
  "Empty", RED_COLOR "red" RESET_COLOR, WHITE_COLOR "white" RESET_COLOR, NULL
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
  /* the menu items */
  char* menu_items[] = { "play the game", "quit" };
  int count;

  /* display the heading */
  char* heading = "\nWelcome to Gomoku";
  puts(heading);
  PUTLINE('=', strlen(heading));

  /* display each menu item */
  for (count = 0; count < NUM_MENU_ITEMS; ++count) {
    printf("%d) %s\n", count + 1, menu_items[count]);
  }

}

/**
 * prints the heading of the board
 **/
static void print_heading(void) {
  int count;
  for (count = 0; count < BOARD_WIDTH; ++count) {
    printf("%2d|", count + 1);
  }
  putchar('\n');
  PUTLINE('-', (BOARD_WIDTH + 1) * 3);
}

enum input_result quit_game () {
  char selection[1 + EXTRA_CHARS];
  enum input_result result = IR_FAILURE;

  while (result == IR_FAILURE) {
    normal_print("Are you sure you want to quit the game? (y/n): ");
    result = get_input(selection, 1 + EXTRA_CHARS);
    if (result != IR_FAILURE) {
      if (strncmp(selection, "y", 1) == 0) {
        return IR_RTM;
      } else if (strncmp(selection, "n", 1) == 0) {
        return IR_SUCCESS;
      } else {
        invalid_menu_selection_error();
        result = IR_FAILURE;
      }
    }
  }
  return IR_FAILURE;
}

/* gets the user input and does buffer handling */
enum input_result get_input(char* inputValue, int size) {
  fgets(inputValue, size, stdin);
  
  /* if the user just pressed enter - return rtm */
  if (inputValue[0] == '\n') {
    return IR_RTM;
  }

  /* if crtl+D detected - read rest of line and return rtm 
  if (feof(stdin)) {
    read_rest_of_line();
    return IR_RTM;
  }
  */

  /* Code courtesy of Paul Miller, week 3 sample material */

  /**
  * test if the newline character was stored - if 
  * it was not then we have buffer overflow and therefore
  * must clear the buffer and return IR FAILURE
  **/
  if(inputValue[strlen(inputValue) - 1] != '\n') {
    read_rest_of_line();
    too_long_error();
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

/**
 * displays the game board including heading, etc.
 **/
void display_board(board theboard) {
  int y, x;

  /* print the heading for the board */
  printf("\n");
  printf("  |");
  print_heading();

  /* for each row of the board */
  for (y = 0; y < BOARD_HEIGHT; ++y) {
    /* print the row number */
    printf("%-2d", BOARD_HEIGHT - y);

    /* print the values of each cell in the row */
    for (x = 0; x < BOARD_WIDTH; ++x) {
      printf("| %s", game_tokens[theboard[y][x]]);
    }
    printf("|\n");

    /* print the line under each row */

    if (y < BOARD_HEIGHT - 1) {
      PUTLINE('-', 3 * (BOARD_WIDTH + 1));
    } else {
      PUTLINE('=', 3 * (BOARD_WIDTH + 1));
    }
  
  }
}

