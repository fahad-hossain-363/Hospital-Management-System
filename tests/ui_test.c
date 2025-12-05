#include <stdio.h>
#include "../include/ui.h"
#include "../include/utils.h"

int main() {
    ui_print_banner();
    printf("\n\n\n");
    // ui_print_start_menu();
    const char* menu[] = {"Login", "Register", "Exit"};
    ui_print_menu("Main Menu", menu, 3, 72);
    utils_pause();
    return 0;
}