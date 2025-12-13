/**
 * @file auth.c
 * @brief Authentication implementation for Healthcare Management System
 */

#include <stdio.h>
#include <string.h>
#include "../include/auth.h"
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/hospital.h"
#include "../include/receptionist.h"
#include "../include/admin.h"
#include "../include/doctor_portal.h"
#include "../include/doctor.h"

int auth_save_to_file(void) {
    FILE* file = fopen(USERS_FILE, "wb");
    if (file == NULL) {
        return -1;
    }
    if (fwrite(&user_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return -1;
    }
    if (fwrite(users, sizeof(User), user_count, file) != (size_t)user_count) {
        fclose(file);
        return -1;
    }
    fclose(file);
    return 0;
}

int auth_load_from_file(void) {
    FILE* file = fopen(USERS_FILE, "rb");
    if (file == NULL) {
        return -1;
    }
    if (fread(&user_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return -1;
    }
    if (user_count < 0 || user_count > MAX_USERS) {
        fclose(file);
        user_count = 0;
        return -1;
    }
    if (fread(users, sizeof(User), user_count, file) != (size_t)user_count) {
        fclose(file);
        user_count = 0;
        return -1;
    }
    fclose(file);
    return 0;
}

void auth_init_default_admin(void) {
    if (user_count == 0) {
        users[0].id = ADMIN_ID_START;
        strcpy(users[0].username, "admin");
        strcpy(users[0].password, "admin123");
        encrypt(users[0].password);
        users[0].role = ROLE_ADMIN;
        users[0].is_active = true;
        user_count = 1;
        auth_save_to_file();
    }
}

void auth_register_user(void) {
    if (user_count >= MAX_USERS) {
        ui_print_error("Maximum user limit reached!");
        ui_pause();
        return;
    }
    
    User new_user;
    Doctor new_doctor;
    char username_line[80], password_line[80], role_line[80];
    char name_line[NAME_LINE_SIZE], phone_line[PHONE_LINE_SIZE], email_line[EMAIL_LINE_SIZE];
    char spec_line[SPEC_LINE_SIZE], room_line[ROOM_LINE_SIZE];
    int selected_role = 0;
    
    // Step 1: Select role first
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step1[] = {
            "Admin",
            "Receptionist",
            "Doctor",
            ">> ",
        };
        ui_print_menu("Register User", step1, 4, UI_SIZE);
        selected_role = utils_get_int();
        
        switch (selected_role) {
            case 0:
                ui_print_info("Cancelled.");
                ui_pause();
                return;
            case 1:
                new_user.role = ROLE_ADMIN;
                snprintf(role_line, sizeof(role_line), "Role: Admin");
                new_user.id = ADMIN_ID_START + user_count;
                break;
            case 2:
                new_user.role = ROLE_RECEPTIONIST;
                snprintf(role_line, sizeof(role_line), "Role: Receptionist");
                new_user.id = RECEPTIONIST_ID_START + user_count;
                break;
            case 3:
                if (doctor_count >= MAX_DOCTORS) {
                    ui_print_error("Maximum doctor limit reached!");
                    ui_pause();
                    return;
                }
                new_user.role = ROLE_DOCTOR;
                snprintf(role_line, sizeof(role_line), "Role: Doctor");
                new_user.id = DOCTOR_ID_START + doctor_count;
                new_doctor.id = new_user.id;
                break;
            default:
                ui_print_error("Invalid role! Try again.");
                ui_pause();
                continue;
        }
        break;
    }
    
    // Step 2: Get username
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step2[] = {role_line, "Username:", ">> "};
        ui_print_menu("Register User", step2, 3, UI_SIZE);
        utils_get_string(new_user.username, USERNAME_SIZE);
        
        if (strlen(new_user.username) < 3) {
            ui_print_error("Username must be at least 3 characters!");
            ui_pause();
            continue;
        }
        
        // Check if username exists
        bool exists = false;
        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].username, new_user.username) == 0) {
                exists = true;
                break;
            }
        }
        if (exists) {
            ui_print_error("Username already exists!");
            ui_pause();
            continue;
        }
        
        snprintf(username_line, sizeof(username_line), "Username: %s", new_user.username);
        break;
    }
    
    // Step 3: Get password
    while (1) {
        ui_clear_screen();
        ui_print_banner();
        const char* step3[] = {role_line, username_line, "Password:", ">> "};
        ui_print_menu("Register User", step3, 4, UI_SIZE);
        utils_get_string(new_user.password, PASSWORD_SIZE);
        
        if (strlen(new_user.password) < 4) {
            ui_print_error("Password must be at least 4 characters!");
            ui_pause();
            continue;
        }
        snprintf(password_line, sizeof(password_line), "Password: ****");
        break;
    }
    
    // If Doctor, collect additional profile data
    if (selected_role == 3) {
        // Step 4: Get full name
        while (1) {
            ui_clear_screen();
            ui_print_banner();
            const char* step4[] = {role_line, username_line, "Full Name:", ">> "};
            ui_print_menu("Register Doctor", step4, 4, UI_SIZE);
            utils_get_string(new_doctor.name, NAME_SIZE);
            
            if (!utils_is_valid_name(new_doctor.name)) {
                ui_print_error("Invalid name!");
                ui_pause();
                continue;
            }
            utils_fix_name(new_doctor.name);
            snprintf(name_line, sizeof(name_line), "Name: %s", new_doctor.name);
            break;
        }
        
        // Step 5: Get phone
        while (1) {
            ui_clear_screen();
            ui_print_banner();
            const char* step5[] = {role_line, username_line, name_line, "Phone (11 digits):", ">> "};
            ui_print_menu("Register Doctor", step5, 5, UI_SIZE);
            utils_get_string(new_doctor.phone, PHONE_SIZE);
            
            if (!utils_is_valid_phone(new_doctor.phone)) {
                ui_print_error("Invalid phone!");
                ui_pause();
                continue;
            }
            snprintf(phone_line, sizeof(phone_line), "Phone: %s", new_doctor.phone);
            break;
        }
        
        // Step 6: Get email
        while (1) {
            ui_clear_screen();
            ui_print_banner();
            const char* step6[] = {role_line, username_line, name_line, phone_line, "Email:", ">> "};
            ui_print_menu("Register Doctor", step6, 6, UI_SIZE);
            utils_get_string(new_doctor.email, EMAIL_SIZE);
            
            if (strlen(new_doctor.email) < 5) {
                ui_print_error("Invalid email!");
                ui_pause();
                continue;
            }
            snprintf(email_line, sizeof(email_line), "Email: %s", new_doctor.email);
            break;
        }
        
        // Step 7: Get specialization
        while (1) {
            ui_clear_screen();
            ui_print_banner();
            const char* step7[] = {role_line, username_line, name_line, phone_line, email_line, "Specialization:", ">> "};
            ui_print_menu("Register Doctor", step7, 7, UI_SIZE);
            utils_get_string(new_doctor.specialization, SPEC_SIZE);
            
            if (strlen(new_doctor.specialization) < 2) {
                ui_print_error("Invalid specialization!");
                ui_pause();
                continue;
            }
            snprintf(spec_line, sizeof(spec_line), "Specialization: %s", new_doctor.specialization);
            break;
        }
        
        // Step 8: Get room number
        while (1) {
            ui_clear_screen();
            ui_print_banner();
            const char* step8[] = {role_line, name_line, phone_line, spec_line, "Room Number:", ">> "};
            ui_print_menu("Register Doctor", step8, 6, UI_SIZE);
            new_doctor.room_number = utils_get_int();
            
            if (new_doctor.room_number < 1 || new_doctor.room_number > 999) {
                ui_print_error("Invalid room number (1-999)!");
                ui_pause();
                continue;
            }
            snprintf(room_line, sizeof(room_line), "Room: %d", new_doctor.room_number);
            break;
        }
        
        new_doctor.is_available = true;
        new_doctor.is_active = true;
        
        // Confirm Doctor registration
        ui_clear_screen();
        ui_print_banner();
        const char* confirm_doc[] = {
            username_line,
            name_line,
            phone_line,
            email_line,
            spec_line,
            room_line,
            "Confirm registration? (Y/N):",
            ">> "
        };
        ui_print_menu("Confirm Doctor Registration", confirm_doc, 8, UI_SIZE);
        char confirm = utils_get_char();
        
        if (confirm != 'Y' && confirm != 'y') {
            ui_print_info("Registration cancelled.");
            ui_pause();
            return;
        }
        
        // Save doctor
        doctors[doctor_count] = new_doctor;
        doctor_count++;
        doctor_available++;
        doctor_save_to_file();
        
    } else {
        // Confirm Admin/Receptionist registration
        ui_clear_screen();
        ui_print_banner();
        const char* confirm_items[] = {
            username_line,
            role_line,
            "Confirm registration? (Y/N):",
            ">> "
        };
        ui_print_menu("Register User", confirm_items, 4, UI_SIZE);
        char confirm = utils_get_char();
        
        if (confirm != 'Y' && confirm != 'y') {
            ui_print_info("Registration cancelled.");
            ui_pause();
            return;
        }
    }
    
    // Save user credentials
    new_user.is_active = true;
    encrypt(new_user.password);  // Encryption
    users[user_count] = new_user;
    user_count++;
    auth_save_to_file();
    
    ui_print_success("User registered successfully!");
    ui_pause();
}

void auth_view_users(void) {
    ui_clear_screen();
    ui_print_banner();
    
    if (user_count == 0) {
        const char* empty[] = {"No users found!"};
        ui_print_menu("All Users", empty, 1, UI_SIZE);
        ui_pause();
        return;
    }
    
    for (int i = 0; i < user_count; i++) {
        char id_line[50], user_line[80], role_line[50], status_line[50];
        
        snprintf(id_line, sizeof(id_line), "User ID: %d", users[i].id);
        snprintf(user_line, sizeof(user_line), "Username: %s", users[i].username);
        
        const char* role_str;
        switch (users[i].role) {
            case ROLE_ADMIN: role_str = "Admin"; break;
            case ROLE_RECEPTIONIST: role_str = "Receptionist"; break;
            case ROLE_DOCTOR: role_str = "Doctor"; break;
            default: role_str = "Unknown";
        }
        snprintf(role_line, sizeof(role_line), "Role: %s", role_str);
        snprintf(status_line, sizeof(status_line), "Status: %s", 
                 users[i].is_active ? "Active" : "Inactive");
        
        const char* items[] = {id_line, user_line, role_line, status_line, ""};
        
        char title[50];
        snprintf(title, sizeof(title), "User %d", i + 1);
        ui_print_menu(title, items, 5, UI_SIZE);
    }
    ui_pause();
}

void auth_user_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Register New User",
            "View All Users",
            "Back",
            ">> "
        };
        
        ui_print_menu("User Management", menu_items, 4, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                auth_register_user();
                break;
            case 2:
                auth_view_users();
                break;
            case 3:
                ui_print_info("Returning...");
                ui_pause();
                break;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 3);
}

void auth_role_login(UserRole required_role) {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    
    // Get role name for display
    const char* role_name;
    switch (required_role) {
        case ROLE_ADMIN: 
            role_name = "Admin"; 
            break;
        case ROLE_RECEPTIONIST: 
            if (receptionist_count == 0) {
                ui_print_error("No receptionist account found!");
                ui_pause();
                return;
            }
            role_name = "Receptionist"; 
            break;
        case ROLE_DOCTOR: 
            if (doctor_count == 0) {
                ui_print_error("No doctor account found!");
                ui_pause();
                return;
            }
            role_name = "Doctor"; 
            break;
        default: 
            role_name = "User";
    }
    
    char title[50];
    snprintf(title, sizeof(title), "%s Login", role_name);
    
    // Get username
    ui_clear_screen();
    ui_print_banner();
    
    const char* menu_items[] = {
        "Username:",
        ">> "
    };
    ui_print_menu(title, menu_items, 2, UI_SIZE);
    utils_get_string(username, USERNAME_SIZE);
    
    // Get password
    ui_clear_screen();
    ui_print_banner();
    
    char user_line[80];
    snprintf(user_line, sizeof(user_line), "Username: %s", username);
    const char* pass_items[] = {
        user_line,
        "Password:",
        ">> "
    };
    ui_print_menu(title, pass_items, 3, UI_SIZE);
    utils_get_string(password, PASSWORD_SIZE);
    encrypt(password);  // Encryption for comparison
    
    // Find user with matching role
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0 &&
            users[i].is_active &&
            users[i].role == required_role) {
            
            current_user = &users[i];
            
            // Route to appropriate portal
            switch (required_role) {
                case ROLE_ADMIN:
                    admin_main_menu();
                    break;
                case ROLE_RECEPTIONIST:
                    receptionist_menu();
                    break;
                case ROLE_DOCTOR:
                    doctor_portal_menu(users[i].id, username);
                    break;
                default:
                    break;
            }
            
            current_user = NULL;
            return;
        }
    }
    
    char error_msg[80];
    snprintf(error_msg, sizeof(error_msg), "Invalid credentials or not a %s!", role_name);
    ui_print_error(error_msg);
    ui_pause();
}

void login_menu(void) {
    int choice;
    
    do {
        ui_clear_screen();
        ui_print_banner();
        
        const char* menu_items[] = {
            "Admin Login",
            "Receptionist Login",
            "Doctor Login",
            "Back",
            ">> "
        };
        
        ui_print_menu("Login", menu_items, 5, UI_SIZE);
        choice = utils_get_int();
        
        switch (choice) {
            case 1:
                auth_role_login(ROLE_ADMIN);
                break;
            case 2:
                auth_role_login(ROLE_RECEPTIONIST);
                break;
            case 3:
                auth_role_login(ROLE_DOCTOR);
                break;
            case 4:
                return;
            default:
                ui_print_error("Invalid choice!");
                ui_pause();
        }
    } while (choice != 4);
}

void encrypt(char* password) {
    for (int i = 0; password[i] != '\0'; i++) {
        password[i] = password[i] ^ 1;
    }
}

void decrypt(char* password) {
    encrypt(password);
}
