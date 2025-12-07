/**
 * @file patient.c
 * @brief Patient management implementation for Healthcare Management System
 * 
 * This file contains the implementation of all patient CRUD operations.
 */

#include <stdio.h>
#include <string.h>
#include "../include/patient.h"
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/hospital.h"

int generate_patient_id(void) {
    return PATIENT_ID_START + patient_count;
}

void patient_add(void) {
    if (patient_count >= MAX_PATIENTS) {
        ui_print_error("Error: Maximum patient limit reached!");
        ui_pause();
        return;
    }
    
    // Create new patient
    Patient new_patient;
    new_patient.id = generate_patient_id();
    new_patient.is_active = true;
    
    // lines for menu
    char name_line[70], age_line[70], gender_line[70], phone_line[70], address_line[70], blood_group_line[70];
    
    // Step 1: Get Name
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step1[] = {"Name:", ">> "};
        ui_print_menu("Add Patient", step1, 2, 72);
        utils_get_string(new_patient.name, NAME_SIZE);
        if (utils_is_valid_name(new_patient.name)) {
            utils_fix_name(new_patient.name);
            break;
        }
        ui_print_error("Invalid name! Please try again.");
        ui_pause();
    }
    
    // Step 2: Get Age
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        sprintf(name_line, "Name: %s", new_patient.name);
        const char* step2[] = {name_line, "Age:", ">> "};
        ui_print_menu("Add Patient", step2, 3, 72);
        new_patient.age = utils_get_int();
        if (new_patient.age > 0 && new_patient.age < 120) {
            break;
        }
        ui_print_error("Invalid age! Please try again.");
        ui_pause();
    }
    
    // Step 3: Get Gender
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        sprintf(age_line, "Age: %d", new_patient.age);
        const char* step3[] = {name_line, age_line, "Gender (M/F):", ">> "};
        ui_print_menu("Add Patient", step3, 4, 72);
        char gender_input = utils_get_char();
        if (gender_input == 'M' || gender_input == 'm') {
            new_patient.gender = MALE;
            break;
        } else if (gender_input == 'F' || gender_input == 'f') {
            new_patient.gender = FEMALE;
            break;
        }
        ui_print_error("Invalid gender! Please try again.");
        ui_pause();
    }
    
    // Step 4: Get Phone
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        sprintf(gender_line, "Gender: %s", (new_patient.gender == MALE) ? "Male" : "Female");
        const char* step4[] = {name_line, age_line, gender_line, "Phone (11 digits):", ">> "};
        ui_print_menu("Add Patient", step4, 5, 72);
        utils_get_string(new_patient.phone, PHONE_SIZE);
        if (utils_is_valid_phone(new_patient.phone)) {
            break;
        }
        ui_print_error("Invalid phone! Please try again.");
        ui_pause();
    }
    
    // Step 5: Get Address
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        sprintf(phone_line, "Phone: %s", new_patient.phone);
        const char* step5[] = {name_line, age_line, gender_line, phone_line, "Address:", ">> "};
        ui_print_menu("Add Patient", step5, 6, 72);
        utils_get_string(new_patient.address, ADDRESS_SIZE);
        if (utils_is_valid_address(new_patient.address)) {
            break;
        }
        ui_print_error("Invalid address! Please try again.");
        ui_pause();
    }
    
    // Step 6: Get Blood Group
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        sprintf(address_line, "Address: %s", new_patient.address);
        const char* step6[] = 
        {
            name_line, age_line, gender_line, phone_line, address_line, 
            "Blood Group (e.g. A+, O-, or U for Unknown):", ">> "
        };
        ui_print_menu("Add Patient", step6, 7, 72);
        utils_get_string(new_patient.blood_group, BLOOD_SIZE);
        if (utils_is_valid_blood_group(new_patient.blood_group)) {
            utils_str_to_upper(new_patient.blood_group);
            break;
        }
        ui_print_error("Invalid blood group! Please try again.");
        ui_pause();
    }

    // Step 7: Confirm
    sprintf(blood_group_line, "Blood Group: %s", new_patient.blood_group);
    const char* step7[] = 
    {
        name_line, age_line, gender_line, phone_line, address_line, blood_group_line,
        "Confirm (Y/N):", ">> "
    };
    ui_clear_screen();
    ui_print_banner();
    ui_print_menu("Add Patient", step7, 8, 72);
    char confirm = utils_get_char();
    if (confirm != 'Y' && confirm != 'y') {
        ui_print_info("Patient addition cancelled.");
        ui_pause();
        return;
    }
    
    // Add to array
    patients[patient_count] = new_patient;
    patient_count++;
    
    ui_clear_screen();
    ui_print_banner();

    char id_line[70];
    sprintf(id_line, "Patient ID: %d", new_patient.id);
    const char* success_items[] = {
        id_line, name_line, age_line, gender_line, phone_line, address_line, blood_group_line,
        "Patient added successfully!"
    };
    ui_print_menu("Patient Added", success_items, 8, 72);
    ui_pause();
    
}

void search_patient_by(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Search by patient ID",
            "Search by patient name",
            "Search by patient phone",
            "Back to Patient Menu",
            "Enter your choice: "
        };
        
        ui_print_menu("Search Patient", menu_items, 5, 72);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                // patient_search_by_id();
                break;
            case 2:
                // patient_search_by_name();
                break;
            case 3:
                // patient_search_by_phone();
                break;
            case 4:
                ui_print_info("Returning to receptionist menu...");
                break;
            default:
                ui_print_error("Invalid choice! Please try again.");
                ui_pause();
        }
    } while (choice != 4);
}

void receptionist_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Add Patient",
            "View All Patients",
            "Search Patient",
            "Update Patient",
            "Delete Patient",
            "Back to Main Menu",
            "Enter your choice: "
        };
        
        ui_print_menu("Receptionist Menu", menu_items, 7, 72);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                patient_add();
                break;
            case 2:
                // patient_view_all();
                break;
            case 3: {
                ui_clear_screen();
                ui_print_banner();
                
                // Way of searching {ID, name, phone} 
                search_patient_by();
                ui_pause();
                break;
            }
            case 4:
                // patient_update();
                break;
            case 5:
                // patient_delete();
                break;
            case 6:
                ui_print_info("Returning to main menu...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice! Please try again.");
                ui_pause();
        }
    } while (choice != 6);
}