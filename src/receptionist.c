/**
 * @file receptionist.c
 * @brief Receptionist portal implementation for Healthcare Management System
 */

#include <stdio.h>
#include <string.h>
#include "../include/receptionist.h"
#include "../include/patient.h"
#include "../include/doctor.h"
#include "../include/appointment.h"
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/hospital.h"

void receptionist_patient_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Add Patient",
            "View Active Patients",
            "View Discharged Patients",
            "Search Patient",
            "Update Patient",
            "Discharge Patient",
            "Back",
            ">> "
        };
        
        ui_print_menu("Patient Management", menu_items, 8, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                patient_add();
                patient_save_to_file();
                break;
            case 2:
                patient_view_all();
                break;
            case 3:
                patient_view_discharged();
                break;
            case 4:
                patient_search_by();
                break;
            case 5:
                patient_update_using_id();
                patient_save_to_file();
                break;
            case 6:
                patient_discharge();
                patient_save_to_file();
                break;
            case 7:
                ui_print_info("Returning to receptionist menu...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 7);
}

void receptionist_appointment_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Create Appointment",
            "View All Appointments",
            "Back",
            ">> "
        };
        
        ui_print_menu("Appointment Management", menu_items, 4, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                appointment_create();
                break;
            case 2:
                ui_clear_screen();
                ui_print_banner();
                for (int i = 0; i < appointment_count; i++) {
                    ui_print_appointment(appointments[i], i);
                }
                if (appointment_count == 0) {
                    const char* no_appt[] = {"No appointments found!"};
                    ui_print_menu("All Appointments", no_appt, 1, UI_SIZE);
                }
                ui_pause();
                break;
            case 3:
                ui_print_info("Returning to receptionist menu...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 3);
}

void receptionist_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Patient Management",
            "Appointment Management",
            "Logout",
            ">> "
        };
        
        ui_print_menu("Receptionist Portal", menu_items, 4, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                receptionist_patient_menu();
                break;
            case 2:
                receptionist_appointment_menu();
                break;
            case 3:
                ui_print_info("Logging out...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 3);
}

/*
 *==========================================================================
 *                        RECEPTIONIST DATA FUNCTIONS
 *==========================================================================
 */

int receptionist_save_to_file(void) {
    FILE* file = fopen(RECEPTIONISTS_FILE, "wb");
    if (file == NULL) {
        return -1;
    }
    if (fwrite(&receptionist_count, sizeof(int), 1, file) != 1 ||
        fwrite(&receptionist_available, sizeof(int), 1, file) != 1 ||
        fwrite(receptionists, sizeof(Receptionist), receptionist_count, file) != (size_t)receptionist_count) {
        fclose(file);
        return -1;
    }
    fclose(file);
    return 0;
}

int receptionist_load_from_file(void) {
    FILE* file = fopen(RECEPTIONISTS_FILE, "rb");
    if (file == NULL) {
        return -1;
    }
    if (fread(&receptionist_count, sizeof(int), 1, file) != 1 ||
        fread(&receptionist_available, sizeof(int), 1, file) != 1) {
        fclose(file);
        return -1;
    }
    if (receptionist_count < 0 || receptionist_count > MAX_RECEPTIONISTS) {
        fclose(file);
        receptionist_count = 0;
        return -1;
    }
    if (fread(receptionists, sizeof(Receptionist), receptionist_count, file) != (size_t)receptionist_count) {
        fclose(file);
        receptionist_count = 0;
        return -1;
    }
    fclose(file);
    return 0;
}

int receptionist_search_id(int id) {
    for (int i = 0; i < receptionist_count; i++) {
        if (receptionists[i].id == id) {
            return i;
        }
    }
    return -1;
}

void receptionist_view_all(void) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();

    if (receptionist_available == 0 || receptionist_count == 0) {
        const char* menu_items[] = {"No receptionists found!"};
        ui_print_menu("View All Receptionists", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }

    for (int i = 0; i < receptionist_count; i++) {
        if (receptionists[i].is_active) {
            ui_print_receptionist(receptionists[i], count++);
        }
    }
    ui_pause();
}

void receptionist_view_discharged(void) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();

    if (receptionist_unavailable == 0) {
        const char* menu_items[] = {"No inactive receptionists found!"};
        ui_print_menu("Inactive Receptionists", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }

    for (int i = 0; i < receptionist_count; i++) {
        if (!receptionists[i].is_active) {
            ui_print_receptionist(receptionists[i], count++);
        }
    }
    ui_pause();
}

void receptionist_discharge(void) {
    int id;
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        
        const char* enter_id_items[] = {
            "Enter receptionist ID (0 to cancel): ",
            ">> "
        };
        
        ui_print_menu("Deactivate Receptionist", enter_id_items, 2, UI_SIZE);
        id = utils_get_int();

        if (id == 0) {
            ui_print_info("Cancelled.");
            ui_pause();
            return;
        }

        if (!utils_is_valid_id(id, ROLE_RECEPTIONIST)) {
            ui_print_error("Invalid ID!");
            ui_pause();
            continue;
        }
        break;
    }

    int index = receptionist_search_id(id);
    if (index == -1) {
        ui_print_error("Receptionist not found!");
        ui_pause();
        return;
    }

    ui_clear_screen();
    ui_print_banner();
    ui_print_receptionist(receptionists[index], index);
    
    const char* menu[] = {
        "Confirm Deactivate",
        "Cancel",
        ">> "
    };
    
    ui_print_menu("Deactivate Receptionist", menu, 3, UI_SIZE);
    int input = utils_get_int();

    if (input == 1) {
        receptionists[index].is_active = false;
        ui_print_success("Receptionist deactivated successfully!");
        receptionist_available--;
        receptionist_unavailable++;
        receptionist_save_to_file();
        ui_pause();
    } else {
        ui_print_info("Deactivation cancelled.");
        ui_pause();
    }
}