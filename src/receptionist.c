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
            "Enter your choice: "
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
            "Enter your choice: "
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
            "Enter your choice: "
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
