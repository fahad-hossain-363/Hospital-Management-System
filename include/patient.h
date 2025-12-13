/**
 * @file patient.h
 * @brief Patient management functions for Healthcare Management System
 * 
 * This header declares all patient-related CRUD operations.
 */

#ifndef PATIENT_H
#define PATIENT_H

#include "hospital.h"

/**
 * Saves all patients to binary file.
 * @return 0 on success, -1 on failure.
 */
 int patient_save_to_file(void);

/**
 * Loads all patients from binary file.
 * @return 0 on success, -1 if file doesn't exist.
 */
 int patient_load_from_file(void);

/**
 * Generates a unique patient ID.
 * @return The generated patient ID.
 */
 int patient_generate_id(void);

/**
 * Adds a new patient to the system.
 */
 void patient_add(void);

/**
 * Searches for a patient by ID.
 */
 void patient_search_by_id(void);

/**
 * Searches for a patient by name.
 */
 void patient_search_by_name(void);

/**
 * Searches for a patient by phone number.
 */
 void patient_search_by_phone(void);

/**
 * Handles the search choice for patient.
 */
 void patient_search_by(void);

/**
 * Updates a patient information by ID.
 */
 void patient_update_using_id(void);

/**
 * Discharges a patient by ID (sets is_active to false).
 */
 void patient_discharge(void);

/**
 * Displays all patients in the system.
 */
 void patient_view_all(void);

/**
 * Displays all discharged patients in the system.
 */
 void patient_view_discharged(void);

/**
 * Searches patient by ID and returns index.
 * @param id The patient ID to search for.
 * @return Index of patient in array, or -1 if not found.
 */
 int patient_search_id(int id);

#endif