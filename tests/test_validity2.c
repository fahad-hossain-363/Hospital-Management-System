#include <stdio.h>
#include "../include/utils.h"
#include <stdbool.h>

int test_validate_valid_email() {
    char email[] = "test@example.com";   
    int expected = 1;

    int actual = utils_is_valid_email(email);
    int success = (actual == expected);

    printf("actual: %d, expected: %d, success: %d\n",
           actual, expected, success);

    return success;
}

int main() {
    test_validate_valid_email();
}