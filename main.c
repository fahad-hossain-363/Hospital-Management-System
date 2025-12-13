#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/utils.h"
#include "include/ui.h"
#include "include/hospital.h"
#include "include/patient.h"
#include "include/doctor.h"
#include "include/appointment.h"
#include "include/receptionist.h"
#include "include/admin.h"
#include "include/doctor_portal.h"
#include "include/auth.h"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        }
        else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
            print_version();
            return 0;
        }
    }
    
    // Initialize the system
    // ui_dummy_loading(30);
    hospital_init();
    ensure_data_dir();
    
    if (argc > 1) {
        if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--about") == 0) {
            show_about();
            ui_clear_screen();
            return 0;
        } 
        else if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--login") == 0) {
            login_menu();
            ui_clear_screen();
            return 0;
        }
        else {
            ui_print_error("Invalid option!\n");
            print_help(argv[0]);
            return 1;
        }
    }
    
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Login",
            "About",
            "Exit",
            ">> "
        };
        
        ui_print_menu("Main Menu", menu_items, 4, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                login_menu();
            break;
            case 2:
                show_about();
            break;
            case 3:
                ui_print_success("Goodbye!");
                ui_pause();
                ui_clear_screen();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 3);
    
    return 0;
}
