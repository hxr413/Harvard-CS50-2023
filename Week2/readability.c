#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letter(string t);
int count_word(string t);
int count_sentence(string t);

int main(void)
{
    // Prompt the user for a string of text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences
    int l = count_letter(text);
    int w = count_word(text);
    int s = count_sentence(text);

    // FOR DEBUGGING: printf("%i letter, %i words, %i sentences\n", l, w, s);

    // Calculate Coleman-Liau index
    float L = (float)l / (float)w * 100;
    float S = (float)s / (float)w * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // FOR DEBUGGING: printf("L = %f, S = %f, index = %f\n", L, S, index);

    // Print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer
    // If the resulting index number is 16 or higher, output "Grade 16+" instead of giving the exact index number.
    // If the index number is less than 1, output "Before Grade 1".
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int)(round(index)));
    }
}

// A letter is any lowercase character from a to z or any uppercase character from A to Z
int count_letter(string t)
{
    int letter = 0;

    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if (isupper(t[i]) || islower(t[i]))
        {
            letter++;
        }
    }

    return letter;
}

// Any sequence of characters separated by spaces should count as a word
int count_word(string t)
{
    int word = 0;

    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if (isspace(t[i]))
        {
            word++;
        }
    }

    return (word + 1);
}

// Any occurrence of a period, exclamation point, or question mark indicates the end of a sentence
int count_sentence(string t)
{
    int sentence = 0;

    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if ((t[i] == '.') || (t[i] == '!') || (t[i] == '?'))
        {
            sentence++;
        }
    }

    return sentence;
}

