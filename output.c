#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int x = 0;
int y = 0;
int z = 0;

int sum()
{
    z = x;
    z += y;
}
int main()
{
    x = 20;
    y = 30;
    sum();
    {
    printf("%i", z);
    }
    {
    printf("%i", 2);
    }
}
