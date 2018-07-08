/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *****************************************************************************/
#include "error.h"
#include "io.h"

/**
 * Prints a messge that the input entered was too long
 **/
void too_long_error(void) {
  error_print("input entered is too long. Please try again.\n");
}

/**
 * Prints a message that the input entered was not numeric
 **/
void non_int_error(void) {
  error_print("input was not numeric. Please try again.\n");
}

/**
 * Prints a message that the menu input was invalid
 **/
void invalid_menu_selection_error(void) {
  error_print("invalid menu item selected\n");
}

void invalid_coordinate_error(const char* input) {
  error_print("%s is not a valid coordinate string. Please try again.\n", input);
}
