#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask the user for their name
    string name = get_string("What's your name? ");
    
    //Print out the greeting
    printf("hello, %s\n", name);
}