#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
const int alphabet = 26;
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Get key
    if ((argc != 2) || (only_digits(argv[1]) != true))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    // Get plaintext
    string plaintext = get_string("Plaintext:  ");
    string ciphertext = plaintext;

    // Encipher
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        ciphertext[i] = rotate(plaintext[i], key);
    }

    //Print ciphertext
    printf("Ciphertext: %s", ciphertext);
    printf("\n");
    return 0;
}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return false;
        }
    }
    return true; // Without this line, there will be error "Non-void function does not return a value in all contral paths".
}

char rotate(char plain, int n)
{
    char cipher = plain;

    if (isupper(plain) != 0) // Handle uppercase
    {
        cipher = (plain - 'A' + n) % alphabet + 'A';
    }
    else if (islower(plain) != 0) // Handle lowercase
    {
        cipher = (plain - 'a' + n) % alphabet + 'a';
    }

    return cipher;
}