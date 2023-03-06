// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// the hash function combines the ASCII sum of first 3 letters and the ASCII value of first letter in word
// for number of different sums, consider min = AAA = 195, max = ZZ'(or Z'Z) = 271 (where ' is treated as having ASCII value 91), so there are 271-195+1=77 different sums
// for each sum, there are 26 different first letters, so there should be 77x26=2002 buckets
const unsigned int N = 2002;
// number of letters
const int num_letter = 26;

// number of words in dictionary
int dict_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // 1. hash word to get a hash value
    int index = hash(word);

    // 2. access linked list at that index in hash table

    // 3. traverse linked list, looking for word
    // set up a pointer called cursor, pointing at 1st element
    node *cursor = table[index];

    // when reach null, i.e. end of linked list, cursor at the end of the list and still not found
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        // if not found, move to next element cursor = cursor->next
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    // consider the first 3 letters in word. if word length < 3, the vacancies are considered as A
    char letters[3] = {'A', 'A', 'A'};

    if (strlen(word) == 1)
    {
        letters[0] = toupper(word[0]);
    }
    // in dictionary, ' usually appears in the format [word]'s, so it's safe to assume for words with 1 or 2 letters, there will be no ' in them.
    else if (strlen(word) == 2)
    {
        letters[0] = toupper(word[0]);
        letters[1] = toupper(word[1]);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            // if there is a ', change it to [, which has ASCII value 91, 1 larger than Z(=90)
            if (word[i] == '\'')
            {
                letters[i] = '[';
            }

            if (isalpha(word[i]))
            {
                // make sure the ASCII sum is case-insensitive
                letters[i] = toupper(word[i]);
            }
        }
    }

    // turn all letters into ASCII values
    int numbers[3];

    for (int i = 0; i < 3; i++)
    {
        // make sure AAA turns into 0 and etc.
        numbers[i] = (int)(letters[i] - 'A');
    }

    // calculate the ASCII sum of first 3 letters
    int sum = numbers[0] + numbers[1] + numbers[2];

    // for min = AAA, index = 0, for max = ZZ'(or Z'Z), index = (271-3x65)x26+(90-65) = 2001
    int index = sum * num_letter + numbers[0];

    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // store dictionary in a hash table

    // 1. open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fclose(dict);
        return false;
    }

    // 2. read strings from file one at a time

    // buffer is a character array where to read word into and then access all of the individual characters
    char buffer[LENGTH + 1];

    while (fscanf(dict, "%s", buffer) != EOF)
    {
        // 3. create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dict);
            return false;
        }
        strcpy(n->word, buffer);
        n->next = NULL;

        // 4. Hash word to obtain a hash value
        int index = hash(buffer);

        // 5. Insert node into hash table at that location
        n->next = table[index];
        table[index] = n;

        dict_size++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
