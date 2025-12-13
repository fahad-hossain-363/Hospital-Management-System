#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

void test_utils_get_int() {
    printf("Enter an integer: ");
    int expected = 5;
    int actual = utils_get_int();
    int success = (actual == expected);
    printf("  Expected: %d\n", expected);
    printf("  Actual:   %d\n", actual);
    printf("  Success:  %s\n\n", success ? "Yes" : "No");
}

void test_utils_get_char() {
    printf("Enter a character: ");
    char expected = 'c';
    char actual = utils_get_char();
    int success = (actual == expected);
    printf("  Expected: %c\n", expected);
    printf("  Actual:   %c\n", actual);
    printf("  Success:  %s\n\n", success ? "Yes" : "No");
}

void test_utils_get_float() {
    printf("Enter a float: ");
    float expected = 3.14;
    float actual = utils_get_float();
    int success = (actual >= 3.13 && actual <= 3.15);
    printf("  Expected: %.2f\n", expected);
    printf("  Actual:   %.2f\n", actual);
    printf("  Success:  %s\n\n", success ? "Yes" : "No");
}

void test_utils_get_double() {
    printf("Enter a double: ");
    double expected = 3.141593;
    double actual = utils_get_double();
    int success = (actual >= 3.141592 && actual <= 3.141594);
    printf("  Expected: %.6f\n", expected);
    printf("  Actual:   %.6f\n", actual);
    printf("  Success:  %s\n\n", success ? "Yes" : "No");
}

void test_utils_get_string() {
    printf("Enter a string: ");
    char expected[] = "happy birthday";
    char actual[50];
    utils_get_string(actual, 50);
    int success = (strcmp(actual, expected) == 0);
    printf("  Expected: %s\n", expected);
    printf("  Actual:   %s\n", actual);
    printf("  Success:  %s\n\n", success ? "Yes" : "No");
}

void test_utils_is_valid_phone() {
    printf("Testing utils_is_valid_phone():\n\n");
    
    char *phone1 = "01315648613";
    int expected1 = 1, actual1 = utils_is_valid_phone(phone1);
    printf("  Input:    %s\n", phone1);
    printf("  Expected: %s\n", expected1 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual1 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected1 == actual1) ? "Yes" : "No");
    
    char *phone2 = "1234567890";
    int expected2 = 0, actual2 = utils_is_valid_phone(phone2);
    printf("  Input:    %s\n", phone2);
    printf("  Expected: %s\n", expected2 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual2 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected2 == actual2) ? "Yes" : "No");
}

void test_utils_is_valid_email() {
    printf("Testing utils_is_valid_email():\n\n");
    
    char *email1 = "this.is.an.email@gmail.com";
    int expected1 = 1, actual1 = utils_is_valid_email(email1);
    printf("  Input:    %s\n", email1);
    printf("  Expected: %s\n", expected1 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual1 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected1 == actual1) ? "Yes" : "No");
    
    char *email2 = "noatsign.com";
    int expected2 = 0, actual2 = utils_is_valid_email(email2);
    printf("  Input:    %s\n", email2);
    printf("  Expected: %s\n", expected2 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual2 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected2 == actual2) ? "Yes" : "No");
}

void test_utils_str_to_upper() {
    printf("Testing utils_str_to_upper():\n\n");
    
    char input1[] = "hello world";
    char expected1[] = "HELLO WORLD";
    char *actual1 = utils_str_to_upper(input1);
    int success1 = (strcmp(actual1, expected1) == 0);
    printf("  Input:    hello world\n");
    printf("  Expected: %s\n", expected1);
    printf("  Actual:   %s\n", actual1);
    printf("  Success:  %s\n\n", success1 ? "Yes" : "No");
    
    char input2[] = "Test123";
    char expected2[] = "TEST123";
    char *actual2 = utils_str_to_upper(input2);
    int success2 = (strcmp(actual2, expected2) == 0);
    printf("  Input:    Test123\n");
    printf("  Expected: %s\n", expected2);
    printf("  Actual:   %s\n", actual2);
    printf("  Success:  %s\n\n", success2 ? "Yes" : "No");
}

void test_utils_is_valid_blood_group() {
    printf("Testing utils_is_valid_blood_group():\n\n");
    
    char *blood1 = "A+";
    int expected1 = 1, actual1 = utils_is_valid_blood_group(blood1);
    printf("  Input:    %s\n", blood1);
    printf("  Expected: %s\n", expected1 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual1 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected1 == actual1) ? "Yes" : "No");
    
    char *blood2 = "AB-";
    int expected2 = 1, actual2 = utils_is_valid_blood_group(blood2);
    printf("  Input:    %s\n", blood2);
    printf("  Expected: %s\n", expected2 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual2 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected2 == actual2) ? "Yes" : "No");
    
    char *blood3 = "X+";
    int expected3 = 0, actual3 = utils_is_valid_blood_group(blood3);
    printf("  Input:    %s\n", blood3);
    printf("  Expected: %s\n", expected3 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual3 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected3 == actual3) ? "Yes" : "No");
}

void test_utils_is_valid_address() {
    printf("Testing utils_is_valid_address():\n\n");
    
    char *addr1 = "123 Main Street, Dhaka";
    int expected1 = 1, actual1 = utils_is_valid_address(addr1);
    printf("  Input:    %s\n", addr1);
    printf("  Expected: %s\n", expected1 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual1 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected1 == actual1) ? "Yes" : "No");
    
    char *addr2 = "Apt. 5, Block B";
    int expected2 = 1, actual2 = utils_is_valid_address(addr2);
    printf("  Input:    %s\n", addr2);
    printf("  Expected: %s\n", expected2 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual2 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected2 == actual2) ? "Yes" : "No");
    
    char *addr3 = "Invalid@Address#123";
    int expected3 = 0, actual3 = utils_is_valid_address(addr3);
    printf("  Input:    %s\n", addr3);
    printf("  Expected: %s\n", expected3 ? "Valid" : "Invalid");
    printf("  Actual:   %s\n", actual3 ? "Valid" : "Invalid");
    printf("  Success:  %s\n\n", (expected3 == actual3) ? "Yes" : "No");
}

int main() {
    printf("=== UTILITY FUNCTIONS TEST ===\n\n");
    
    // test_utils_get_int();
    // test_utils_get_char();
    // test_utils_get_float();
    // test_utils_get_double();
    // test_utils_get_string();
    test_utils_is_valid_phone();
    test_utils_is_valid_email();
    test_utils_str_to_upper();
    test_utils_is_valid_blood_group();
    test_utils_is_valid_address();
    
    return 0;
}