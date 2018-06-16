/******************************************************************************
 * Student Name    :    Steph Ridnell
 * RMIT Student ID :    s3272974
 * COURSE CODE     :    CPT220
 *****************************************************************************/
#include "error.h"
#include "io.h"

void too_long_error(void) {
  error_print("input entered is too long. Please try again.\n");
}

void non_int_error(void) {
  error_print("input was not numeric. Please try again.\n");
}

void invalid_menu_selection_error(void) {
  error_print("invalid menu item selected\n");
}
