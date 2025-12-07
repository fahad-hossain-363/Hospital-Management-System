/**
 * @file ui.c
 * @brief User interface functions for Healthcare Management System
 * 
 * This file contains the implementation of user interface functions
 * used throughout the HMS application.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/ui.h"
#include "../include/utils.h"


void ui_clear_screen(void) {
    #ifdef _WIN32
        system("cls");
        #else
        system("clear");
    #endif
}

void ui_pause(void) {
    printf("\nPress enter to continue...");
    getchar();
}

void ui_print_header(const char *title) {
    ui_clear_screen();
    printf(MAGENTA "\n%s\n" RESET, title);
}

void ui_print_success(const char *message) {
    printf(GREEN "\n%s" RESET "\n", message);
}

void ui_print_error(const char *message) {
    printf(RED "\n%s" RESET "\n", message);
}

void ui_print_warning(const char *message) {
    printf(YELLOW "\n%s" RESET "\n", message);
}

void ui_print_info(const char *message) {
    printf(BRIGHT_BLUE "\n%s" RESET "\n", message);
}


void ui_print_banner(void){
    unsigned char b = 219;  // █ Full block character
    
    char* hms = 
    "#####################################\n"
    "#                                   #\n"
    "#        X  X  X   X  XXXX          #\n"
    "#        X  X  XX XX  X             #\n"
    "#        XXXX  X X X  XXXX          #\n"
    "#        X  X  X   X     X          #\n"
    "#        X  X  X   X  XXXX          #\n"
    "#                                   #\n"
    "#    HEALTHCARE MANAGEMENT SYSTEM   #\n"
    "#                                   #\n"
    "#####################################\n";
    
    printf("\n");
    
    while (*hms) {
        if (*hms == 'X') {
            printf(BRIGHT_RED "%c%c" RESET, b, b);
        } 
        else if (*hms == '#') {
            printf(SOFT_GRAY "%c%c" RESET, b, b);
        }
        else if (*hms == '\n') {
            printf("\n");
        } 
        else if (isalpha(*hms)){
            printf(BOLD CYAN "%c" RESET " ", *hms);
        } 
        else {
            printf("  ");
        }
        hms++;
    }
}

void ui_print_menu
    (
    const char *title, 
    const char *items[], 
    int item_count, 
    int box_width
    ) {
    unsigned char h = 205;  // ═
    unsigned char v = 186;  // ║
    unsigned char tl = 201; // ╔
    unsigned char tr = 187; // ╗
    unsigned char bl = 200; // ╚
    unsigned char br = 188; // ╝
    
    printf(BRIGHT_BLACK "%c", tl);
    for (int i = 0; i < box_width; i++) printf("%c", h);
    printf("%c" RESET "\n", tr);

    char title_upper[100];
    strncpy(title_upper, title, sizeof(title_upper) - 1);
    title_upper[sizeof(title_upper) - 1] = '\0';
    utils_str_to_upper(title_upper);
    
    int title_len = strlen(title_upper) + 4;
    int title_padding = (box_width - title_len) / 2;
    printf(BRIGHT_BLACK "%c" RESET, v);
    for (int i = 0; i < title_padding; i++) printf(" ");
    printf(BG_NEON_PURPLE BOLD "  %s  " RESET, title_upper);
    for (int i = 0; i < box_width - title_padding - title_len; i++) printf(" ");
    printf(BRIGHT_BLACK "%c" RESET "\n", v);
    
    printf(BRIGHT_BLACK "%c" RESET, v);
    for (int i = 0; i < box_width; i++) printf(" ");
    printf(BRIGHT_BLACK "%c" RESET "\n", v);
    
    for (int i = 0; i < item_count - 1; i++) {
        int item_len = strlen(items[i]);
        printf(BRIGHT_BLACK "%c" RESET "  " SOFT_YELLOW BOLD "%d. %s" RESET, v, i + 1, items[i]);
        for (int j = 0; j < box_width - item_len - 5; j++) printf(" ");
        printf(BRIGHT_BLACK "%c" RESET "\n", v);
    }
    
    printf(BRIGHT_BLACK "%c" RESET, v);
    for (int i = 0; i < box_width; i++) printf(" ");
    printf(BRIGHT_BLACK "%c" RESET "\n", v);
    printf(BRIGHT_BLACK "%c", bl);
    for (int i = 0; i < box_width; i++) printf("%c", h);
    printf("%c" RESET "\n\n", br);
    
    printf(BOLD SOFT_GREEN "%s" RESET, items[item_count - 1]);
}