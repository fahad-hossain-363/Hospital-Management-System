#include <stdio.h>
#include "../include/utils.h"
#include "../include/ui.h"

int main() {
    int choice;

    do {
        ui_main_menu();
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                ui_print_info("Patient Management - Coming soon!");
                utils_pause();
                break;
            case 2:
                ui_print_info("Doctor Management - Coming soon!");
                utils_pause();
                break;
            case 3:
                ui_print_info("Appointment Management - Coming soon!");
                utils_pause();
                break;
            case 4:
                ui_print_info("Reports - Coming soon!");
                utils_pause();
                break;
            case 5:
                ui_print_success("Goodbye!");
                break;
            default:
                ui_print_error("Invalid choice!");
                utils_pause();
        }
    } while (choice != 5);

    return 0;
}