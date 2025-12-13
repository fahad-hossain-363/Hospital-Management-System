/**
 * @file receptionist.h
 * @brief Receptionist portal and data management functions
 */

#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include "hospital.h"

/**
 * Saves all receptionists to binary file.
 * @return 0 on success, -1 on failure.
 */
int receptionist_save_to_file(void);

/**
 * Loads all receptionists from binary file.
 * @return 0 on success, -1 if file doesn't exist.
 */
int receptionist_load_from_file(void);

/**
 * Searches for a receptionist by ID.
 * @param id The receptionist ID to search for.
 * @return Index of receptionist, or -1 if not found.
 */
int receptionist_search_id(int id);

/**
 * Views all active receptionists.
 */
void receptionist_view_all(void);

/**
 * Views all inactive receptionists.
 */
void receptionist_view_discharged(void);

/**
 * Deactivates a receptionist.
 */
void receptionist_discharge(void);

/**
 * Receptionist patient management menu.
 */
void receptionist_patient_menu(void);

/**
 * Receptionist appointment menu.
 */
void receptionist_appointment_menu(void);

/**
 * Main receptionist portal menu.
 */
void receptionist_menu(void);

#endif
