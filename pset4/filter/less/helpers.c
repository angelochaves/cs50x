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
            mean = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtRed = mean;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // define temporary variables for every channel
    int sepiaBlue = 0, sepiaGreen = 0, sepiaRed = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            // caps pixels value at 255
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // create temporary pixel
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