/**
 * @file ui.c
 * @brief User interface functions for Healthcare Management System
 * 
 * This file contains the implementation of user interface functions
 * used throughout the HMS application.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/ui.h"
#include "../include/utils.h"


void ui_clear_screen(void) {
    #ifdef _WIN32
        system("cls");
        #else
        system("clear");
    #endif
}

void ui_pause(void) {
    printf("\nPress enter to continue...");
    getchar();
}

void ui_print_header(const char *title) {
    printf(BG_NEON_PURPLE BOLD "  %s  " RESET, title);
}

void ui_print_success(const char *message) {
    printf(SOFT_GREEN "\n%s" RESET , message);
}

void ui_print_error(const char *message) {
    printf(SOFT_RED "\n%s" RESET , message);
}

void ui_print_warning(const char *message) {
    printf(SOFT_YELLOW "\n%s" RESET , message);
}

void ui_print_info(const char *message) {
    printf(SOFT_BLUE "\n%s" RESET , message);
}


void ui_print_banner(void){
    unsigned char b = 219;  // █ Full block character
    
    char* hms = 
    "#####################################\n"
    "#                                   #\n"
    "#        X  X  X   X  XXXX          #\n"
    "#        X  X  XX XX  X             #\n"
    "#        XXXX  X X X  XXXX          #\n"
    "#        X  X  X   X     X          #\n"
    "#        X  X  X   X  XXXX          #\n"
    "#                                   #\n"
    "#    HEALTHCARE MANAGEMENT SYSTEM   #\n"
    "#                                   #\n"
    "#####################################\n";
    
    printf("\n");
    
    while (*hms) {
        if (*hms == 'X') {
            printf(BRIGHT_RED "%c%c" RESET, b, b);
        } 
        else if (*hms == '#') {
            printf(SOFT_GRAY "%c%c" RESET, b, b);
        }
        else if (*hms == '\n') {
            printf("\n");
        } 
        else if (isalpha(*hms)){
            printf(BOLD CYAN "%c" RESET " ", *hms);
        } 
        else {
            printf("  ");
        }
        hms++;
    }
    printf("\n");
}

void ui_print_menu
    (
    const char *title, 
    const char *items[], 
    int item_count, 
    int box_width
    ) {
    unsigned char h = 205;  // ═
    unsigned char v = 186;  // ║
    unsigned char tl = 201; // ╔
    unsigned char tr = 187; // ╗
    unsigned char bl = 200; // ╚
    unsigned char br = 188; // ╝
    
    printf(BRIGHT_BLACK "%c", tl);
    for (int i = 0; i < box_width; i++) printf("%c", h);
    printf("%c" RESET "\n", tr);

    char title_upper[100];
    strncpy(title_upper, title, sizeof(title_upper) - 1);
    title_upper[sizeof(title_upper) - 1] = '\0';
    utils_str_to_upper(title_upper);
    
    int title_len = strlen(title_upper) + 4;
    int title_padding = (box_width - title_len) / 2;
    printf(BRIGHT_BLACK "%c" RESET, v);
    for (int i = 0; i < title_padding; i++) printf(" ");
    ui_print_header(title_upper);
    for (int i = 0; i < box_width - title_padding - title_len; i++) printf(" ");
    printf(BRIGHT_BLACK "%c" RESET "\n", v);
    
    printf(BRIGHT_BLACK "%c" RESET, v);
    for (int i = 0; i < box_width; i++) printf(" ");
    printf(BRIGHT_BLACK "%c" RESET "\n", v);
    
    for (int i = 0; i < item_count - 1; i++) {
        int item_len = strlen(items[i]);
        printf(BRIGHT_BLACK "%c" RESET "  " SOFT_YELLOW BOLD "%d. %s" RESET, v, i + 1, items[i]);
        for (int j = 0; j < box_width - item_len - 5; j++) printf(" ");
        printf(BRIGHT_BLACK "%c" RESET "\n", v);
    }
    
    printf(BRIGHT_BLACK "%c" RESET, v);
    for (int i = 0; i < box_width; i++) printf(" ");
    printf(BRIGHT_BLACK "%c" RESET "\n", v);
    printf(BRIGHT_BLACK "%c", bl);
    for (int i = 0; i < box_width; i++) printf("%c", h);
    printf("%c" RESET "\n\n", br);
    
    printf(BOLD SOFT_GREEN "%s" RESET, items[item_count - 1]);
}

void ui_print_patient(Patient patient, int index) {

    char id_line[ID_LINE_SIZE];
    snprintf(id_line, sizeof(id_line), "Patient ID: %d", patient.id);

    char name_line[NAME_LINE_SIZE];
    snprintf(name_line, sizeof(name_line), "Name: %s", patient.name);

    char age_line[AGE_LINE_SIZE];
    snprintf(age_line, sizeof(age_line), "Age: %d", patient.age);

    char gender_line[GENDER_LINE_SIZE];
    snprintf(gender_line, sizeof(gender_line), "Gender: %s", patient.gender == MALE ? "Male" : "Female");

    char phone_line[PHONE_LINE_SIZE];
    snprintf(phone_line, sizeof(phone_line), "Phone: %s", patient.phone);

    char address_line[ADDRESS_LINE_SIZE];
    snprintf(address_line, sizeof(address_line), "Address: %s", patient.address);

    char blood_group_line[BLOOD_LINE_SIZE];
    snprintf(blood_group_line, sizeof(blood_group_line), "Blood Group: %s", patient.blood_group);

    char status_line[STATUS_LINE_SIZE];
    snprintf(status_line, sizeof(status_line), "Status: %s", patient.is_active ? "Active" : "Inactive");

    const char* items[] = {
        id_line,
        name_line,
        age_line,
        gender_line,
        phone_line,
        address_line,
        blood_group_line,
        status_line,
        ""
    };

    char title[70];
    snprintf(title, sizeof(title), "Patient %d", index + 1);
    ui_print_menu(title, items, 9, 72);
}

void ui_print_doctor(Doctor doctor, int index) {

    char id_line[70];
    snprintf(id_line, sizeof(id_line), "Doctor ID: %d", doctor.id);

    char name_line[70];
    snprintf(name_line, sizeof(name_line), "Name: %s", doctor.name);

    char phone_line[70];
    snprintf(phone_line, sizeof(phone_line), "Phone: %s", doctor.phone);

    char email_line[70];
    snprintf(email_line, sizeof(email_line), "Email: %s", doctor.email);

    char spec_line[70];
    snprintf(spec_line, sizeof(spec_line), "Specialization: %s", doctor.specialization);

    char room_line[70];
    snprintf(room_line, sizeof(room_line), "Room Number: %d", doctor.room_number);

    char avail_line[70];
    snprintf(avail_line, sizeof(avail_line), "Available: %s", doctor.is_available ? "Yes" : "No");

    char status_line[70];
    snprintf(status_line, sizeof(status_line), "Status: %s", doctor.is_active ? "Active" : "Inactive");

    const char* items[] = {
        id_line,
        name_line,
        phone_line,
        email_line,
        spec_line,
        room_line,
        avail_line,
        status_line,
        ""
    };

    char title[70];
    snprintf(title, sizeof(title), "Doctor %d", index + 1);
    ui_print_menu(title, items, 9, 72);
}