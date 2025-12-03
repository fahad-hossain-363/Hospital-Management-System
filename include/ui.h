#ifndef UI_H
#define UI_H

/**
 * @file ui.h
 * @brief Header file for user interface functions.
 *
 * This header file contains declarations for user interface functions
 * used in the hospital management system.
 */

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_BLUE    "\033[34m"

#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_MAGENTA "\033[35m"

/**
 * Clears the console screen.
 */
 void ui_clear_screen(void);

 /**
 * Prints a formatted header with title.
 * 
 * @param title The title to display.
 */
void ui_print_header(const char *title);

/**
 * Prints a success message in green.
 * 
 * @param message The success message.
 */
void ui_print_success(const char *message);

/**
 * Prints an error message in red.
 * 
 * @param message The error message.
 */
void ui_print_error(const char *message);

/**
* Prints a warning message in yellow.
 * 
 * @param message The warning message.
 */
void ui_print_warning(const char *message);

/**
* Prints an info message in cyan.
 * 
 * @param message The info message.
 */
 void ui_print_info(const char *message);

/**
 * Displays the main menu.
 */
void ui_main_menu(void);


#endif
