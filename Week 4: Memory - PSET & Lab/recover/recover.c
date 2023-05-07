#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./recover FILENAME.raw");
        return 1;
    }

    FILE *f = fopen(argv[1],"r");

    if (*f == NULL)
    {
        printf("Invalid file.");
        return 1;
    }


}