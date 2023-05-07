#include <stdio.h>
#include <stdlib.h>

int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

BYTE buffer[BLOCK_SIZE];

int main(int argc, char *argv[])
{
    int c = 1;
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

    while(fread(buffer, 1, BLOCK_SIZE, argv[1]) == BLOCK_SIZE)
    {
        printf("READING BLOCK NUMBER %i", c);
    }



}