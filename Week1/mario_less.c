#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Ask user to input height
    int height;
    do
    {
        printf("Please input a positive integer between 1 and 8. \n");
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);


    //Print the pyramid from i = 1 to height
    //Make sure there are spaceholders j = height - i
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= (height - i); j++)
        {
            printf(" ");
        }

        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}