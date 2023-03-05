#include "helpers.h"
#include <math.h>

RGBTRIPLE blur_compute(int a, int b, int height, int width, RGBTRIPLE copy[height][width]);
int compare(int a, int b);

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

    // Insert newly computed pixel into image
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

// Detect edges
// For each pixel: 1. compute gx and gy for RGB, 2. pixels at the border have all 0 values,
// 3. compute new value use (gx^2 + gy^2)^0.5, 4. any value > 255 is treated as 255 (compare)
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // Initialisation
    int matrix_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int matrix_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int max = 255;

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            // For a certain pixel at position (a, b), compute its gx and gy

            // From CS0 Discord server @Mao#4194:
            // .rgbtBlue (and the other two) are BYTEs which are just integers capped at 255, so they will never exceed 255
            // If you try to store a number over 255 into a BYTE, it will overflow and wrap-around, so you'd use a long in those cases
            long gx_red = 0, gx_green = 0, gx_blue = 0;
            long gy_red = 0, gy_green = 0, gy_blue = 0;

            for (int i = a - 1; i <= a + 1; i++)
            {

                for (int j = b - 1; j <= b + 1; j++)
                {
                    // Check if the neighborhood pixels are valid
                    if (i < 0 || i >= height || j < 0 || j >= width)
                    {
                        continue;
                    }
                    gx_red += matrix_x[i - (a - 1)][j - (b - 1)] * copy[i][j].rgbtRed;
                    gx_green += matrix_x[i - (a - 1)][j - (b - 1)] * copy[i][j].rgbtGreen;
                    gx_blue += matrix_x[i - (a - 1)][j - (b - 1)] * copy[i][j].rgbtBlue;
                    gy_red += matrix_y[i - (a - 1)][j - (b - 1)] * copy[i][j].rgbtRed;
                    gy_green += matrix_y[i - (a - 1)][j - (b - 1)] * copy[i][j].rgbtGreen;
                    gy_blue += matrix_y[i - (a - 1)][j - (b - 1)] * copy[i][j].rgbtBlue;
                }
            }
            image[a][b].rgbtRed = compare(round(sqrt(gx_red * gx_red + gy_red * gy_red)), max);
            image[a][b].rgbtGreen = compare(round(sqrt(gx_green * gx_green + gy_green * gy_green)), max);
            image[a][b].rgbtBlue = compare(round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue)), max);
        }
    }
    return;
}

// Compare two integers and return the smaller one
int compare(int a, int b)
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
