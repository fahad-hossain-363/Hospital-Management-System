#include <stdio.h>
#include <stdbool.h>
#include "../include/utils.h"

int test_fix_name() {
    char name[] = "aRVIN yEFAT oRiN";   
    char expected[] = "Arvin Yefat Orin";

    utils_fix_name(name);   

    int success = (strcmp(name, expected) == 0);

    printf("Input Fixed: %s | Expected: %s | Success: %d\n",
           name, expected, success);

    return success;
}

int main() {
    test_fix_name();
}