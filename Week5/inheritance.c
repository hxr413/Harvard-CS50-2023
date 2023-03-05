// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

char random_parent_allele(person parent);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
// allocate (via malloc) one `person` for each member of the family of that number of generations
// return a pointer to the `person` in the youngest generation.
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *child = malloc(sizeof(person));

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person
        child->parents[0] = parent0;
        child->parents[1] = parent1;

        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        child->alleles[0] = random_parent_allele(*parent0);
        child->alleles[1] = random_parent_allele(*parent1);
        // or
        // child->alleles[0] = child->parents[0]->alleles[rand() % 2];
        // child->alleles[1] = child->parents[1]->alleles[rand() % 2];
    }

    // If there are no generations left to create, i.e. (generations == 1)
    else
    {
        // TODO: Set parent pointers to NULL
        child->parents[0] = NULL;
        child->parents[1] = NULL;

        // TODO: Randomly assign alleles
        child->alleles[0] = random_allele();
        child->alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    // return a pointer for the person that was allocated
    return child;
}

// Free `p` and all ancestors of `p`.
// accept as input a pointer to a person, free memory for that person, and then recursively free memory for all of their ancestors.
void free_family(person *p)
{
    // TODO: Handle base case
    // If the input to the function is NULL, then there’s nothing to free, so your function can return immediately.
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents recursively, call free_family() on two parents
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

// Randomly assign one parent' alleles to child
char random_parent_allele(person parent)
{
    int r = rand() % 2;
    if (r == 0)
    {
        return parent.alleles[0];
    }
    else if (r == 1)
    {
        return parent.alleles[1];
    }
    return 0;
}