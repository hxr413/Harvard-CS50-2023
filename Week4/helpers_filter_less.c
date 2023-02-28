#include "helpers.h"
#include <math.h>

int compare_int(int a, int b);
RGBTRIPLE blur_compute(int a, int b, int height, int width, RGBTRIPLE copy[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set RGB
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate new RGB
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // In case any new values exceed 255
            int max = 255;

            // Set new RGB
            image[i][j].rgbtRed = compare_int(sepiaRed, max);
            image[i][j].rgbtGreen = compare_int(sepiaGreen, max);
            image[i][j].rgbtBlue = compare_int(sepiaBlue, max);
        }
    }
    return;
}

// Compare two integers and return the smaller one
int compare_int(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int k = width - j - 1;

            //Swap pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Copy newly computed pixel into image
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b] = blur_compute(a, b, height, width, copy);
        }
    }
    return;
}

// Compute new RGB for a certain pixel at position (a, b)
RGBTRIPLE blur_compute(int a, int b, int height, int width, RGBTRIPLE copy[height][width])
{
    float num_pixels = 0.0;
    int sum_Red = 0, sum_Green = 0, sum_Blue = 0;

    // Consider the neighborhood pixels
    for (int i = a - 1; i <= a + 1; i++)
    {
        for (int j = b - 1; j <= b + 1; j++)
        {
            // Check if the neighborhood pixels are valid
            if (i < 0 || i >= height || j < 0 || j >= width)
            {
                continue;
            }
            num_pixels++;
            sum_Red += copy[i][j].rgbtRed;
            sum_Green += copy[i][j].rgbtGreen;
            sum_Blue += copy[i][j].rgbtBlue;
        }
    }

    // Make new pixel
    RGBTRIPLE blur;
    blur.rgbtRed = round(sum_Red / num_pixels);
    blur.rgbtGreen = round(sum_Green / num_pixels);
    blur.rgbtBlue = round(sum_Blue / num_pixels);

    return blur;
}