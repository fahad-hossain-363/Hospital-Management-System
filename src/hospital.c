/**
 * @file hospital.c
 * @brief Global data definitions for Healthcare Management System
 * 
 * This file contains the actual definitions of global variables
 * declared with extern in hospital.h.
 */

#include "../include/hospital.h"
#include "../include/patient.h"
#include "../include/doctor.h"
#include "../include/appointment.h"
#include "../include/auth.h"
#include "../include/ui.h"
#include "../include/utils.h"
#include <stddef.h>

Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
User users[MAX_USERS];
Appointment appointments[MAX_APPOINTMENTS];

int patient_count = 0;
int patient_available = 0;
int patient_unavailable = 0;
int doctor_count = 0;
int doctor_available = 0;
int doctor_unavailable = 0;
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