#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // Calculate number of years (int) until we reach threshold // Use a loop to update the population size and the number of years that have passed
    int n = 0;
    int start;
    int end;
    for
    (
      start = get_int("Start size: "), end = get_int("End size: ");
      start < end;
      start = start + (start / 3) - (start / 4), n++
    )

    // Prompt for start size // If start size < 9, repeat
    do
    {
      printf("Please input a positive integer greater than 9.\n");
      start = get_int("Start size: ");
    }
    while (start < 9);

    // Prompt for end size // If end size < start size, repeat

    do
    {
      printf("Please input a positive integer greater than your start size.\n");
      end = get_int("End size: ");
    }
    while (end < start);

    // Print number of years (Years: n)
    {
       printf("Years: %i\n", n);
    }
}
