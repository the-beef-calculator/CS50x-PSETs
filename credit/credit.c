#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }

    while(height < 1 || height > 8);


    // for each column
    for (int i = 0; i < height; i++)
    {
        for (int j = height; j <= i; j++ )
        {
            //constructing left side, adding spaces
            if (j < height)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        //skips to the next line
        printf(" \n");
    }
}