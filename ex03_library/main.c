// Including the required headers
#include <stdio.h>
#include "math_ops.h"

int main(int argc, char *argv[]) {
    int num1 = 5;
    int num2 = 4;

    // Using the square function from our library
    printf("The square of %d is %d\n", num1, square(num1));

    // Using the factorial function from our library
    printf("The factorial of %d is %d\n", num2, factorial(num2));

    return 0;
}
