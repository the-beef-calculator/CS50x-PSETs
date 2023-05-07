#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

   int grayscaleHex;

   for (int i = 0; i < height; i++)
   {
        for (int j = 0; j < width; j++)
        {
            //grayscale is defined by averaging R,G, and B colors, and changing every pixel hex color to the new gray hex value.

            grayscaleHex = round( (float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = grayscaleHex;
            image[i][j].rgbtGreen = grayscaleHex;
            image[i][j].rgbtBlue = grayscaleHex;


        }
   }



}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed,sepiaGreen,sepiaBlue;

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


            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];


    for (int i = 0; i < height; i++)
    {
        int z = 0;

        for (int j = width - 1; j >= 0; j--)
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
// void blur(int height, int width, RGBTRIPLE image[height][width])
// {

//     RGBTRIPLE copy[height][width];

//     //copies the original image into a new variable as a reference.
//     for (int i = 0; i < height; i++)
//     {
//         for (int j = 0; j < width; j++)
//         {
//             copy[i][j].rgbtRed = image[i][j].rgbtRed;
//             copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
//             copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
//         }
//     }


//     for (int i = 0; i < height; i++)
//     {
//         for (int j = 0; j < width; j++)
//         {
//         int count = -1;
//         int numberCount = 0;
//         float avgRed = 0, avgGreen = 0, avgBlue = 0;

//         for (int z = -1; z <= 1; z++)
//         {
//             for (int k = -1; k <= 1; k++)
//             {
//                 if (i+z < 0 || i+z >= height || j+k < 0 || j+k >= width)
//                 {
//                     continue;
//                 }
//                 avgRed += copy[i+z][j+k].rgbtRed;
//                 avgGreen += copy[i+z][j+k].rgbtGreen;
//                 avgBlue += copy[i+z][j+k].rgbtBlue;
//                 numberCount++;
//             }
//         }

//         image[i][j].rgbtRed = round(avgRed / numberCount);
//         image[i][j].rgbtGreen = round(avgGreen / numberCount);
//         image[i][j].rgbtBlue = round(avgBlue / numberCount);
//     }
//     }
// }

void blur(int height, int width, RGBTRIPLE image[height][width])
{


    int count = -1;
    int numberCount = 0;
    RGBTRIPLE copy[height][width];

    float avgRed = 0,avgGreen = 0,avgBlue = 0;

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
            for (int z = -1; z <= 1; z++)
            {

                if ((i - 1 < 0 || i + 1 >= height) || (j - 1 < 0 || j + 1 >= width))
                {
                    continue;
                }

                while (count <= 1 )
                {

                    avgRed += copy[i + z][j + count].rgbtRed;
                    avgGreen += copy[i + z][j + count].rgbtGreen;
                    avgBlue += copy[i + z][j + count].rgbtBlue;
                    count++;
                    numberCount++;

                }

            }

             image[i][j].rgbtRed = round((float) avgRed / (float)numberCount);
             image[i][j].rgbtGreen = round((float) avgGreen / (float)numberCount);
             image[i][j].rgbtBlue = round((float) avgBlue / (float)numberCount);

            count = -1;
            numberCount = 0;
            avgRed = 0;
            avgBlue = 0;
            avgGreen = 0;

            }


    }
     return;
}
}