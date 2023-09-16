#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
    // printf needs the stdio library
    // libc is automatically linked
    printf("Hello World!\n");

    // sqrt needs the math library
    // we have to link it manually
    double x = 2.0;
    double y = sqrt(x);
    printf("The square root of %f is %f\n", x, y);

    return 0;
}