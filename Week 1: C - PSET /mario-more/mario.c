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

    while (height < 1 || height > 8);
    //spaces will always be 1 less than hash amount
    spaces = height - 1;
    // there will always be at least 1 hash
    hashnumber = 1;
    //quadruple for loop (probably not the best practice)

    for (int i = 0; i < height; i++)
    {
        // adding spaces on the left side
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }
        //printing of hashes starts after spaces run out
        for (int z = 0; z < hashnumber; z++)
        {
            printf("#");
        }
        // adding two spaces
        printf("  ");
        // repeat for the right side
        for (int h = 0; h < hashnumber; h++)
        {
            printf("#");
        }

        printf("\n");
        hashnumber++;
        spaces--;

    }
}
