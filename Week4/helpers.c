#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtBlue == 0x00) // Since smiley.bmp only contains white and black pixels, one condition is enough
            {
                image[i][j].rgbtBlue = 0x4d;
                image[i][j].rgbtGreen = 0xcc;
                image[i][j].rgbtRed = 0xff;
            }
        }
    }
}