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
        for (int j = 0; j <= i; j++ )
        {
            //constructing left side, adding spaces
            spaces = height - 1;
            if (spaces > 0)
            {
            while (spaces != 0)
            {
                printf(" ");
                spaces--;
            }
            }
            {
                printf("#");
            }
        }
        //skips to the next line
        printf(" \n");
    }
}