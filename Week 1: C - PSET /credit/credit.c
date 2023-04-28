#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    int spaces;

    do
    {
        height = get_int("Height: ");
    }

    while(height < 1 || height > 8);

    // for each column
    for (int i = 0; i < height; i++)
    {
        for (int j = height; j >= 0; j-- )
        {
            }
        }
        //skips to the next line
        printf(" \n");
    }
