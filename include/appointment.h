/**
 * @file appointment.h
 * @brief Appointment management functions for Healthcare Management System
 * 
 * This header declares appointment-related CRUD operations.
 */

#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "hospital.h"

/**
 * Saves all appointments to binary file.
 * @return 0 on success, -1 on failure.
 */
 int appointment_save_to_file(void);

/**
 * Loads all appointments from binary file.
 * @return 0 on success, -1 if file doesn't exist.
 */
 int appointment_load_from_file(void);

/**
 * Generates a unique appointment ID.
 * @return The generated appointment ID.
 */
 int appointment_generate_id(void);

/**
 * Creates a new appointment (called by receptionist).
 */
 void appointment_create(void);

/**
 * Views all appointments for a specific doctor.
 * @param doctor_id The doctor's ID.
 */
 void appointment_view_by_doctor(int doctor_id);

/**
 * Views all appointments for a specific patient.
 * @param patient_id The patient's ID.
 */
 void appointment_view_by_patient(int patient_id);

/**
 * Updates appointment status.
 * @param appt_id The appointment ID.
 * @param status The new status.
 */
 void appointment_update_status(int appt_id, AppointmentStatus status);

/**
 * Cancels an appointment.
 * @param appt_id The appointment ID.
 */
 void appointment_cancel(int appt_id);

/**
 * Finds appointment by ID.
 * @param id The appointment ID.
 * @return Index of appointment, or -1 if not found.
 */
 int appointment_search_id(int id);

/**
 * Gets status string from enum.
 * @param status The appointment status.
 * @return String representation.
 */
 const char* appointment_status_str(AppointmentStatus status);

/**
 * Prints an appointment in a formatted box.
 * @param appt The appointment to print.
 * @param index The display index.
 */
void ui_print_appointment(Appointment appt, int index);

#endif
