#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is *number of voters* who prefer candidate i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j, i.e. if true, then i points towards j
bool locked[MAX][MAX];

// Each pair has a winner, loser
// int is the index of candidate in the candidate array
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2]; // Array of all pairs, no tie

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool detect_cycles(int loser, int winner);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // Look for a candidate called "name"
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate found, update "ranks" array for the voter, and return true.
        // "ranks[i]" is the voter's ith preference, with ranks[0] being top preference.
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // If no candidate found, update nothing and return false
    return false;
}

// Update the "preferences" array given one voter's "ranks", called once for each voter
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO: tables in the walkthrough video are helpful
    // Add each pair of candidates to "pairs" array if one candidate is preferred over the other
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // Update global variable "pair_count" to be the total number of pairs
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory, i.e. the number of voters who prefer the preferred candidate
void sort_pairs(void)
{
    // TODO: sort by "preferences[i][j]", selection sort
    for (int i = 0; i < pair_count; i++)
    {
        int max = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[max].winner][pairs[max].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                max = j;
            }
        }
        // Swap
        pair temp = pairs[i];
        pairs[i] = pairs[max];
        pairs[max] = temp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO: detection mechanism for whether adding an arrow woule make a cycle, can use recursion
    for (int i = 0; i < pair_count; i++)
    {
        if (!detect_cycles(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool detect_cycles(int loser, int winner)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Check path: loser -> i
        if (locked[loser][i] == true)
        {
            // Check path: loser == winner
            if (i == winner)
            {
                return true;
            }
            // Check path: i -> winner
            if (detect_cycles(i, winner) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election, which is the (only one) source of the graph, and the candidate has no arrow pointing at them
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                break;
            }
            else if (j == candidate_count - 1)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
    return;
}