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

#define VERSION "1.0.0"

void print_help(const char* program_name);
void print_version(void);
void ensure_data_dir(void);

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
            ui_print_error("Invalid option!");
            ui_pause();
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

void print_help(const char* program_name) {
    printf("\n" BOLD BRIGHT_RED "Healthcare Management System" RESET BOLD SOFT_GREEN " v%s" RESET "\n\n", VERSION);
    printf(SOFT_YELLOW "Usage:" RESET " %s [option] or ./hms.exe [option] for windows\n", program_name);
    printf(SOFT_YELLOW "Usage:" RESET " ./hms.out [option] for linux\n\n");
    printf(SOFT_YELLOW "Options:" RESET "\n");
    printf("  -h, --help      Show this help message\n");
    printf("  -v, --version   Show version information\n");
    printf("  -a, --about     Show about information\n");
    printf("  -l, --login     Go directly to login menu\n");
    printf("\n");
    printf("If no options are provided, the interactive menu will start.\n\n");
}

void print_version(void) {
    printf("\n" BOLD "Healthcare Management System" RESET "\n");
    printf("Version: " SOFT_GREEN "%s" RESET "\n", VERSION);
    printf("Built with C\n\n");
}

void ensure_data_dir(void) {

    FILE* file = fopen(PATIENTS_FILE, "rb");
    if (file == NULL) {
        system("mkdir data 2>nul"); // 2>nul for already existing folder
    } else {
        fclose(file);
    }

}
