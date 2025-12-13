#include <stdio.h>
#include "../include/ui.h"
#include "../include/utils.h"
#include "../include/patient.h"
#include "../include/receptionist.h"

int main() {
    // ui_clear_screen();
    // ui_print_banner();
    // printf("\n\n\n");
    // // ui_print_start_menu();
    // const char* menu[] = {"Login", "Register", "Exit"};
    // ui_print_menu("Main Menu", menu, 3, 72);
    // ui_pause();

    receptionist_menu();
    return 0;
}