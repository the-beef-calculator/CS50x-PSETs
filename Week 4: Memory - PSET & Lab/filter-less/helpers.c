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
    RGBTRIPLE tmp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // //copy of first
            // tmp.rgbtRed = image[i][j].rgbtRed;
            // tmp.rgbtGreen = image[i][j].rgbtGreen;
            // tmp.rgbtBlue = image[i][j].rgbtBlue;


            // image[i][j].rgbtRed = image[i][width - j].rgbtRed;
            // image[i][j].rgbtBlue = image[i][width -j].rgbtBlue;
            // image[i][j].rgbtGreen = image[i][width - j].rgbtGreen;

            // image[i][width - j].rgbtRed = tmp.rgbtRed;
            // image[i][width - j].rgbtBlue = tmp.rgbtBlue;
            // image[i][width - j].rgbtGreen = tmp.rgbtGreen;

            swap(&image[i][j], &image[i][j-1]);



        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

void swap(RGBTRIPLE* x[index1][index2], RGBTRIPLE* y[index3][index4] )
{
    RGBTRIPLE tmp[inde][];

    tmp = *x[][];
    *x[][] = *y[][];
    *y[][] = tmp;
            // tmp.rgbtRed = *x.rgbtRed;
            // tmp.rgbtGreen = *x.rgbtGreen;
            // tmp.rgbtBlue = *x.rgbtBlue;

            //  *x.rgbtRed = *y.rgbtRed;
            //  *x.rgbtBlue = *y.rgbtBlue;
            //  *x.rgbtGreen = *y.rgbtGreen;

            // *y.rgbtRed = tmp.rgbtRed;
            // *y.rgbtBlue = tmp.rgbtBlue;
            // *y.rgbtGreen = tmp.rgbtGreen;
}
