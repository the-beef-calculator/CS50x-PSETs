#include <stdio.h>


int add(int x, int y)
{
    return x+y;
}
int main(void)
{
    int x = 104;
    int y = 3000;

    printf("%d\n", add (x,y));

    return 0;
}