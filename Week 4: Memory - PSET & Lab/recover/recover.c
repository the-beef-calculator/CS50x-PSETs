#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int BLOCK_SIZE = 512;
typedef uint8_t BYTE;


int main(int argc, char *argv[])
{

    int c = 0;
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

    char* filename = malloc(8);

    BYTE buffer[BLOCK_SIZE];

    while(fread(buffer, 1, BLOCK_SIZE, f) == BLOCK_SIZE)
    {


        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)

        {
            sprintf(filename, "%03i.jpg", c);
            FILE *img = fopen(filename,"w");

            fwrite(f, 1, BLOCK_SIZE, img);

        }

    }

    printf("found %d files!\n", c);

    free(filename);

}