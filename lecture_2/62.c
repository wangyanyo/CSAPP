#include <stdio.h>

int int_shifts_are_arithmetic()
{
    int res = -1;
    int size = sizeof(int) << 3;

    return (res >> size) & 1;
}

int main()
{
    printf("%d\n", int_shifts_are_arithmetic());
}