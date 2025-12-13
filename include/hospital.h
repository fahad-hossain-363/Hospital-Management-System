/**
 * @file hospital.h
 * @brief Core data structures and definitions for Healthcare Management System
 * 
 * This header defines all shared structures, enumerations, and constants
 * used throughout the HMS application.
 */

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdbool.h>

/*
 *==========================================================================
 *                              CONSTANTS
 *==========================================================================
 */

#define UI_SIZE         72

#define MAX_PATIENTS    100
#define MAX_DOCTORS     20
#define MAX_RECEPTIONISTS 20
#define MAX_USERS       50
#define MAX_APPOINTMENTS 200

#define NAME_SIZE       50
#define PHONE_SIZE      15
#define EMAIL_SIZE      50
#define ADDRESS_SIZE    100
#define SPEC_SIZE       30      /* Specialization */
#define BLOOD_SIZE      5       /* Blood group */
#define AGE_SIZE        5       /* Age */
#define USERNAME_SIZE   30
#define PASSWORD_SIZE   50
#define GENDER_SIZE     10
#define STATUS_SIZE     10
#define ROOM_SIZE       10

#define ID_LINE_SIZE        20
#define NAME_LINE_SIZE      NAME_SIZE + 20
#define PHONE_LINE_SIZE     PHONE_SIZE + 20
#define ADDRESS_LINE_SIZE   ADDRESS_SIZE + 20
#define BLOOD_LINE_SIZE     BLOOD_SIZE + 20
#define GENDER_LINE_SIZE    GENDER_SIZE + 20
#define STATUS_LINE_SIZE    STATUS_SIZE + 20
#define SPEC_LINE_SIZE      SPEC_SIZE + 20
#define ROOM_LINE_SIZE      ROOM_SIZE + 20
#define AGE_LINE_SIZE       AGE_SIZE + 20
#define PHONE_LINE_SIZE     PHONE_SIZE + 20
#define EMAIL_LINE_SIZE     EMAIL_SIZE + 20
#define BLOOD_LINE_SIZE     BLOOD_SIZE + 20
#define GENDER_LINE_SIZE    GENDER_SIZE + 20
#define STATUS_LINE_SIZE    STATUS_SIZE + 20

#define DATA_DIR            "data/"
#define PATIENTS_FILE       "data/patients.dat"
#define DOCTORS_FILE        "data/doctors.dat"
#define RECEPTIONISTS_FILE  "data/receptionists.dat"
#define USERS_FILE          "data/users.dat"
#define APPOINTMENTS_FILE   "data/appointments.dat"

#define PATIENT_ID_START      1001
#define DOCTOR_ID_START       2001
#define ADMIN_ID_START        3001
#define RECEPTIONIST_ID_START 4001
#define APPOINTMENT_ID_START  5001

#define REASON_SIZE     100
#define TIME_SIZE       10
#define DATE_SIZE       15


#define VERSION "1.0.0"

/*
 *==========================================================================
 *                              ENUMERATIONS
 *==========================================================================
 */

typedef enum {
    ROLE_ADMIN,
    ROLE_DOCTOR,
    ROLE_RECEPTIONIST,
    ROLE_PATIENT
} UserRole;

typedef enum { 
    MALE, 
    FEMALE 
} Gender;

typedef enum {
    APPT_PENDING,
    APPT_CONFIRMED,
    APPT_COMPLETED,
    APPT_CANCELLED
} AppointmentStatus;

/*
 *==========================================================================
 *                              STRUCTURES
 *==========================================================================
 */

typedef struct {
    int id;
    char name[NAME_SIZE];
    int age;
    Gender gender;
    char phone[PHONE_SIZE];
    char address[ADDRESS_SIZE];     
    char blood_group[BLOOD_SIZE];   
    bool is_active;
} Patient;

typedef struct {
    int id;
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    char email[EMAIL_SIZE];
    char specialization[SPEC_SIZE];
    int room_number;
    bool is_available;
    bool is_active;
} Doctor;

typedef struct {
    int id;
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    UserRole role;
    bool is_active;
} User;

typedef struct {
    int id;
    int patient_id;
    int doctor_id;
    char date[DATE_SIZE];           // "DD-MM-YYYY"
    char time_slot[TIME_SIZE];      // "10:00 AM"
    char reason[REASON_SIZE];
    AppointmentStatus status;
} Appointment;

typedef struct {
    int id;
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    char email[EMAIL_SIZE];
    bool is_available;
    bool is_active;
} Receptionist;

/*
 *==========================================================================
 *                          GLOBAL DECLARATIONS
 *==========================================================================
 */

/* Global declarations for data arrays */
extern Patient patients[MAX_PATIENTS];
extern Doctor doctors[MAX_DOCTORS];
extern Receptionist receptionists[MAX_RECEPTIONISTS];
extern User users[MAX_USERS];
extern Appointment appointments[MAX_APPOINTMENTS];

/* Count variables */
extern int patient_count;
extern int doctor_count;
extern int receptionist_count;
extern int user_count;
extern int patient_available;
extern int patient_unavailable;
extern int doctor_available;
extern int doctor_unavailable;
extern int receptionist_available;
extern int receptionist_unavailable;
extern int user_available;
extern int user_unavailable;
extern int appointment_count;

/* Current user */
extern User* current_user;

/**
 * Initialize the hospital system by loading all data.
 */
void hospital_init(void);

/**
 * Display about information.
 */
void show_about(void);

/**
 * Display help information.
 */
void print_help(const char* program_name);

/**
 * Display version information.
 */
void print_version(void);

/**
 * Ensure data directory exists.
 */
void ensure_data_dir(void);

#endif