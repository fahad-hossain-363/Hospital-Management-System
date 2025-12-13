/**
 * @file doctor_portal.h
 * @brief Doctor portal functions for Healthcare Management System
 * 
 * This header declares doctor-specific portal operations.
 */

#ifndef DOCTOR_PORTAL_H
#define DOCTOR_PORTAL_H

#include "hospital.h"

/**
 * Views all appointments for current doctor.
 * @param doctor_id The doctor's ID.
 */
 void doctor_portal_view_appointments(int doctor_id);

/**
 * Views pending appointments for current doctor.
 * @param doctor_id The doctor's ID.
 */
 void doctor_portal_view_pending(int doctor_id);

/**
 * Views today's appointments for current doctor.
 * @param doctor_id The doctor's ID.
 * @param today_date Today's date string.
 */
 void doctor_portal_view_today(int doctor_id, const char* today_date);

/**
 * Views patient details for a given patient ID.
 */
 void doctor_portal_view_patient(void);

/**
 * Marks an appointment as completed.
 * @param doctor_id The doctor's ID.
 */
 void doctor_portal_complete_appointment(int doctor_id);

/**
 * Cancels an appointment.
 * @param doctor_id The doctor's ID.
 */
 void doctor_portal_cancel_appointment(int doctor_id);

/**
 * Updates doctor's availability status.
 * @param doctor_id The doctor's ID.
 */
 void doctor_portal_update_availability(int doctor_id);

/**
 * Views doctor's own profile.
 * @param doctor_id The doctor's ID.
 */
 void doctor_portal_view_profile(int doctor_id);

/**
 * Main doctor portal menu.
 * @param doctor_id The doctor's ID.
 * @param doctor_name The doctor's name for display.
 */
 void doctor_portal_menu(int doctor_id, const char* doctor_name);

#endif
