#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

const int alphabet = 26;

int main(int argc, string argv[])
{
    // Get key
    string key = argv[1];

    // Validate key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check key length
    if (strlen(key) != alphabet)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check for non-alpahbetic characters
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Check for repeated characters (case-insensitive)
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // Get plaintext
    string plaintext = get_string("plaintext:  ");
    string ciphertext = plaintext;

    // Encipher
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]) != 0) // Handle uppercase
        {
            ciphertext[i] = toupper(key[plaintext[i] - 'A']);
        }
        else if (islower(plaintext[i]) != 0) // Handle lowercase
        {
            ciphertext[i] = tolower(key[plaintext[i] - 'a']);
        }
        else if (isalpha(plaintext[i]) == 0) // Non-letter characters remain the same
        {
            ciphertext[i] = plaintext[i];
        }
    }

    //Print ciphertext
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}