/**
 * @file doctor.c
 * @brief Doctor management implementation for Healthcare Management System
 * 
 * This file contains the implementation of all doctor CRUD operations.
 */

#include <stdio.h>
#include <string.h>
#include "../include/doctor.h"
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/hospital.h"

int doctor_save_to_file(void) {
    FILE* file = fopen(DOCTORS_FILE, "wb");
    if (file == NULL) {
        return -1;
    }
    fwrite(&doctor_count, sizeof(int), 1, file);
    fwrite(&doctor_available, sizeof(int), 1, file);
    fwrite(doctors, sizeof(Doctor), doctor_count, file);
    
    fclose(file);
    return 0;
}

int doctor_load_from_file(void) {
    FILE* file = fopen(DOCTORS_FILE, "rb");
    if (file == NULL) {
        return -1;
    }
    fread(&doctor_count, sizeof(int), 1, file);
    fread(&doctor_available, sizeof(int), 1, file);
    fread(doctors, sizeof(Doctor), doctor_count, file);

    fclose(file);
    return 0;
}

int doctor_generate_id(void) {
    return DOCTOR_ID_START + doctor_count;
}

void doctor_add(void) {
    if (doctor_count >= MAX_DOCTORS) {
        ui_print_error("Error: Maximum doctor limit reached!");
        ui_pause();
        return;
    }
    
    // Create new doctor
    Doctor new_doctor;
    new_doctor.id = doctor_generate_id();
    new_doctor.is_active = true;
    new_doctor.is_available = true;
    
    // lines for menu
    char name_line[NAME_SIZE], phone_line[PHONE_SIZE], email_line[EMAIL_SIZE], spec_line[SPEC_SIZE], room_line[ROOM_SIZE];
    
    // Step 1: Get Name
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step1[] = {"Name:", ">> "};
        ui_print_menu("Add Doctor", step1, 2, UI_SIZE);
        utils_get_string(new_doctor.name, NAME_SIZE);
        if (utils_is_valid_name(new_doctor.name)) {
            utils_fix_name(new_doctor.name);
            break;
        }
        ui_print_error("Invalid name! Please try again.");
        ui_pause();
    }
    
    // Step 2: Get Phone
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        snprintf(name_line, sizeof(name_line), "Name: %s", new_doctor.name);
        const char* step2[] = {name_line, "Phone (11 digits):", ">> "};
        ui_print_menu("Add Doctor", step2, 3, UI_SIZE);
        utils_get_string(new_doctor.phone, PHONE_SIZE);
        if (utils_is_valid_phone(new_doctor.phone)) {
            break;
        }
        ui_print_error("Invalid phone! Please try again.");
        ui_pause();
    }
    
    // Step 3: Get Email
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        snprintf(phone_line, sizeof(phone_line), "Phone: %s", new_doctor.phone);
        const char* step3[] = {name_line, phone_line, "Email:", ">> "};
        ui_print_menu("Add Doctor", step3, 4, UI_SIZE);
        utils_get_string(new_doctor.email, EMAIL_SIZE);
        if (utils_is_valid_email(new_doctor.email)) {
            break;
        }
        ui_print_error("Invalid email! Please try again.");
        ui_pause();
    }
    
    // Step 4: Get Specialization
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        snprintf(email_line, sizeof(email_line), "Email: %s", new_doctor.email);
        const char* step4[] = {name_line, phone_line, email_line, "Specialization:", ">> "};
        ui_print_menu("Add Doctor", step4, 5, UI_SIZE);
        utils_get_string(new_doctor.specialization, SPEC_SIZE);
        if (strlen(new_doctor.specialization) > 0) {
            utils_fix_name(new_doctor.specialization);
            break;
        }
        ui_print_error("Specialization cannot be empty!");
        ui_pause();
    }
    
    // Step 5: Auto-generate Room Number and Confirm
    new_doctor.room_number = 100 + doctor_count + 1;
    snprintf(spec_line, sizeof(spec_line), "Specialization: %s", new_doctor.specialization);
    snprintf(room_line, sizeof(room_line), "Room Number: %d (auto-assigned)", new_doctor.room_number);
    
    const char* step5[] = 
    {
        name_line, phone_line, email_line, spec_line, room_line,
        "Confirm (Y/N):", ">> "
    };
    ui_clear_screen();
    ui_print_banner();
    ui_print_menu("Add Doctor", step5, 7, UI_SIZE);
    char confirm = utils_get_char();
    if (confirm != 'Y' && confirm != 'y') {
        ui_print_info("Doctor addition cancelled.");
        ui_pause();
        return;
    }
    
    // Add to array
    doctors[doctor_count] = new_doctor;
    doctor_count++;
    doctor_available++;
    
    ui_clear_screen();
    ui_print_banner();

    char id_line[70];
    snprintf(id_line, sizeof(id_line), "Doctor ID: %d", new_doctor.id);
    const char* success_items[] = 
    {
        id_line, name_line, phone_line, 
        email_line, spec_line, room_line,
        "Doctor added successfully!"
    };
    ui_print_menu("Doctor Added", success_items, 7, UI_SIZE);
    ui_pause();
    
}

void doctor_view_all() {
    
    int count = 0;
    ui_clear_screen();
    ui_print_banner();

    if (doctor_available == 0 || doctor_count == 0) {
        const char* menu_items[] = {"No doctors found!"};
        ui_print_menu("View All Doctors", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }

    for (int i = 0; i < doctor_count; i++) {
        if (doctors[i].is_active) {
            ui_print_doctor(doctors[i], count++);
        }
    }
    ui_pause();
}

void doctor_view_one() {
    
    int count = 0;

    if (doctor_available == 0) {
        ui_clear_screen();
        ui_print_banner();
        const char* menu_items[] = {"No doctors found!"};
        ui_print_menu("View All Doctors", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }
    
    for (int i = 0; i < doctor_count; i++) {
        ui_clear_screen();
        ui_print_banner();
        if (doctors[i].is_active) {
            ui_print_doctor(doctors[i], count++);
            ui_pause();
        }
    }
}

void doctor_view() {
    
    const char* menu_items[] = 
    {
        "All at once",
        "One after another",
        "Back to Doctor Menu",
        ">> "
    };
    
    int choice;
    do {
        ui_clear_screen();
        ui_print_banner();
        ui_print_menu("View Doctors", menu_items, 4, UI_SIZE);
        choice = utils_get_int();
        switch (choice) {
            case 1:
                doctor_view_all();
                break;
            case 2:
                doctor_view_one();
                break;
            case 3:
                ui_print_info("Returning to doctor menu...");
                ui_pause();
                return;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
                break;
        }
    } while (choice != 3);
}

void doctor_search_by_id(void) {
    
    int id;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Enter ID: ",
            ">> "
        };
        
        ui_print_menu("Search Doctor", menu_items, 2, UI_SIZE);
        id = utils_get_int();

        if (!utils_is_valid_id(id, ROLE_DOCTOR)) {
            ui_print_error("Invalid ID!");
            ui_pause();
            continue;
        }
        for (int i = 0; i < doctor_count; i++) {
            if (doctors[i].id == id) {
                ui_clear_screen();
                ui_print_banner();
                
                ui_print_doctor(doctors[i], (doctors[i].id - DOCTOR_ID_START));
                ui_pause();
                return;
            }
        }
        ui_print_error("Doctor not found!");
        ui_pause();
        return;
    } while (1);

}

void doctor_search_by_name(void) {
    char name[NAME_SIZE];
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Enter name: ",
            ">> "
        };
        
        ui_print_menu("Search Doctor", menu_items, 2, UI_SIZE);
        utils_get_string(name, NAME_SIZE);

        if (!utils_is_valid_name(name)) {
            ui_print_error("Invalid name!");
            ui_pause();
            continue;
        }

        utils_fix_name(name);
        for (int i = 0; i < doctor_count; i++) {
            if (strcmp(doctors[i].name, name) == 0) {
                ui_clear_screen();
                ui_print_banner();
                
                ui_print_doctor(doctors[i], (doctors[i].id - DOCTOR_ID_START));
                ui_pause();
                return;
            }
        }
        ui_print_error("Doctor not found!");
        ui_pause();
        return;
    } while (1);
}

void doctor_search_by_phone(void) {
    char phone[PHONE_SIZE];
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Enter phone: ",
            ">> "
        };
        
        ui_print_menu("Search Doctor", menu_items, 2, UI_SIZE);
        utils_get_string(phone, PHONE_SIZE);

        if (!utils_is_valid_phone(phone)) {
            ui_print_error("Invalid phone!");
            ui_pause();
            continue;
        }
        for (int i = 0; i < doctor_count; i++) {
            if (strcmp(doctors[i].phone, phone) == 0) {
                ui_clear_screen();
                ui_print_banner();

                ui_print_doctor(doctors[i], (doctors[i].id - DOCTOR_ID_START));
                ui_pause();
                return;
            }
        }
        ui_print_error("Doctor not found!");
        ui_pause();
        return;
    } while (1);
}

void doctor_search_by(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Search by doctor ID",
            "Search by doctor name",
            "Search by doctor phone",
            "Back to Doctor Menu",
            "Enter your choice: "
        };
        
        ui_print_menu("Search Doctor", menu_items, 5, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                doctor_search_by_id();
                break;
            case 2:
                doctor_search_by_name();
                break;
            case 3:
                doctor_search_by_phone();
                break;
            case 4:
                ui_print_info("Returning to doctor menu...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice! Please try again.");
                ui_pause();
        }
    } while (choice != 4);
}

int doctor_search_id (int id) {
    for (int i = 0; i < doctor_count; i++) {
        if (doctors[i].id == id) {
            return i;
        }
    }
    return -1;
}

void doctor_update_name(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();

    const char* menu[] = {
        menu_items[0],
        "Enter new name: ",
        ">> "
    };
            
    char name[NAME_SIZE];
    ui_print_menu("Update Doctor", menu, 3, UI_SIZE);
    utils_get_string(name, NAME_SIZE);
    utils_fix_name(name);

    if (!utils_is_valid_name(name)) {
        ui_print_error("Invalid name! Could not update.");
        ui_pause();
        return;
    }
    doctors[index].name[0] = '\0';
    strncpy(doctors[index].name, name, NAME_SIZE);
}

void doctor_update_phone(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[1],
        "Enter new phone: ",
        ">> "
    };
            
    char phone[PHONE_SIZE];
    ui_print_menu("Update Doctor", menu, 3, UI_SIZE);
    utils_get_string(phone, PHONE_SIZE);

    if (!utils_is_valid_phone(phone)) {
        ui_print_error("Invalid phone! Could not update.");
        ui_pause();
        return;
    }
    doctors[index].phone[0] = '\0';
    strncpy(doctors[index].phone, phone, PHONE_SIZE);
}

void doctor_update_email(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[2],
        "Enter new email: ",
        ">> "
    };
            
    char email[EMAIL_SIZE];
    ui_print_menu("Update Doctor", menu, 3, UI_SIZE);
    utils_get_string(email, EMAIL_SIZE);

    if (!utils_is_valid_email(email)) {
        ui_print_error("Invalid email! Could not update.");
        ui_pause();
        return;
    }
    doctors[index].email[0] = '\0';
    strncpy(doctors[index].email, email, EMAIL_SIZE);
}

void doctor_update_specialization(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[3],
        "Enter new specialization: ",
        ">> "
    };
            
    char spec[SPEC_SIZE];
    ui_print_menu("Update Doctor", menu, 3, UI_SIZE);
    utils_get_string(spec, SPEC_SIZE);

    if (strlen(spec) == 0) {
        ui_print_error("Specialization cannot be empty! Could not update.");
        ui_pause();
        return;
    }
    utils_fix_name(spec);
    doctors[index].specialization[0] = '\0';
    strncpy(doctors[index].specialization, spec, SPEC_SIZE);
}

void doctor_update_room(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[4],
        "Enter new room number: ",
        ">> "
    };
            
    ui_print_menu("Update Doctor", menu, 3, UI_SIZE);
    int room = utils_get_int();

    if (room <= 0 || room >= 1000) {
        ui_print_error("Invalid room number! Could not update.");
        ui_pause();
        return;
    }
    doctors[index].room_number = room;
}

void doctor_update_availability(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[5],
        "Set availability (1 for available, 2 for unavailable): ",
        ">> "
    };
    
    int input;
    ui_print_menu("Update Doctor", menu, 3, UI_SIZE);
    input = utils_get_int();

    if (input == 1) {
        doctors[index].is_available = true;
    } else if (input == 2) {
        doctors[index].is_available = false;
    } else {
        ui_print_error("Invalid input! Could not update.");
        ui_pause();
    }
}

void doctor_update_status(const char* menu_items[], int index) {
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu[] = {
        menu_items[6],
        "Enter new status: (1 for active, 2 for inactive) ",
        ">> "
    };
    
    bool status;
    int input;
    ui_print_menu("Update Doctor", menu, 3, UI_SIZE);
    input = utils_get_int();

    if (input == 1) {
        status = true;
    } else if (input == 2) {
        status = false;
    }
    doctors[index].is_active = status;
}

void doctor_update_using_id() {
    ui_clear_screen();
    ui_print_banner();

    int id;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* enter_id_items[] = {
            "Enter doctor ID: (0 to go back) ",
            ">> "
        };
        
        ui_print_menu("Update Doctor", enter_id_items, 2, UI_SIZE);
        id = utils_get_int();
        
        if (id == 0) return;

        if (!utils_is_valid_id(id, ROLE_DOCTOR)) {
            ui_print_error("Invalid ID!");
            ui_pause();
        } else {
            ui_print_info("Doctor found!");
            ui_pause();
            break;
        }
    } while (1);

    int index = doctor_search_id(id);
    if (index == -1) return;

    char name_line[NAME_LINE_SIZE], phone_line[PHONE_LINE_SIZE], email_line[70], spec_line[70], room_line[70], avail_line[70], status_line[STATUS_LINE_SIZE];

    snprintf(name_line, NAME_LINE_SIZE, "Name: %s", doctors[index].name);
    snprintf(phone_line, PHONE_LINE_SIZE, "Phone: %s", doctors[index].phone);
    snprintf(email_line, sizeof(email_line), "Email: %s", doctors[index].email);
    snprintf(spec_line, sizeof(spec_line), "Specialization: %s", doctors[index].specialization);
    snprintf(room_line, sizeof(room_line), "Room Number: %d", doctors[index].room_number);

    int doctor_id = doctors[index].id;

    if (doctors[index].is_available) {
        snprintf(avail_line, sizeof(avail_line), "Availability: Available");
    } else {
        snprintf(avail_line, sizeof(avail_line), "Availability: Unavailable");
    }
    if (doctors[index].is_active) {
        snprintf(status_line, STATUS_LINE_SIZE, "Status: Active");
    } else {
        snprintf(status_line, STATUS_LINE_SIZE, "Status: Inactive");
    }

    const char* menu_items[] = {
        name_line,
        phone_line,
        email_line,
        spec_line,
        room_line,
        avail_line,
        "Go back",
        "Enter which field to update: "
    };
    
    char title[50];
    snprintf(title, 50, "Update Doctor | ID: %d", doctor_id);

    ui_clear_screen();
    ui_print_banner();
    ui_print_menu(title, menu_items, 8, UI_SIZE);

    int choice = utils_get_int();
    
    switch (choice) {
        case 1:
            doctor_update_name(menu_items, index);
            break;
        case 2:
            doctor_update_phone(menu_items, index);
            break;
        case 3:
            doctor_update_email(menu_items, index);
            break;
        case 4:
            doctor_update_specialization(menu_items, index);
            break;
        case 5:
            doctor_update_room(menu_items, index);
            break;
        case 6:
            doctor_update_availability(menu_items, index);
            break;
        case 7:
            ui_print_info("Returning to doctor menu...");
            ui_pause();
            break;
        default:
            ui_print_error("Invalid choice! Please try again.");
            ui_pause();
            break;
    }
}

void doctor_discharge() {
    int id;
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        
        const char* enter_id_items[] = {
            "Enter doctor ID (0 to cancel): ",
            ">> "
        };
        
        ui_print_menu("Discharge Doctor", enter_id_items, 2, UI_SIZE);
        id = utils_get_int();

        if (id == 0) {
            ui_print_info("User Pressed 0. \nCanceling deletion...");
            ui_pause();
            return;
        }

        if (!utils_is_valid_id(id, ROLE_DOCTOR)) {
            ui_print_error("Invalid ID!");
            ui_pause();
            continue;
        }
        break;
    }

    int index = doctor_search_id(id);
    if (index == -1) {
        ui_print_error("Doctor not found!");
        ui_pause();
        return;
    }

    ui_clear_screen();
    ui_print_banner();
    ui_print_doctor(doctors[index], index);
    
    const char* menu[] = {
        "Confirm Discharge",
        "Cancel",
        ">> "
    };
    
    ui_print_menu("Discharge Doctor", menu, 3, UI_SIZE);
    int input = utils_get_int();

    if (input == 1) {
        doctors[index].is_active = false;
        ui_print_success("Doctor discharged successfully!");
        doctor_available--;
        doctor_unavailable++;
        ui_pause();
    } else {
        ui_print_info("Discharge cancelled.");
        ui_pause();
    }
}

void doctor_view_discharged(void) {
    int count = 0;
    ui_clear_screen();
    ui_print_banner();

    if (doctor_unavailable == 0) {
        const char* menu_items[] = {"No discharged doctors found!"};
        ui_print_menu("Discharged Doctors", menu_items, 1, UI_SIZE);
        ui_pause();
        return;
    }

    for (int i = 0; i < doctor_count; i++) {
        if (!doctors[i].is_active) {
            ui_print_doctor(doctors[i], count++);
        }
    }
    ui_pause();
}

void doctor_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Add Doctor",
            "View Active Doctors",
            "View Discharged Doctors",
            "Search Doctor",
            "Update Doctor",
            "Discharge Doctor",
            "Back to Main Menu",
            "Enter your choice: "
        };
        
        ui_print_menu("Doctor Management", menu_items, 8, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                doctor_add();
                doctor_save_to_file();
                break;
            case 2:
                doctor_view();
                break;
            case 3:
                doctor_view_discharged();
                break;
            case 4:
                doctor_search_by();
                break;
            case 5:
                doctor_update_using_id();
                doctor_save_to_file();
                break;
            case 6:
                doctor_discharge();
                doctor_save_to_file();
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
