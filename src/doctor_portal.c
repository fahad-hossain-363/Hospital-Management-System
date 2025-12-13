/**
 * @file doctor_portal.c
 * @brief Doctor portal implementation for Healthcare Management System
 * 
 * This file contains the doctor's personal portal with appointment
 * management and profile features.
 */

#include <stdio.h>
#include <string.h>
#include "../include/doctor_portal.h"
#include "../include/appointment.h"
#include "../include/patient.h"
#include "../include/doctor.h"
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/hospital.h"

void doctor_portal_view_appointments(int doctor_id) {
    appointment_view_by_doctor(doctor_id);
}

void doctor_portal_view_pending(int doctor_id) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();
    
    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].doctor_id == doctor_id && 
            appointments[i].status == APPT_PENDING) {
            ui_print_appointment(appointments[i], count++);
        }
    }
    
    if (count == 0) {
        const char* menu_items[] = {"No pending appointments!"};
        ui_print_menu("Pending Appointments", menu_items, 1, UI_SIZE);
    }
    ui_pause();
}

void doctor_portal_view_today(int doctor_id, const char* today_date) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();
    
    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].doctor_id == doctor_id && 
            strcmp(appointments[i].date, today_date) == 0 &&
            appointments[i].status != APPT_CANCELLED) {
            ui_print_appointment(appointments[i], count++);
        }
    }
    
    if (count == 0) {
        const char* menu_items[] = {"No appointments for today!"};
        ui_print_menu("Today's Appointments", menu_items, 1, UI_SIZE);
    }
    ui_pause();
}

void doctor_portal_view_patient(void) {
    int patient_id;
    
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu_items[] = {
        "Enter Patient ID:",
        ">> "
    };
    
    ui_print_menu("View Patient Details", menu_items, 2, UI_SIZE);
    patient_id = utils_get_int();
    
    if (!utils_is_valid_id(patient_id, ROLE_PATIENT)) {
        ui_print_error("Invalid patient ID!");
        ui_pause();
        return;
    }
    
    int idx = patient_search_id(patient_id);
    if (idx == -1) {
        ui_print_error("Patient not found!");
        ui_pause();
        return;
    }
    
    ui_clear_screen();
    ui_print_banner();
    ui_print_patient(patients[idx], idx);
    ui_pause();
}

void doctor_portal_complete_appointment(int doctor_id) {
    int appt_id;
    
    // First show pending appointments
    ui_clear_screen();
    ui_print_banner();
    
    int count = 0;
    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].doctor_id == doctor_id && 
            (appointments[i].status == APPT_PENDING || 
             appointments[i].status == APPT_CONFIRMED)) {
            ui_print_appointment(appointments[i], count++);
        }
    }
    
    if (count == 0) {
        const char* menu_items[] = {"No appointments to complete!"};
        ui_print_menu("Complete Appointment", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }
    
    const char* input_items[] = {
        "Enter Appointment ID to mark as completed (0 to cancel):",
        ">> "
    };
    ui_print_menu("Complete Appointment", input_items, 2, UI_SIZE);
    appt_id = utils_get_int();
    
    if (appt_id == 0) return;
    
    int idx = appointment_search_id(appt_id);
    if (idx == -1) {
        ui_print_error("Appointment not found!");
        ui_pause();
        return;
    }
    
    if (appointments[idx].doctor_id != doctor_id) {
        ui_print_error("This appointment is not assigned to you!");
        ui_pause();
        return;
    }
    
    appointments[idx].status = APPT_COMPLETED;
    appointment_save_to_file();
    ui_print_success("Appointment marked as completed!");
    ui_pause();
}

void doctor_portal_cancel_appointment(int doctor_id) {
    int appt_id;
    
    // First show pending appointments
    ui_clear_screen();
    ui_print_banner();
    
    int count = 0;
    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].doctor_id == doctor_id && 
            appointments[i].status == APPT_PENDING) {
            ui_print_appointment(appointments[i], count++);
        }
    }
    
    if (count == 0) {
        const char* menu_items[] = {"No appointments to cancel!"};
        ui_print_menu("Cancel Appointment", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }
    
    const char* input_items[] = {
        "Enter Appointment ID to cancel (0 to go back):",
        ">> "
    };
    ui_print_menu("Cancel Appointment", input_items, 2, UI_SIZE);
    appt_id = utils_get_int();
    
    if (appt_id == 0) return;
    
    int idx = appointment_search_id(appt_id);
    if (idx == -1) {
        ui_print_error("Appointment not found!");
        ui_pause();
        return;
    }
    
    if (appointments[idx].doctor_id != doctor_id) {
        ui_print_error("This appointment is not assigned to you!");
        ui_pause();
        return;
    }
    
    appointments[idx].status = APPT_CANCELLED;
    appointment_save_to_file();
    ui_print_success("Appointment cancelled!");
    ui_pause();
}

void doctor_portal_update_availability(int doctor_id) {
    int idx = doctor_search_id(doctor_id);
    if (idx == -1) {
        ui_print_error("Doctor not found!");
        ui_pause();
        return;
    }
    
    ui_clear_screen();
    ui_print_banner();
    
    char current_status[50];
    snprintf(current_status, sizeof(current_status), "Current Status: %s", 
             doctors[idx].is_available ? "Available" : "Unavailable");
    
    const char* menu_items[] = {
        "Set availability (1 for available, 2 for unavailable): ",
        current_status,
        "Back",
        ">> "
    };
    
    ui_print_menu("Update Availability", menu_items, 4, UI_SIZE);
    int choice = utils_get_int();
    
    switch (choice) {
        case 1:
            doctors[idx].is_available = true;
            doctor_save_to_file();
            ui_print_success("Status set to Available!");
            ui_pause();
            break;
        case 2:
            doctors[idx].is_available = false;
            doctor_save_to_file();
            ui_print_success("Status set to Unavailable!");
            ui_pause();
            break;
        case 3:
            return;
        default:
            ui_print_error("Invalid choice!");
            ui_pause();
    }
}

void doctor_portal_view_profile(int doctor_id) {
    int idx = doctor_search_id(doctor_id);
    if (idx == -1) {
        ui_print_error("Doctor not found!");
        ui_pause();
        return;
    }
    
    ui_clear_screen();
    ui_print_banner();
    ui_print_doctor(doctors[idx], idx);
    ui_pause();
}

void doctor_portal_menu(int doctor_id, const char* doctor_name) {
    int choice;
    
    // Build title with doctor's name
    char title[80];
    snprintf(title, sizeof(title), "Doctor Portal | Dr. %s", doctor_name);
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "View All My Appointments",
            "View Pending Appointments",
            "View Patient Details",
            "Complete Appointment",
            "Cancel Appointment",
            "Update My Availability",
            "View My Profile",
            "Logout",
            ">> "
        };
        
        ui_print_menu(title, menu_items, 9, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                doctor_portal_view_appointments(doctor_id);
                break;
            case 2:
                doctor_portal_view_pending(doctor_id);
                break;
            case 3:
                doctor_portal_view_patient();
                break;
            case 4:
                doctor_portal_complete_appointment(doctor_id);
                break;
            case 5:
                doctor_portal_cancel_appointment(doctor_id);
                break;
            case 6:
                doctor_portal_update_availability(doctor_id);
                break;
            case 7:
                doctor_portal_view_profile(doctor_id);
                break;
            case 8:
                ui_print_info("Logging out...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 8);
}
