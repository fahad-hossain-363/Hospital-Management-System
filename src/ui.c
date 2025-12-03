#include <stdio.h>
#include <stdlib.h>
#include "../include/ui.h"
#include "../include/utils.h"


void ui_clear_screen(void) {
    #ifdef _WIN32
        system("cls");
        #else
        system("clear");
    #endif
}

void ui_print_header(const char *title) {
    ui_clear_screen();
    printf(COLOR_MAGENTA "%s\n" COLOR_RESET, title);
}

void ui_print_success(const char *message) {
    printf(COLOR_GREEN "%s" COLOR_RESET "\n", message);
}

void ui_print_error(const char *message) {
    printf(COLOR_RED "%s" COLOR_RESET "\n", message);
}

void ui_print_warning(const char *message) {
    printf(COLOR_YELLOW "%s" COLOR_RESET "\n", message);
}

void ui_print_info(const char *message) {
    printf(COLOR_BLUE "%s" COLOR_RESET "\n", message);
}

void ui_main_menu(void) {
    ui_print_header("HEALTHCARE MANAGEMENT SYSTEM - Main Menu");
    
    printf("\n");
    printf("  " COLOR_CYAN "1." COLOR_RESET " Patient Management\n");
    printf("  " COLOR_CYAN "2." COLOR_RESET " Doctor Management\n");
    printf("  " COLOR_CYAN "3." COLOR_RESET " Appointment Management\n");
    printf("  " COLOR_CYAN "4." COLOR_RESET " Reports\n");
    printf("  " COLOR_CYAN "5." COLOR_RESET " Exit\n");
    printf("\n");
    printf("Select Option : ");
}
