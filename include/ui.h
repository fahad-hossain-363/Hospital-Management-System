/**
 * @file ui.h
 * @brief Header file for user interface functions.
 *
 * This header file contains declarations for user interface functions
 * used in the hospital management system.
 */

#ifndef UI_H
#define UI_H

#include "hospital.h"

/* 
 *======================================================================
 *                         ANSI COLOR CODES                                  
 *======================================================================
 */

/* Basic Foreground Colors */
#define BLACK          "\033[30m"
#define RED            "\033[31m"
#define GREEN          "\033[32m"
#define BLUE           "\033[34m"
#define YELLOW         "\033[33m"
#define MAGENTA        "\033[35m"
#define CYAN           "\033[36m"
#define WHITE          "\033[37m"

/* Bright Foreground Colors */
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

/* Extended Foreground Colors (256-color palette) */
#define LIME           "\033[38;5;154m"
#define SOFT_CYAN      "\033[38;5;159m"
#define SOFT_TEAL      "\033[38;5;44m"
#define SOFT_GREEN     "\033[38;5;120m"
#define SOFT_RED       "\033[38;5;124m"
#define SOFT_BLUE      "\033[38;5;75m"
#define SOFT_GRAY      "\033[38;5;250m"
#define SOFT_YELLOW    "\033[38;5;187m"

/* Neon Accent Colors */
#define NEON_TEAL      "\033[38;5;51m"
#define NEON_PINK      "\033[38;5;205m"
#define NEON_PURPLE    "\033[38;5;141m"
#define NEON_ORANGE    "\033[38;5;208m"

/* Status Colors */
#define STATUS_GOOD    "\033[38;5;114m"
#define STATUS_WARN    "\033[38;5;214m"
#define STATUS_BAD     "\033[38;5;160m"
#define STATUS_INFO    "\033[38;5;75m"

/* Muted/Dim Text Colors */
#define TEXT_MUTED     "\033[38;5;244m"
#define TEXT_DIM       "\033[38;5;240m"

/* Basic Background Colors */
#define BG_BLACK       "\033[40m"
#define BG_WHITE       "\033[47m"

/* Bright Background Colors */
#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"

/* Extended Background Colors */
#define BG_NEON_PURPLE "\033[48;5;57m"
#define BG_NEON_TEAL   "\033[48;5;43m"

/* Text Styles */
#define RESET          "\033[0m"
#define BOLD           "\033[1m"
#define UNDERLINE      "\033[4m"

/* Cursor */
#define HIDE_CURSOR    "\033[?25l"
#define SHOW_CURSOR    "\033[?25h"

/* 
 *=======================================================================
 *                         FUNCTION PROTOTYPES                                
 *=======================================================================
 */

 
/**
 * Clears the console screen.
 */
 void ui_clear_screen(void);

 
/**
 * Pauses the program execution until the user presses a key.
 */
 void ui_pause(void);
 
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
 * Prints the HMS banner.
 */
 void ui_print_banner(void);
 
/**
 * Prints a menu in a box.
 *
 * @param title The title of the menu.
 * @param items The array of menu items.
 * @param item_count The number of menu items.
 * @param box_width The width of the box.
 */
 void ui_print_menu(const char *title, const char *items[], int item_count, int box_width);

/**
 * Prints a patient in a box.
 *
 * @param patient The patient to print.
 */
 void ui_print_patient(Patient patient, int index);

/**
 * Prints a doctor in a box.
 *
 * @param doctor The doctor to print.
 * @param index The display index.
 */
 void ui_print_doctor(Doctor doctor, int index);

/**
 * Prints a receptionist in a box.
 *
 * @param receptionist The receptionist to print.
 * @param index The display index.
 */
 void ui_print_receptionist(Receptionist receptionist, int index);

/**
 * Prints a dummy loading animation.
 */
 void ui_dummy_loading(int time);
 
 #endif
