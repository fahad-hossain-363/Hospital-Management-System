/**
 * @file admin.h
 * @brief Admin management functions for Healthcare Management System
 * 
 * This header declares admin-specific operations including
 * discharged patient management that receptionists cannot access.
 */

#ifndef ADMIN_H
#define ADMIN_H

#include "hospital.h"

/**
 * Views all discharged (inactive) patients.
 */
 void admin_view_discharged_patients(void);

/**
 * Searches discharged patients by ID.
 */
 void admin_search_discharged_by_id(void);

/**
 * Searches discharged patients by name.
 */
 void admin_search_discharged_by_name(void);

/**
 * Handles search choice for discharged patients.
 */
 void admin_search_discharged(void);

/**
 * Permanently deletes a discharged patient from the system.
 */
 void admin_delete_patient(void);

 /**
 * Views all discharged (inactive) doctors.
 */
 void admin_view_discharged_doctors(void);

 /**
 * Permanently deletes an inactive doctor from the system.
 */
 void admin_delete_doctor(void);

 /**
  * Admin patient management menu.
  */
  void admin_patient_menu(void);
 
 /**
 * Admin doctor management menu.
 */
 void admin_doctor_menu(void);
 
/**
 * Main admin menu.
 */
 void admin_main_menu(void);

/**
 * Admin receptionist management menu.
 */
 void admin_receptionist_menu(void);

#endif
