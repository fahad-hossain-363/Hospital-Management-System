/**
 * @file appointment.c
 * @brief Appointment management implementation for Healthcare Management System
 * 
 * This file contains the implementation of appointment CRUD operations.
 */

#include <stdio.h>
#include <string.h>
#include "../include/appointment.h"
#include "../include/patient.h"
#include "../include/doctor.h"
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/hospital.h"

int appointment_save_to_file(void) {
    FILE* file = fopen(APPOINTMENTS_FILE, "wb");
    if (file == NULL) {
        return -1;
    }
    fwrite(&appointment_count, sizeof(int), 1, file);
    fwrite(appointments, sizeof(Appointment), appointment_count, file);
    
    fclose(file);
    return 0;
}

int appointment_load_from_file(void) {
    FILE* file = fopen(APPOINTMENTS_FILE, "rb");
    if (file == NULL) {
        return -1;
    }
    fread(&appointment_count, sizeof(int), 1, file);
    fread(appointments, sizeof(Appointment), appointment_count, file);

    fclose(file);
    return 0;
}

int appointment_generate_id(void) {
    return APPOINTMENT_ID_START + appointment_count;
}

const char* appointment_status_str(AppointmentStatus status) {
    switch (status) {
        case APPT_PENDING:   return "Pending";
        case APPT_CONFIRMED: return "Confirmed";
        case APPT_COMPLETED: return "Completed";
        case APPT_CANCELLED: return "Cancelled";
        default:             return "Unknown";
    }
}

int appointment_search_id(int id) {
    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].id == id) {
            return i;
        }
    }
    return -1;
}

void appointment_create(void) {
    if (appointment_count >= MAX_APPOINTMENTS) {
        ui_print_error("Error: Maximum appointment limit reached!");
        ui_pause();
        return;
    }
    
    Appointment new_appt;
    new_appt.id = appointment_generate_id();
    new_appt.status = APPT_PENDING;
    
    char patient_line[70], doctor_line[70], date_line[70], time_line[70];
    
    // Step 1: Get Patient ID
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step1[] = {"Patient ID:", ">> "};
        ui_print_menu("Create Appointment", step1, 2, UI_SIZE);
        new_appt.patient_id = utils_get_int();
        
        if (!utils_is_valid_id(new_appt.patient_id, ROLE_PATIENT)) {
            ui_print_error("Invalid patient ID!");
            ui_pause();
            continue;
        }
        
        int idx = patient_search_id(new_appt.patient_id);
        if (idx == -1 || !patients[idx].is_active) {
            ui_print_error("Patient not found or inactive!");
            ui_pause();
            continue;
        }
        snprintf(patient_line, sizeof(patient_line), "Patient: %s (ID: %d)", 
                 patients[idx].name, new_appt.patient_id);
        break;
    }
    
    // Step 2: Get Doctor ID
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step2[] = {patient_line, "Doctor ID:", ">> "};
        ui_print_menu("Create Appointment", step2, 3, UI_SIZE);
        new_appt.doctor_id = utils_get_int();
        
        if (!utils_is_valid_id(new_appt.doctor_id, ROLE_DOCTOR)) {
            ui_print_error("Invalid doctor ID!");
            ui_pause();
            continue;
        }
        
        int idx = doctor_search_id(new_appt.doctor_id);
        if (idx == -1 || !doctors[idx].is_active) {
            ui_print_error("Doctor not found or inactive!");
            ui_pause();
            continue;
        }
        if (!doctors[idx].is_available) {
            ui_print_warning("Warning: Doctor is marked as unavailable.");
            ui_pause();
        }
        snprintf(doctor_line, sizeof(doctor_line), "Doctor: Dr. %s (ID: %d)", 
                 doctors[idx].name, new_appt.doctor_id);
        break;
    }
    
    // Step 3: Get Date
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step3[] = {patient_line, doctor_line, "Date (DD-MM-YYYY):", ">> "};
        ui_print_menu("Create Appointment", step3, 4, UI_SIZE);
        utils_get_string(new_appt.date, DATE_SIZE);
        
        if (strlen(new_appt.date) > 0) {
            snprintf(date_line, sizeof(date_line), "Date: %s", new_appt.date);
            break;
        }
        ui_print_error("Date cannot be empty!");
        ui_pause();
    }
    
    // Step 4: Get Time Slot
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step4[] = {patient_line, doctor_line, date_line, "Time (e.g. 10:00 AM):", ">> "};
        ui_print_menu("Create Appointment", step4, 5, UI_SIZE);
        utils_get_string(new_appt.time_slot, TIME_SIZE);
        
        if (strlen(new_appt.time_slot) > 0) {
            snprintf(time_line, sizeof(time_line), "Time: %s", new_appt.time_slot);
            break;
        }
        ui_print_error("Time cannot be empty!");
        ui_pause();
    }
    
    // Step 5: Get Reason
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step5[] = {patient_line, doctor_line, date_line, time_line, "Reason for visit:", ">> "};
        ui_print_menu("Create Appointment", step5, 6, UI_SIZE);
        utils_get_string(new_appt.reason, REASON_SIZE);
        
        if (strlen(new_appt.reason) > 0) {
            break;
        }
        ui_print_error("Reason cannot be empty!");
        ui_pause();
    }
    
    // Step 6: Confirm
    char reason_line[120];
    snprintf(reason_line, sizeof(reason_line), "Reason: %s", new_appt.reason);
    const char* step6[] = {
        patient_line, doctor_line, date_line, time_line, reason_line,
        "Confirm (Y/N):", ">> "
    };
    ui_clear_screen();
    ui_print_banner();
    ui_print_menu("Create Appointment", step6, 7, UI_SIZE);
    char confirm = utils_get_char();
    
    if (confirm != 'Y' && confirm != 'y') {
        ui_print_info("Appointment creation cancelled.");
        ui_pause();
        return;
    }
    
    // Add to array
    appointments[appointment_count] = new_appt;
    appointment_count++;
    
    ui_clear_screen();
    ui_print_banner();
    
    char id_line[70];
    snprintf(id_line, sizeof(id_line), "Appointment ID: %d", new_appt.id);
    const char* success_items[] = {
        id_line, patient_line, doctor_line, date_line, time_line,
        "Status: Pending",
        "Appointment created successfully!"
    };
    ui_print_menu("Appointment Created", success_items, 7, UI_SIZE);
    ui_pause();
    
    appointment_save_to_file();
}

void ui_print_appointment(Appointment appt, int index) {
    int p_idx = patient_search_id(appt.patient_id);
    int d_idx = doctor_search_id(appt.doctor_id);
    
    char id_line[70];
    snprintf(id_line, sizeof(id_line), "Appointment ID: %d", appt.id);
    
    char patient_line[70];
    if (p_idx != -1) {
        snprintf(patient_line, sizeof(patient_line), "Patient: %s (ID: %d)", 
                 patients[p_idx].name, appt.patient_id);
    } else {
        snprintf(patient_line, sizeof(patient_line), "Patient ID: %d", appt.patient_id);
    }
    
    char doctor_line[70];
    if (d_idx != -1) {
        snprintf(doctor_line, sizeof(doctor_line), "Doctor: Dr. %s", doctors[d_idx].name);
    } else {
        snprintf(doctor_line, sizeof(doctor_line), "Doctor ID: %d", appt.doctor_id);
    }
    
    char date_line[70];
    snprintf(date_line, sizeof(date_line), "Date: %s", appt.date);
    
    char time_line[70];
    snprintf(time_line, sizeof(time_line), "Time: %s", appt.time_slot);
    
    char reason_line[120];
    snprintf(reason_line, sizeof(reason_line), "Reason: %s", appt.reason);
    
    char status_line[70];
    snprintf(status_line, sizeof(status_line), "Status: %s", appointment_status_str(appt.status));
    
    const char* items[] = {
        id_line, patient_line, doctor_line, date_line, time_line, reason_line, status_line, ""
    };
    
    char title[70];
    snprintf(title, sizeof(title), "Appointment %d", index + 1);
    ui_print_menu(title, items, 8, 72);
}

void appointment_view_by_doctor(int doctor_id) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();
    
    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].doctor_id == doctor_id && 
            appointments[i].status != APPT_CANCELLED) {
            ui_print_appointment(appointments[i], count++);
        }
    }
    
    if (count == 0) {
        const char* menu_items[] = {"No appointments found!"};
        ui_print_menu("My Appointments", menu_items, 1, UI_SIZE);
    }
    ui_pause();
}

void appointment_view_by_patient(int patient_id) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();
    
    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].patient_id == patient_id) {
            ui_print_appointment(appointments[i], count++);
        }
    }
    
    if (count == 0) {
        const char* menu_items[] = {"No appointments found!"};
        ui_print_menu("Patient Appointments", menu_items, 1, UI_SIZE);
    }
    ui_pause();
}

void appointment_update_status(int appt_id, AppointmentStatus status) {
    int idx = appointment_search_id(appt_id);
    if (idx == -1) {
        ui_print_error("Appointment not found!");
        ui_pause();
        return;
    }
    
    appointments[idx].status = status;
    appointment_save_to_file();
    ui_print_success("Appointment status updated!");
    ui_pause();
}

void appointment_cancel(int appt_id) {
    appointment_update_status(appt_id, APPT_CANCELLED);
}
