#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int mean = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate mean of colors of the pixels to bring it to gray scale
            mean = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtRed = mean;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // define temporary pixel
    RGBTRIPLE pt;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(width / 2); j++)
        {
            // swap pixel information
            pt = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = pt;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // copy image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0) // close to upleft corner
            {
                image[i][j].rgbtBlue = round((float)(temp[i][j].rgbtBlue + temp[i][j + 1].rgbtBlue + temp[i + 1][j].rgbtBlue +
                                                     temp[i + 1][j + 1].rgbtBlue) / 4);

                image[i][j].rgbtGreen = round((float)(temp[i][j].rgbtGreen + temp[i][j + 1].rgbtGreen + temp[i + 1][j].rgbtGreen +
                                                      temp[i + 1][j + 1].rgbtGreen) / 4);

                image[i][j].rgbtRed = round((float)(temp[i][j].rgbtRed + temp[i][j + 1].rgbtRed + temp[i + 1][j].rgbtRed +
                                                    temp[i + 1][j + 1].rgbtRed) / 4);
            }
            else if (i == 0 && j == (width - 1)) // close to upright corner
            {
                image[i][j].rgbtBlue = round((float)(temp[i][j - 1].rgbtBlue + temp[i][j].rgbtBlue + temp[i + 1][j - 1].rgbtBlue +
                                                     temp[i + 1][j].rgbtBlue) / 4);

                image[i][j].rgbtGreen = round((float)(temp[i][j - 1].rgbtGreen + temp[i][j].rgbtGreen + temp[i + 1][j - 1].rgbtGreen +
                                                      temp[i + 1][j].rgbtGreen) / 4);

                image[i][j].rgbtRed = round((float)(temp[i][j - 1].rgbtRed + temp[i][j].rgbtRed + temp[i + 1][j - 1].rgbtRed +
                                                    temp[i + 1][j].rgbtRed) / 4);
            }
            else if (i == (height - 1) && j == 0) // close to bottomleft corner
            {
                image[i][j].rgbtBlue = round((float)(temp[i - 1][j].rgbtBlue + temp[i - 1][j + 1].rgbtBlue + temp[i][j].rgbtBlue +
                                                     temp[i][j + 1].rgbtBlue) / 4);

                image[i][j].rgbtGreen = round((float)(temp[i - 1][j].rgbtGreen + temp[i - 1][j + 1].rgbtGreen + temp[i][j].rgbtGreen +
                                                      temp[i][j + 1].rgbtGreen) / 4);

                image[i][j].rgbtRed = round((float)(temp[i - 1][j].rgbtRed + temp[i - 1][j + 1].rgbtRed + temp[i][j].rgbtRed +
                                                    temp[i][j + 1].rgbtRed) / 4);
            }
            else if (i == (height - 1) && j == (width - 1)) // close to bottomright corner
            {
                image[i][j].rgbtBlue = round((float)(temp[i - 1][j - 1].rgbtBlue + temp[i - 1][j].rgbtBlue + temp[i][j - 1].rgbtBlue +
                                                     temp[i][j].rgbtBlue) / 4);

                image[i][j].rgbtGreen = round((float)(temp[i - 1][j - 1].rgbtGreen + temp[i - 1][j].rgbtGreen +
                                                      temp[i][j - 1].rgbtGreen + temp[i][j].rgbtGreen) / 4);

                image[i][j].rgbtRed = round((float)(temp[i - 1][j - 1].rgbtRed + temp[i - 1][j].rgbtRed + temp[i][j - 1].rgbtRed +
                                                    temp[i][j].rgbtRed) / 4);
            }
            else if (i == 0 && j > 0) // close to ceiling
            {
                image[i][j].rgbtBlue = round((float)(temp[i][j - 1].rgbtBlue + temp[i][j].rgbtBlue +
                                                     temp[i][j + 1].rgbtBlue + temp[i + 1][j - 1].rgbtBlue + temp[i + 1][j].rgbtBlue +
                                                     temp[i + 1][j + 1].rgbtBlue) / 6);

                image[i][j].rgbtGreen = round((float)(temp[i][j - 1].rgbtGreen + temp[i][j].rgbtGreen +
                                                      temp[i][j + 1].rgbtGreen + temp[i + 1][j - 1].rgbtGreen + temp[i + 1][j].rgbtGreen +
                                                      temp[i + 1][j + 1].rgbtGreen) / 6);

                image[i][j].rgbtRed = round((float)(temp[i][j - 1].rgbtRed + temp[i][j].rgbtRed + temp[i][j + 1].rgbtRed +
                                                    temp[i + 1][j - 1].rgbtRed + temp[i + 1][j].rgbtRed + temp[i + 1][j + 1].rgbtRed) / 6);
            }
            else if (i == (height - 1) && j > 0) // close to floor
            {
                image[i][j].rgbtBlue = round((float)(temp[i - 1][j - 1].rgbtBlue + temp[i - 1][j].rgbtBlue +
                                                     temp[i - 1][j + 1].rgbtBlue + temp[i][j - 1].rgbtBlue + temp[i][j].rgbtBlue +
                                                     temp[i][j + 1].rgbtBlue) / 6);

                image[i][j].rgbtGreen = round((float)(temp[i - 1][j - 1].rgbtGreen + temp[i - 1][j].rgbtGreen +
                                                      temp[i - 1][j + 1].rgbtGreen + temp[i][j - 1].rgbtGreen + temp[i][j].rgbtGreen +
                                                      temp[i][j + 1].rgbtGreen) / 6);

                image[i][j].rgbtRed = round((float)(temp[i - 1][j - 1].rgbtRed + temp[i - 1][j].rgbtRed + temp[i - 1][j + 1].rgbtRed +
                                                    temp[i][j - 1].rgbtRed + temp[i][j].rgbtRed + temp[i][j + 1].rgbtRed) / 6);
            }
            else if (i > 0 && j == 0) // close to left wall
            {
                image[i][j].rgbtBlue = round((float)(temp[i - 1][j].rgbtBlue + temp[i - 1][j + 1].rgbtBlue + temp[i][j].rgbtBlue +
                                                     temp[i][j + 1].rgbtBlue + temp[i + 1][j].rgbtBlue + temp[i + 1][j + 1].rgbtBlue) / 6);

                image[i][j].rgbtGreen = round((float)(temp[i - 1][j].rgbtGreen + temp[i - 1][j + 1].rgbtGreen + temp[i][j].rgbtGreen +
                                                      temp[i][j + 1].rgbtGreen + temp[i + 1][j].rgbtGreen + temp[i + 1][j + 1].rgbtGreen) / 6);

                image[i][j].rgbtRed = round((float)(temp[i - 1][j].rgbtRed + temp[i - 1][j + 1].rgbtRed + temp[i][j].rgbtRed +
                                                    temp[i][j + 1].rgbtRed + temp[i + 1][j].rgbtRed + temp[i + 1][j + 1].rgbtRed) / 6);
            }
            else if (i > 0 && j == (width - 1)) // close to right wall
            {
                image[i][j].rgbtBlue = round((float)(temp[i - 1][j - 1].rgbtBlue + temp[i - 1][j].rgbtBlue +
                                                     temp[i][j - 1].rgbtBlue + temp[i][j].rgbtBlue +
                                                     temp[i + 1][j - 1].rgbtBlue + temp[i + 1][j].rgbtBlue) / 6);

                image[i][j].rgbtGreen = round((float)(temp[i - 1][j - 1].rgbtGreen + temp[i - 1][j].rgbtGreen +
                                                      temp[i][j - 1].rgbtGreen + temp[i][j].rgbtGreen +
                                                      temp[i + 1][j - 1].rgbtGreen + temp[i + 1][j].rgbtGreen) / 6);

                image[i][j].rgbtRed = round((float)(temp[i - 1][j - 1].rgbtRed + temp[i - 1][j].rgbtRed +
                                                    temp[i][j - 1].rgbtRed + temp[i][j].rgbtRed +
                                                    temp[i + 1][j - 1].rgbtRed + temp[i + 1][j].rgbtRed) / 6);
            }
            else // general case
            {
                image[i][j].rgbtBlue = round((float)(temp[i - 1][j - 1].rgbtBlue + temp[i - 1][j].rgbtBlue +
                                                     temp[i - 1][j + 1].rgbtBlue + temp[i][j - 1].rgbtBlue + temp[i][j].rgbtBlue +
                                                     temp[i][j + 1].rgbtBlue + temp[i + 1][j - 1].rgbtBlue + temp[i + 1][j].rgbtBlue +
                                                     temp[i + 1][j + 1].rgbtBlue) / 9);

                image[i][j].rgbtGreen = round((float)(temp[i - 1][j - 1].rgbtGreen + temp[i - 1][j].rgbtGreen +
                                                      temp[i - 1][j + 1].rgbtGreen + temp[i][j - 1].rgbtGreen + temp[i][j].rgbtGreen +
                                                      temp[i][j + 1].rgbtGreen + temp[i + 1][j - 1].rgbtGreen + temp[i + 1][j].rgbtGreen +
                                                      temp[i + 1][j + 1].rgbtGreen) / 9);

                image[i][j].rgbtRed = round((float)(temp[i - 1][j - 1].rgbtRed + temp[i - 1][j].rgbtRed + temp[i - 1][j + 1].rgbtRed +
                                                    temp[i][j - 1].rgbtRed + temp[i][j].rgbtRed + temp[i][j + 1].rgbtRed +
                                                    temp[i + 1][j - 1].rgbtRed + temp[i + 1][j].rgbtRed + temp[i + 1][j + 1].rgbtRed) / 9);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    float gb, gxb, gyb, gg, gxg, gyg, gr, gxr, gyr;
    int igx[10], igy[10];

    // copy image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // read actual image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Upleft corner
            if (i == 0 && j == 0)
            {
                // set values for gx
                igx[1] = 0;
                igx[2] = 0;
                igx[3] = 0;
                igx[4] = 0;
                igx[5] = 0;
                igx[6] = 2;
                igx[7] = 0;
                igx[8] = 0;
                igx[9] = 1;

                // set values for gy
                igy[1] = 0;
                igy[2] = 0;
                igy[3] = 0;
                igy[4] = 0;
                igy[5] = 0;
                igy[6] = 0;
                igy[7] = 0;
                igy[8] = 2;
                igy[9] = 1;
            }
            // Upright corner
            else if (i == 0 && j == (width - 1))
            {
                // set values for gx
                igx[1] = 0;
                igx[2] = 0;
                igx[3] = 0;
                igx[4] = -2;
                igx[5] = 0;
                igx[6] = 0;
                igx[7] = -1;
                igx[8] = 0;
                igx[9] = 0;

                // set values for gy
                igy[1] = 0;
                igy[2] = 0;
                igy[3] = 0;
                igy[4] = 0;
                igy[5] = 0;
                igy[6] = 0;
                igy[7] = 1;
                igy[8] = 2;
                igy[9] = 0;
            }
            // Bottomleft corner
            else if (i == (height - 1) && j == 0)
            {
                // set values for gx
                igx[1] = 0;
                igx[2] = 0;
                igx[3] = 1;
                igx[4] = 0;
                igx[5] = 0;
                igx[6] = 2;
                igx[7] = 0;
                igx[8] = 0;
                igx[9] = 0;

                // set values for gy
                igy[1] = 0;
                igy[2] = -2;
                igy[3] = -1;
                igy[4] = 0;
                igy[5] = 0;
                igy[6] = 0;
                igy[7] = 0;
                igy[8] = 0;
                igy[9] = 0;
            }
            // Bottomright corner
            else if (i == (height - 1) && j == (width - 1))
            {
                // set values for gx
                igx[1] = -1;
                igx[2] = 0;
                igx[3] = 0;
                igx[4] = -2;
                igx[5] = 0;
                igx[6] = 0;
                igx[7] = 0;
                igx[8] = 0;
                igx[9] = 0;

                // set values for gy
                igy[1] = -1;
                igy[2] = -2;
                igy[3] = 0;
                igy[4] = 0;
                igy[5] = 0;
                igy[6] = 0;
                igy[7] = 0;
                igy[8] = 0;
                igy[9] = 0;
            }
            // Ceiling
            else if (i == 0 && j > 0)
            {
                // set values for gx
                igx[1] = 0;
                igx[2] = 0;
                igx[3] = 0;
                igx[4] = -2;
                igx[5] = 0;
                igx[6] = 2;
                igx[7] = -1;
                igx[8] = 0;
                igx[9] = 1;

                // set values for gy
                igy[1] = 0;
                igy[2] = 0;
                igy[3] = 0;
                igy[4] = 0;
                igy[5] = 0;
                igy[6] = 0;
                igy[7] = 1;
                igy[8] = 2;
                igy[9] = 1;
            }
            // Floor
            else if (i == (height - 1) && j > 0)
            {
                // set values for gx
                igx[1] = -1;
                igx[2] = 0;
                igx[3] = 1;
                igx[4] = -2;
                igx[5] = 0;
                igx[6] = 2;
                igx[7] = 0;
                igx[8] = 0;
                igx[9] = 0;

                // set values for gy
                igy[1] = -1;
                igy[2] = -2;
                igy[3] = -1;
                igy[4] = 0;
                igy[5] = 0;
                igy[6] = 0;
                igy[7] = 0;
                igy[8] = 0;
                igy[9] = 0;
            }
            // Left wall
            else if (i > 0 && j == 0)
            {
                // set values for gx
                igx[1] = 0;
                igx[2] = 0;
                igx[3] = 1;
                igx[4] = 0;
                igx[5] = 0;
                igx[6] = 2;
                igx[7] = 0;
                igx[8] = 0;
                igx[9] = 1;

                // set values for gy
                igy[1] = 0;
                igy[2] = -2;
                igy[3] = -1;
                igy[4] = 0;
                igy[5] = 0;
                igy[6] = 0;
                igy[7] = 0;
                igy[8] = 2;
                igy[9] = 1;
            }
            // Right wall
            else if (i > 0 && j == (width - 1))
            {
                // set values for gx
                igx[1] = -1;
                igx[2] = 0;
                igx[3] = 0;
                igx[4] = -2;
                igx[5] = 0;
                igx[6] = 0;
                igx[7] = -1;
                igx[8] = 0;
                igx[9] = 0;

                // set values for gy
                igy[1] = -1;
                igy[2] = -2;
                igy[3] = 0;
                igy[4] = 0;
                igy[5] = 0;
                igy[6] = 0;
                igy[7] = 1;
                igy[8] = 2;
                igy[9] = 0;
            }
            // General situation
            else
            {
                // set values for gx
                igx[1] = -1;
                igx[2] = 0;
                igx[3] = 1;
                igx[4] = -2;
                igx[5] = 0;
                igx[6] = 2;
                igx[7] = -1;
                igx[8] = 0;
                igx[9] = 1;

                // set values for gy
                igy[1] = -1;
                igy[2] = -2;
                igy[3] = -1;
                igy[4] = 0;
                igy[5] = 0;
                igy[6] = 0;
                igy[7] = 1;
                igy[8] = 2;
                igy[9] = 1;
            }

            // calculate Gx for green
            gxb = (temp[i - 1][j - 1].rgbtBlue * igx[1] +
                   temp[i - 1][j].rgbtBlue * igx[2] +
                   temp[i - 1][j + 1].rgbtBlue * igx[3] +
                   temp[i][j - 1].rgbtBlue * igx[4] +
                   temp[i][j].rgbtBlue * igx[5] +
                   temp[i][j + 1].rgbtBlue * igx[6] +
                   temp[i + 1][j - 1].rgbtBlue * igx[7] +
                   temp[i + 1][j].rgbtBlue * igx[8] +
                   temp[i + 1][j + 1].rgbtBlue * igx[9]);

            // calculate Gy for blue
            gyb = (temp[i - 1][j - 1].rgbtBlue * igy[1] +
                   temp[i - 1][j].rgbtBlue * igy[2] +
                   temp[i - 1][j + 1].rgbtBlue * igy[3] +
                   temp[i][j - 1].rgbtBlue * igy[4] +
                   temp[i][j].rgbtBlue * igy[5] +
                   temp[i][j + 1].rgbtBlue * igy[6] +
                   temp[i + 1][j - 1].rgbtBlue * igy[7] +
                   temp[i + 1][j].rgbtBlue * igy[8] +
                   temp[i + 1][j + 1].rgbtBlue * igy[9]);

            // calculate G for blue
            gb = round(sqrt((float)pow(gxb, 2) + (float)pow(gyb, 2)));
            image[i][j].rgbtBlue = (gb > 255) ? 255 : gb;

            // calculate Gx for green
            gxg = (temp[i - 1][j - 1].rgbtGreen * igx[1] +
                   temp[i - 1][j].rgbtGreen * igx[2] +
                   temp[i - 1][j + 1].rgbtGreen * igx[3] +
                   temp[i][j - 1].rgbtGreen * igx[4] +
                   temp[i][j].rgbtGreen * igx[5] +
                   temp[i][j + 1].rgbtGreen * igx[6] +
                   temp[i + 1][j - 1].rgbtGreen * igx[7] +
                   temp[i + 1][j].rgbtGreen * igx[8] +
                   temp[i + 1][j + 1].rgbtGreen * igx[9]);

            // calculate Gy for green
            gyg = (temp[i - 1][j - 1].rgbtGreen * igy[1] +
                   temp[i - 1][j].rgbtGreen * igy[2] +
                   temp[i - 1][j + 1].rgbtGreen * igy[3] +
                   temp[i][j - 1].rgbtGreen * igy[4] +
                   temp[i][j].rgbtGreen * igy[5] +
                   temp[i][j + 1].rgbtGreen * igy[6] +
                   temp[i + 1][j - 1].rgbtGreen * igy[7] +
                   temp[i + 1][j].rgbtGreen * igy[8] +
                   temp[i + 1][j + 1].rgbtGreen * igy[9]);

            // calculate G for green
            gg = round(sqrt((float)pow(gxg, 2) + (float)pow(gyg, 2)));
            image[i][j].rgbtGreen = (gg > 255) ? 255 : gg;

            // calculate Gx for red
            gxr = (temp[i - 1][j - 1].rgbtRed * igx[1] +
                   temp[i - 1][j].rgbtRed * igx[2] +
                   temp[i - 1][j + 1].rgbtRed * igx[3] +
                   temp[i][j - 1].rgbtRed * igx[4] +
                   temp[i][j].rgbtRed * igx[5] +
                   temp[i][j + 1].rgbtRed * igx[6] +
                   temp[i + 1][j - 1].rgbtRed * igx[7] +
                   temp[i + 1][j].rgbtRed * igx[8] +
                   temp[i + 1][j + 1].rgbtRed * igx[9]);

            // calculate Gy for red
            gyr = (temp[i - 1][j - 1].rgbtRed * igy[1] +
                   temp[i - 1][j].rgbtRed * igy[2] +
                   temp[i - 1][j + 1].rgbtRed * igy[3] +
                   temp[i][j - 1].rgbtRed * igy[4] +
                   temp[i][j].rgbtRed * igy[5] +
                   temp[i][j + 1].rgbtRed * igy[6] +
                   temp[i + 1][j - 1].rgbtRed * igy[7] +
                   temp[i + 1][j].rgbtRed * igy[8] +
                   temp[i + 1][j + 1].rgbtRed * igy[9]);

            // calculate G for red
            gr = round(sqrt((float)pow(gxr, 2) + (float)pow(gyr, 2)));
            image[i][j].rgbtRed = (gr > 255) ? 255 : gr;
        }
    }
    return;
}
