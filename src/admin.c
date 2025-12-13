/**
 * @file admin.c
 * @brief Admin management implementation for Healthcare Management System
 * 
 * This file contains admin-specific operations including
 * discharged patient/doctor management that receptionists cannot access.
 */

#include <stdio.h>
#include <string.h>
#include "../include/admin.h"
#include "../include/patient.h"
#include "../include/doctor.h"
#include "../include/receptionist.h"
#include "../include/auth.h"
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/hospital.h"

/*
 *==========================================================================
 *                       DISCHARGED PATIENT FUNCTIONS
 *==========================================================================
 */

void admin_view_discharged_patients(void) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();

    if (patient_unavailable == 0) {
        const char* menu_items[] = {"No discharged patients found!"};
        ui_print_menu("Discharged Patients", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }

    for (int i = 0; i < patient_count; i++) {
        if (!patients[i].is_active) {
            ui_print_patient(patients[i], count++);
        }
    }
    ui_pause();
}

void admin_search_discharged_by_id(void) {
    int id;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Enter Patient ID (0 to cancel): ",
            ">> "
        };
        
        ui_print_menu("Search Discharged Patient", menu_items, 2, UI_SIZE);
        id = utils_get_int();

        if (id == 0) return;

        if (!utils_is_valid_id(id, ROLE_PATIENT)) {
            ui_print_error("Invalid ID!");
            ui_pause();
            continue;
        }

        for (int i = 0; i < patient_count; i++) {
            if (patients[i].id == id && !patients[i].is_active) {
                ui_clear_screen();
                ui_print_banner();
                ui_print_patient(patients[i], i);
                ui_pause();
                return;
            }
        }
        ui_print_error("Discharged patient not found with that ID!");
        ui_pause();
        return;
    } while (1);
}

void admin_search_discharged_by_name(void) {
    char name[NAME_SIZE];
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Enter Patient Name: ",
            ">> "
        };
        
        ui_print_menu("Search Discharged Patient", menu_items, 2, UI_SIZE);
        utils_get_string(name, NAME_SIZE);

        if (!utils_is_valid_name(name)) {
            ui_print_error("Invalid name!");
            ui_pause();
            continue;
        }

        utils_fix_name(name);
        for (int i = 0; i < patient_count; i++) {
            if (strcmp(patients[i].name, name) == 0 && !patients[i].is_active) {
                ui_clear_screen();
                ui_print_banner();
                ui_print_patient(patients[i], i);
                ui_pause();
                return;
            }
        }
        ui_print_error("Discharged patient not found with that name!");
        ui_pause();
        return;
    } while (1);
}

void admin_search_discharged(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Search by ID",
            "Search by Name",
            "Back",
            ">> "
        };
        
        ui_print_menu("Search Discharged Patients", menu_items, 4, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                admin_search_discharged_by_id();
                break;
            case 2:
                admin_search_discharged_by_name();
                break;
            case 3:
                return;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 3);
}

void admin_delete_patient(void) {
    int id;
    
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        
        const char* enter_id_items[] = {
            "Enter patient ID to permanently delete (0 to cancel): ",
            ">> "
        };
        
        ui_print_menu("Delete Patient Permanently", enter_id_items, 2, UI_SIZE);
        id = utils_get_int();

        if (id == 0) return;

        if (!utils_is_valid_id(id, ROLE_PATIENT)) {
            ui_print_error("Invalid ID!");
            ui_pause();
            continue;
        }
        break;
    }

    // Find the patient
    int index = -1;
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == id && !patients[i].is_active) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        ui_print_error("Discharged patient not found! Only discharged patients can be permanently deleted.");
        ui_pause();
        return;
    }

    ui_clear_screen();
    ui_print_banner();
    ui_print_patient(patients[index], index);
    
    const char* menu[] = {
        "Confirm Permanent Delete",
        "Cancel",
        ">> "
    };
    
    ui_print_menu("Delete Patient Permanently", menu, 3, UI_SIZE);
    int input = utils_get_int();

    if (input == 1) {
        // Shift all patients after this index
        for (int i = index; i < patient_count - 1; i++) {
            patients[i] = patients[i + 1];
        }
        patient_count--;
        patient_unavailable--;
        
        ui_print_success("Patient permanently deleted from the system!");
        patient_save_to_file();
        ui_pause();
    } else {
        ui_print_info("Deletion cancelled.");
        ui_pause();
    }
}

void admin_patient_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Add Patient",
            "View Active Patients",
            "View Discharged Patients",
            "Search Active Patient",
            "Search Discharged Patient",
            "Update Patient",
            "Discharge Patient",
            "Delete Patient Permanently",
            "Back to Admin Menu",
            ">> "
        };
        
        ui_print_menu("Admin Patient Management", menu_items, 10, UI_SIZE);
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
                admin_view_discharged_patients();
                break;
            case 4:
                patient_search_by();
                break;
            case 5:
                admin_search_discharged();
                break;
            case 6:
                patient_update_using_id();
                patient_save_to_file();
                break;
            case 7:
                patient_discharge();
                patient_save_to_file();
                break;
            case 8:
                admin_delete_patient();
                break;
            case 9:
                ui_print_info("Returning to admin menu...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 9);
}

/*
 *==========================================================================
 *                       INACTIVE DOCTOR FUNCTIONS
 *==========================================================================
 */

void admin_view_discharged_doctors(void) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();

    if (doctor_unavailable == 0) {
        const char* menu_items[] = {"No inactive doctors found!"};
        ui_print_menu("Inactive Doctors", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }

    for (int i = 0; i < doctor_count; i++) {
        if (!doctors[i].is_active) {
            ui_print_doctor(doctors[i], count++);
        }
    }
    ui_pause();
}

void admin_delete_doctor(void) {
    int id;
    
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        
        const char* enter_id_items[] = {
            "Enter doctor ID to permanently delete (0 to cancel): ",
            ">> "
        };
        
        ui_print_menu("Delete Doctor Permanently", enter_id_items, 2, UI_SIZE);
        id = utils_get_int();

        if (id == 0) return;

        if (!utils_is_valid_id(id, ROLE_DOCTOR)) {
            ui_print_error("Invalid ID!");
            ui_pause();
            continue;
        }
        break;
    }

    // Find the doctor
    int index = -1;
    for (int i = 0; i < doctor_count; i++) {
        if (doctors[i].id == id && !doctors[i].is_active) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        ui_print_error("Inactive doctor not found! Only inactive doctors can be permanently deleted.");
        ui_pause();
        return;
    }

    ui_clear_screen();
    ui_print_banner();
    ui_print_doctor(doctors[index], index);
    
    const char* menu[] = {
        "Confirm Permanent Delete",
        "Cancel",
        ">> "
    };
    
    ui_print_menu("Delete Doctor Permanently", menu, 3, UI_SIZE);
    int input = utils_get_int();

    if (input == 1) {
        // Shift all doctors after this index
        for (int i = index; i < doctor_count - 1; i++) {
            doctors[i] = doctors[i + 1];
        }
        doctor_count--;
        doctor_unavailable--;
        
        ui_print_success("Doctor permanently deleted from the system!");
        doctor_save_to_file();
        ui_pause();
    } else {
        ui_print_info("Deletion cancelled.");
        ui_pause();
    }
}

void admin_doctor_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "View Active Doctors",
            "View Inactive Doctors",
            "Search Doctor",
            "Update Doctor",
            "Deactivate Doctor",
            "Delete Doctor Permanently",
            "Back to Admin Menu",
            ">> "
        };
        
        ui_print_menu("Admin Doctor Management", menu_items, 8, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                doctor_view_all();
                break;
            case 2:
                admin_view_discharged_doctors();
                break;
            case 3:
                doctor_search_by();
                break;
            case 4:
                doctor_update_using_id();
                doctor_save_to_file();
                break;
            case 5:
                doctor_deactivate_account();
                doctor_save_to_file();
                break;
            case 6:
                admin_delete_doctor();
                break;
            case 7:
                ui_print_info("Returning to admin menu...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 7);
}

void admin_receptionist_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "View Active Receptionists",
            "View Inactive Receptionists",
            "Deactivate Receptionist",
            "Delete Receptionist Permanently",
            "Back to Admin Menu",
            ">> "
        };
        
        ui_print_menu("Admin Receptionist Management", menu_items, 6, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                receptionist_view_all();
                break;
            case 2:
                receptionist_view_discharged();
                break;
            case 3:
                receptionist_discharge();
                break;
            case 4:
                ui_print_info("Delete receptionist permanently - Coming soon!");
                ui_pause();
                break;
            case 5:
                ui_print_info("Returning to admin menu...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 4);
}

/*
 *==========================================================================
 *                             MAIN ADMIN MENU
 *==========================================================================
 */

void admin_main_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Register New User",
            "Patient Management",
            "Doctor Management",
            "Receptionist Management",
            "Logout",
            ">> "
        };
        
        ui_print_menu("Admin Portal", menu_items, 6, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                auth_register_user();
                break;
            case 2:
                admin_patient_menu();
                break;
            case 3:
                admin_doctor_menu();
                break;
            case 4:
                admin_receptionist_menu();
                break;
            case 5:
                ui_print_info("Logging out...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 5);
}
