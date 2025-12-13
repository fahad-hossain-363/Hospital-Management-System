/**
 * @file doctor.h
 * @brief Doctor management functions for Healthcare Management System
 * 
 * This header declares all doctor-related CRUD operations.
 */

#ifndef DOCTOR_H
#define DOCTOR_H

#include "hospital.h"

/**
 * Saves all doctors to binary file.
 * @return 0 on success, -1 on failure.
 */
 int doctor_save_to_file(void);

/**
 * Loads all doctors from binary file.
 * @return 0 on success, -1 if file doesn't exist.
 */
 int doctor_load_from_file(void);

/**
 * Generates a unique doctor ID.
 * @return The generated doctor ID.
 */
 int doctor_generate_id(void);

/**
 * Displays all doctors in the system.
 */
 void doctor_view_all(void);

/**
 * Displays doctors one by one.
 */
 void doctor_view_one(void);

/**
 * Handles the view choice for doctor.
 */
 void doctor_view(void);

/**
 * Searches for a doctor by ID.
 */
 void doctor_search_by_id(void);

/**
 * Searches for a doctor by name.
 */
 void doctor_search_by_name(void);

/**
 * Searches for a doctor by phone number.
 */
 void doctor_search_by_phone(void);

/**
 * Handles the search choice for doctor.
 */
 void doctor_search_by(void);

/**
 * Searches doctor by ID and returns index.
 * @param id The doctor ID to search for.
 * @return Index of doctor in array, or -1 if not found.
 */
 int doctor_search_id(int id);

/**
 * Updates a doctor information by ID.
 */
 void doctor_update_using_id(void);

/**
 * Deactivates a doctor by ID (sets is_active to false).
 */
 void doctor_deactivate_account(void);

/**
 * Displays all inactive doctors in the system.
 */
 void doctor_view_discharged(void);

#endif
