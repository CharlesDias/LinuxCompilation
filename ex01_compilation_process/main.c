#include "pre_and_macros.h"

int main(int argc, char *argv[])
{
    // Using defined constants
    int var_1 = VAR_1;
    int var_2 = VAR_2;

    // Using function macros
    int var_3 = MAX(var_1, var_2);

    int number = 5;
    int result = SQUARE(number);

    // OS string
    char * str = OS_STRING;

    return 0;
}
