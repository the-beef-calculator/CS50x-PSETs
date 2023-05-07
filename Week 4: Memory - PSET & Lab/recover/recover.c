#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // checking for proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover FILENAME.raw \n");
        return 1;
    }


    FILE *f = fopen(argv[1],"r");
    //checking if file was successfully located and opened
    if (f == NULL)
    {
        printf("File not found or is invalid. \n");
        return 1;
    }




}