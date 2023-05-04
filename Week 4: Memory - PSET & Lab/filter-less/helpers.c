#include "helpers.h"
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

   BYTE grayscaleHex;

   for (int i = 0; i < height; i++)
   {
        for (int j = 0; j < width; j++)
        {
            //grayscale is defined by averaging R,G, and B colors, and changing every pixel hex color to the new gray hex value.
            grayscaleHex = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = grayscaleHex;
            image[i][j].rgbtGreen = grayscaleHex;
            image[i][j].rgbtBlue = grayscaleHex;

        }
   }



}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE sepiaRed,sepiaGreen,sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

           float tr = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
           sepiaRed = (tr > 255) ? 255 : tr;

           float tg = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
           sepiaGreen = (tg > 255) ? 255 : tg;

           float tb = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
           sepiaBlue = (tb > 255) ? 255 : tb;


            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    int z;

    for (int i = 0; i < height; i++)
    {
        for (int j = width; j > 0; j--)
        {
            tmp[i][z].rgbtRed = image[i][j].rgbtRed;
            tmp[i][z].rgbtGreen = image[i][j].rgbtGreen;
            tmp[i][z].rgbtBlue = image[i][j].rgbtBlue;
            z++;
        }


        for (z = 0; z < width; z++)
        {
            image[i][z].rgbtRed = tmp[i][z].rgbtRed;
            image[i][z].rgbtGreen = tmp[i][z].rgbtGreen;
            image[i][z].rgbtBlue = tmp[i][z].rgbtBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int count = -1;
    RGBTRIPLE copy[height][width];

    BYTE avgRed,avgGreen,avgBlue;

    //copies the original image into a new variable as a reference.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //capture a 3x3 grid for all RGB values.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int z = 0; z < 3; z++)
            {
                if ((i - 1 < 0 || i + 1 > height) || (j - 1 < 0 || j + 1 > width))
                {
                    continue;
                }

                while (count < 1 )
                {
                    avgRed += copy[z + count][z].rgbtRed;
                    avgGreen += copy[z + count][z].rgbtGreen;
                    avgBlue += copy[z+ count][z].rgbtBlue;


                 count++;
                }


            }

        }


    return;
}

