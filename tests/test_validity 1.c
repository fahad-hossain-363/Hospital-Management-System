#include <stdio.h>
#include "../include/utils.h"
#include <stdbool.h>

int test_validate_valid_blood() {
    char blood[] = "A+";   
    int expected = 1;

    int actual = utils_is_valid_blood_group(blood);
    int success = (actual == expected);

    printf("actual: %d, expected: %d, success: %d\n",
           actual, expected, success);

    return success;
}

int main() {
    test_validate_valid_blood();
}