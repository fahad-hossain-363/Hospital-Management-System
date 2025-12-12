#include <stdio.h>
#include "../include/utils.h"
#include <stdbool.h>

int test_validate_id() {
    int id = 32;                   
    UserRole role = ROLE_PATIENT;  
    int expected = 0;              

    int actual = utils_is_valid_id(id, role);
    int success = (actual == expected);

    printf("ID: %d | Role: PATIENT | Actual: %d | Expected: %d | Success: %d\n",
           id, actual, expected, success);

    return success;
}

int main() {
    test_validate_id();
}