/**
 * @file hospital.c
 * @brief Global data definitions for Healthcare Management System
 * 
 * This file contains the actual definitions of global variables
 * declared with extern in hospital.h.
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <direct.h>
#else
    #include <sys/stat.h>
#endif

#include "../include/hospital.h"
#include "../include/patient.h"
#include "../include/doctor.h"
#include "../include/appointment.h"
#include "../include/receptionist.h"
#include "../include/auth.h"
#include "../include/ui.h"
#include "../include/utils.h"

Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
Receptionist receptionists[MAX_RECEPTIONISTS];
User users[MAX_USERS];
Appointment appointments[MAX_APPOINTMENTS];

int patient_count = 0;
int patient_available = 0;
int patient_unavailable = 0;
int doctor_count = 0;
int doctor_available = 0;
int doctor_unavailable = 0;
int receptionist_count = 0;
int receptionist_available = 0;
int receptionist_unavailable = 0;
int user_count = 0;
int appointment_count = 0;

User* current_user = NULL;

void hospital_init(void) {
    patient_load_from_file();
    doctor_load_from_file();
    appointment_load_from_file();
    auth_load_from_file();
    auth_init_default_admin();
}

void show_about(void) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* about_items[] = {
        "Healthcare Management System (HMS)",
        "Version: 1.0",
        "Developed for efficient hospital management",
        "including patient, doctor, and appointment",
        "tracking with role-based access control.",
        "Roles: Admin, Receptionist, Doctor",
        ""
    };
    
    ui_print_menu("About HMS", about_items, 7, UI_SIZE);
    ui_pause();
}

void print_help(const char* program_name) {
    printf("\n" BOLD BRIGHT_RED "Healthcare Management System" RESET BOLD SOFT_GREEN " v%s" RESET "\n\n", VERSION);
    printf(SOFT_YELLOW "Usage:" RESET " %s [option] or .\\hms.exe [option] for windows\n", program_name);
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
    #ifdef _WIN32
        _mkdir("data");
    #else
        mkdir("data", 0755);
    #endif
}
