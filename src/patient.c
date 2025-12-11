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

int patient_save_to_file(void) {
    FILE* file = fopen(PATIENTS_FILE, "wb");
    if (file == NULL) {
        return -1;
    }
    fwrite(&patient_count, sizeof(int), 1, file);
    fwrite(&patient_available, sizeof(int), 1, file);
    fwrite(patients, sizeof(Patient), patient_count, file);
    
    fclose(file);
    return 0;
}

int patient_load_from_file(void) {
    FILE* file = fopen(PATIENTS_FILE, "rb");
    if (file == NULL) {
        return -1;
    }
    fread(&patient_count, sizeof(int), 1, file);
    fread(&patient_available, sizeof(int), 1, file);
    fread(patients, sizeof(Patient), patient_count, file);

    fclose(file);
    return 0;
}

int patient_generate_id(void) {
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
    new_patient.id = patient_generate_id();
    new_patient.is_active = true;
    
    // lines for menu
    char name_line[NAME_LINE_SIZE], age_line[AGE_LINE_SIZE], gender_line[GENDER_LINE_SIZE], phone_line[PHONE_LINE_SIZE], address_line[ADDRESS_LINE_SIZE], blood_group_line[BLOOD_LINE_SIZE];
    
    // Step 1: Get Name
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step1[] = {"Name:", ">> "};
        ui_print_menu("Add Patient", step1, 2, UI_SIZE);
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
        snprintf(name_line, sizeof(name_line), "Name: %s", new_patient.name);
        const char* step2[] = {name_line, "Age:", ">> "};
        ui_print_menu("Add Patient", step2, 3, UI_SIZE);
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
        snprintf(age_line, sizeof(age_line), "Age: %d", new_patient.age);
        const char* step3[] = {name_line, age_line, "Gender (M/F):", ">> "};
        ui_print_menu("Add Patient", step3, 4, UI_SIZE);
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
        snprintf(gender_line, sizeof(gender_line), "Gender: %s", (new_patient.gender == MALE) ? "Male" : "Female");
        const char* step4[] = {name_line, age_line, gender_line, "Phone (11 digits):", ">> "};
        ui_print_menu("Add Patient", step4, 5, UI_SIZE);
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
        snprintf(phone_line, sizeof(phone_line), "Phone: %s", new_patient.phone);
        const char* step5[] = {name_line, age_line, gender_line, phone_line, "Address:", ">> "};
        ui_print_menu("Add Patient", step5, 6, UI_SIZE);
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
        snprintf(address_line, sizeof(address_line), "Address: %s", new_patient.address);
        const char* step6[] = 
        {
            name_line, age_line, gender_line, phone_line, address_line, 
            "Blood Group (e.g. A+, O-, or U for Unknown):", ">> "
        };
        ui_print_menu("Add Patient", step6, 7, UI_SIZE);
        utils_get_string(new_patient.blood_group, BLOOD_SIZE);
        if (utils_is_valid_blood_group(new_patient.blood_group)) {
            utils_str_to_upper(new_patient.blood_group);
            break;
        }
        ui_print_error("Invalid blood group! Please try again.");
        ui_pause();
    }

    // Step 7: Confirm
    snprintf(blood_group_line, sizeof(blood_group_line), "Blood Group: %s", new_patient.blood_group);
    const char* step7[] = 
    {
        name_line, age_line, gender_line, phone_line, address_line, blood_group_line,
        "Confirm (Y/N):", ">> "
    };
    ui_clear_screen();
    ui_print_banner();
    ui_print_menu("Add Patient", step7, 8, UI_SIZE);
    char confirm = utils_get_char();
    if (confirm != 'Y' && confirm != 'y') {
        ui_print_info("Patient addition cancelled.");
        ui_pause();
        return;
    }
    
    // Add to array
    patients[patient_count] = new_patient;
    patient_count++;
    patient_available++;
    
    ui_clear_screen();
    ui_print_banner();

    char id_line[70];
    snprintf(id_line, sizeof(id_line), "Patient ID: %d", new_patient.id);
    const char* success_items[] = 
    {
        id_line, name_line, age_line, 
        gender_line, phone_line, 
        address_line, blood_group_line,
        "Patient added successfully!"
    };
    ui_print_menu("Patient Added", success_items, 8, UI_SIZE);
    ui_pause();
    
}

void patient_view_all() {
    
    int count = 0;
    ui_clear_screen();
    ui_print_banner();

    if (patient_available == 0 || patient_count == 0) {
        const char* menu_items[] = {"No patients found!"};
        ui_print_menu("View All Patients", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }

    for (int i = 0; i < patient_count; i++) {
        if (patients[i].is_active) {
            ui_print_patient(patients[i], count++);
        }
    }
    ui_pause();
}

void patient_view_one() {
    
    int count = 0;

    if (patient_available == 0) {
        ui_clear_screen();
        ui_print_banner();
        const char* menu_items[] = {"No patients found!"};
        ui_print_menu("View All Patients", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }
    
    for (int i = 0; i < patient_count; i++) {
        ui_clear_screen();
        ui_print_banner();
        if (patients[i].is_active) {
            ui_print_patient(patients[i], count++);
            ui_pause();
        }
    }
}

void patient_view() {
    
    const char* menu_items[] = 
    {
        "All at once",
        "One after another",
        "Back to Patient Menu",
        ">> "
    };
    
    int choice;
    do {
        ui_clear_screen();
        ui_print_banner();
        ui_print_menu("View Patients", menu_items, 4, UI_SIZE);
        choice = utils_get_int();
        switch (choice) {
            case 1:
                patient_view_all();
                break;
            case 2:
                patient_view_one();
                break;
            case 3:
                ui_print_info("Returning to receptionist menu...");
                ui_pause();
                return;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
                break;
        }
    } while (choice != 3);
}

void patient_search_by_id(void) {
    
    int id;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Enter ID: ",
            ">> "
        };
        
        ui_print_menu("Search Patient", menu_items, 2, UI_SIZE);
        id = utils_get_int();

        if (!utils_is_valid_id(id, ROLE_PATIENT)) {
            ui_print_error("Invalid ID!");
            ui_pause();
            continue;
        }
        for (int i = 0; i < patient_count; i++) {
            if (patients[i].id == id) {
                ui_clear_screen();
                ui_print_banner();
                
                ui_print_patient(patients[i], (patients[i].id - 1001));
                ui_pause();
                return;
            }
        }
        ui_print_error("Patient not found!");
        ui_pause();
        return;
    } while (1);

}

void patient_search_by_name(void) {
    char name[NAME_SIZE];
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Enter name: ",
            ">> "
        };
        
        ui_print_menu("Search Patient", menu_items, 2, UI_SIZE);
        utils_get_string(name, NAME_SIZE);

        if (!utils_is_valid_name(name)) {
            ui_print_error("Invalid name!");
            ui_pause();
            continue;
        }

        utils_fix_name(name);
        for (int i = 0; i < patient_count; i++) {
            if (strcmp(patients[i].name, name) == 0) {
                ui_clear_screen();
                ui_print_banner();
                
                ui_print_patient(patients[i], (patients[i].id - 1001));
                ui_pause();
                return;
            }
        }
        ui_print_error("Patient not found!");
        ui_pause();
        return;
    } while (1);
}

void patient_search_by_phone(void) {
    char phone[PHONE_SIZE];
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Enter phone: ",
            ">> "
        };
        
        ui_print_menu("Search Patient", menu_items, 2, UI_SIZE);
        utils_get_string(phone, PHONE_SIZE);

        if (!utils_is_valid_phone(phone)) {
            ui_print_error("Invalid phone!");
            ui_pause();
            continue;
        }
        for (int i = 0; i < patient_count; i++) {
            if (strcmp(patients[i].phone, phone) == 0) {
                ui_clear_screen();
                ui_print_banner();

                ui_print_patient(patients[i], (patients[i].id - 1001));
                ui_pause();
                return;
            }
        }
        ui_print_error("Patient not found!");
        ui_pause();
        return;
    } while (1);
}

void patient_search_by(void) {
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
        
        ui_print_menu("Search Patient", menu_items, 5, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                patient_search_by_id();
                break;
            case 2:
                patient_search_by_name();
                break;
            case 3:
                patient_search_by_phone();
                break;
            case 4:
                ui_print_info("Returning to receptionist menu...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice! Please try again.");
                ui_pause();
        }
    } while (choice != 4);
}

int patient_search_id (int id) {
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == id) {
            return i;
        }
    }
    return -1;
}

void patient_update_name(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();

    const char* menu[] = {
        menu_items[0],
        "Enter new name: ",
        ">> "
    };
            
    char name[NAME_SIZE];
    ui_print_menu("Update Patient", menu, 3, UI_SIZE);
    utils_get_string(name, NAME_SIZE);
    utils_fix_name(name);

    if (!utils_is_valid_name(name)) {
        ui_print_error("Invalid name! Could not update.");
        ui_pause();
        return;
    }
    patients[index].name[0] = '\0';
    strncpy(patients[index].name, name, NAME_SIZE);
}

void patient_update_phone(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[1],
        "Enter new phone: ",
        ">> "
    };
            
    char phone[PHONE_SIZE];
    ui_print_menu("Update Patient", menu, 3, UI_SIZE);
    utils_get_string(phone, PHONE_SIZE);

    if (!utils_is_valid_phone(phone)) {
        ui_print_error("Invalid phone! Could not update.");
        ui_pause();
        return;
    }
    patients[index].phone[0] = '\0';
    strncpy(patients[index].phone, phone, PHONE_SIZE);
}

void patient_update_address(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[2],
        "Enter new address: ",
        ">> "
    };
            
    char address[ADDRESS_SIZE];
    ui_print_menu("Update Patient", menu, 3, UI_SIZE);
    utils_get_string(address, ADDRESS_SIZE);

    if (!utils_is_valid_address(address)) {
        ui_print_error("Invalid address! Could not update.");
        ui_pause();
        return;
    }
    patients[index].address[0] = '\0';
    strncpy(patients[index].address, address, ADDRESS_SIZE);
}

void patient_update_blood_group(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[3],
        "Enter new blood group: ",
        ">> "
    };
            
    char blood_group[BLOOD_SIZE];
    ui_print_menu("Update Patient", menu, 3, UI_SIZE);
    utils_get_string(blood_group, BLOOD_SIZE);

    if (!utils_is_valid_blood_group(blood_group)) {
        ui_print_error("Invalid blood group! Could not update.");
        ui_pause();
        return;
    }
    utils_str_to_upper(blood_group);
    patients[index].blood_group[0] = '\0';
    strncpy(patients[index].blood_group, blood_group, BLOOD_SIZE);
}

void patient_update_gender(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[4],
        "Enter new gender: ",
        ">> "
    };
            
    char gender_input;
    ui_print_menu("Update Patient", menu, 3, UI_SIZE);
    while (1) {
        gender_input = utils_get_char();
        if (gender_input == 'M' || gender_input == 'm' || gender_input == 'F' || gender_input == 'f') {
            break;
        }
        ui_print_error("Invalid gender!");
        ui_pause();
    }
    if (gender_input == 'M' || gender_input == 'm') {
        patients[index].gender = MALE;
    } else if (gender_input == 'F' || gender_input == 'f') {
        patients[index].gender = FEMALE;
    }
}

void patient_update_status(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[5],
        "Enter new status: (1 for active, 2 for inactive) ",
        ">> "
    };
    
    bool status;
    int input;
    ui_print_menu("Update Patient", menu, 3, UI_SIZE);
    input = utils_get_int();

    if (input == 1) {
        status = true;
    } else if (input == 2) {
        status = false;
    }
    patients[index].is_active = status;
}

void patient_update_using_id() {
    ui_clear_screen();
    ui_print_banner();

    int id;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* enter_id_items[] = {
            "Enter patient ID: (0 to go back) ",
            ">> "
        };
        
        ui_print_menu("Update Patient", enter_id_items, 2, UI_SIZE);
        id = utils_get_int();
        
        if (id == 0) return;

        if (!utils_is_valid_id(id, ROLE_PATIENT)) {
            ui_print_error("Invalid ID!");
            ui_pause();
        } else {
            ui_print_info("Patient found!");
            ui_pause();
            break;
        }
    } while (1);

    int index = patient_search_id(id);
    if (index == -1) return;

    char name_line[NAME_LINE_SIZE], phone_line[PHONE_LINE_SIZE], address_line[ADDRESS_LINE_SIZE], blood_group_line[BLOOD_LINE_SIZE], gender_line[GENDER_LINE_SIZE], status_line[STATUS_LINE_SIZE];

    snprintf(name_line, NAME_LINE_SIZE, "Name: %s",patients[index].name);
    snprintf(phone_line, PHONE_LINE_SIZE, "Phone: %s",patients[index].phone);
    snprintf(address_line, ADDRESS_LINE_SIZE, "Address: %s",patients[index].address);
    snprintf(blood_group_line, BLOOD_LINE_SIZE, "Blood Group: %s",patients[index].blood_group);

    int patient_id = patients[index].id;

    if (patients[index].gender == MALE) {
        snprintf(gender_line, GENDER_LINE_SIZE, "Gender: Male");
    } else {
        snprintf(gender_line, GENDER_LINE_SIZE, "Gender: Female");
    }
    if (patients[index].is_active) {
        snprintf(status_line, STATUS_LINE_SIZE, "Status: Active");
    } else {
        snprintf(status_line, STATUS_LINE_SIZE, "Status: Discharged");
    }

    const char* menu_items[] = {
        name_line,
        phone_line,
        address_line,
        blood_group_line,
        gender_line,
        "Go back",
        "Enter which field to update: "
    };
    
    char title[50];
    snprintf(title, 50, "Update Patient | ID: %d", patient_id);

    ui_clear_screen();
    ui_print_banner();
    ui_print_menu(title, menu_items, 7, UI_SIZE);

    int choice = utils_get_int();
    
    switch (choice) {
        case 1:
            patient_update_name(menu_items, index);
            break;
        case 2:
            patient_update_phone(menu_items, index);
            break;
        case 3:
            patient_update_address(menu_items, index);
            break;
        case 4:
            patient_update_blood_group(menu_items, index);
            break;
        case 5:
            patient_update_gender(menu_items, index);
            break;
        case 6:
            ui_print_info("Returning to receptionist menu...");
            ui_pause();
            break;
        default:
            ui_print_error("Invalid choice! Please try again.");
            ui_pause();
            break;
    }
}

void patient_discharge() {
    int id;
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        
        const char* enter_id_items[] = {
            "Enter patient ID (0 to cancel): ",
            ">> "
        };
        
        ui_print_menu("Discharge Patient", enter_id_items, 2, UI_SIZE);
        id = utils_get_int();

        if (id == 0) {
            ui_print_info("User Pressed 0. \nCanceling deletion...");
            ui_pause();
            return;
        }

        if (!utils_is_valid_id(id, ROLE_PATIENT)) {
            ui_print_error("Invalid ID!");
            ui_pause();
            continue;
        }
        break;
    }

    int index = patient_search_id(id);
    if (index == -1) {
        ui_print_error("Patient not found!");
        ui_pause();
        return;
    }

    ui_clear_screen();
    ui_print_banner();
    ui_print_patient(patients[index], index);
    
    const char* menu[] = {
        "Confirm Discharge",
        "Cancel",
        ">> "
    };
    
    ui_print_menu("Discharge Patient", menu, 3, UI_SIZE);
    int input = utils_get_int();

    if (input == 1) {
        patients[index].is_active = false;
        ui_print_success("Patient discharged successfully!");
        patient_available--;
        patient_unavailable++;
        ui_pause();
    } else {
        ui_print_info("Discharge cancelled.");
        ui_pause();
    }
}

void patient_view_discharged(void) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();

    if (patient_unavailable == 0) {
        const char* menu_items[] = {"No discharged patients found!"};
        ui_print_menu("Discharged Patients", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }

    for (int i = 0; i < patient_count; i++) {
        if (!patients[i].is_active) {
            ui_print_patient(patients[i], count++);
        }
    }
    ui_pause();
}

void patient_receptionist_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Add Patient",
            "View Active Patients",
            "View Discharged Patients",
            "Search Patient",
            "Update Patient",
            "Discharge Patient",
            "Back to Main Menu",
            "Enter your choice: "
        };
        
        ui_print_menu("Receptionist Menu", menu_items, 8, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                patient_add();
                patient_save_to_file();
                break;
            case 2:
                patient_view();
                break;
            case 3:
                patient_view_discharged();
                break;
            case 4:
                patient_search_by();
                break;
            case 5:
                patient_update_using_id();
                patient_save_to_file();
                break;
            case 6:
                patient_discharge();
                patient_save_to_file();
                break;
            case 7:
                ui_print_info("Returning to main menu...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice! Please try again.");
                ui_pause();
        }
    } while (choice != 7);
}