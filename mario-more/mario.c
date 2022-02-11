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

    // starting on left side.
    for (int i = 0; i < height; i++)
    {
        for (int j = height; j < (height - 1) - 1; j++ )
        {
            print(" ");
        }

    }
}
