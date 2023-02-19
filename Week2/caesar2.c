#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
const int alphabet = 26;

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
        if (isupper(plaintext[i]) != 0) // Handle uppercase
        {
            ciphertext[i] = (plaintext[i] - 'A' + key) % alphabet + 'A';
        }
        else if (islower(plaintext[i]) != 0) // Handle lowercase
        {
            ciphertext[i] = (plaintext[i] - 'a' + key) % alphabet + 'a';
        }
        else if (isalpha(plaintext[i]) == 0) // Non-letter characters remain the same
        {
            ciphertext[i] = plaintext[i];
        }
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