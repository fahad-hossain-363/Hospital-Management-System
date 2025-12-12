/**
 * @file auth.h
 * @brief Authentication functions for Healthcare Management System
 */

#ifndef AUTH_H
#define AUTH_H

#include "hospital.h"

/**
 * Saves all users to binary file.
 * @return 0 on success, -1 on failure.
 */
int auth_save_to_file(void);

/**
 * Loads all users from binary file.
 * @return 0 on success, -1 if file doesn't exist.
 */
int auth_load_from_file(void);

/**
 * Registers a new user (admin only).
 */
void auth_register_user(void);

/**
 * Views all users (admin only).
 */
void auth_view_users(void);

/**
 * Creates default admin if no users exist.
 */
void auth_init_default_admin(void);

/**
 * User management menu (admin only).
 */
void auth_user_menu(void);

/**
 * Login with role-based authentication.
 * @param required_role The role to authenticate as.
 */
void auth_role_login(UserRole required_role);

/**
 * Login menu with role selection.
 */
void login_menu(void);

/**
 * Encrypts a password using XOR cipher.
 * @param password The password to encrypt.
 */
void encrypt(char* password);

/**
 * Decrypts a password using XOR cipher.
 * @param password The password to decrypt.
 */
void decrypt(char* password);

#endif