#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    int spaces;
    int hashnumber;

    do
    {
        height = get_int("Height: ");
    }

    while(height < 1 || height > 8);
    spaces = height - 1


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < spaces; j++)
        {


        }

    }
}
