#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

unsigned int hash(const char *word);

// Represents number of buckets in a hash table
#define N 26

// Represent a node
typedef struct node
{
    char word[46];
    struct node *next;
}
node;

int main(int argc, char *argv[])
{

    /* *********************************************************************
    ************************************************************************
                OPEN CORRECT DICTIONARY FROM COMMAND LINE INPUT
    ************************************************************************
    ***********************************************************************/

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    char *dictionary = argv[1]; // Get required dictionary filename

    // open dictionary file or return error
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return 2;
    }

    /* *********************************************************************
    ************************************************************************
                            INITIALISE HASHTABLE
    ************************************************************************
    ***********************************************************************/

    node *hashtable[N]; // Main hash table array of size N

    // NULL values as placeholders
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    /* *********************************************************************
    ************************************************************************
                ITERATION OVER WORDS FROM DICT & LOAD INTO HASHTABLE
    ************************************************************************
    ***********************************************************************/

    char new_word[46]; // Buffer for a word

    while (fscanf(file, "%s", new_word) != EOF) // Iterate over each new word from the dictionary until end of file
    {
        unsigned int hash_val = hash(new_word); // Get hash value for new word
        printf("%i - %c\n", hash_val, new_word[0]); // Optional print check

        node *n = malloc(sizeof(node)); // Allocate node for new word - store pointer in n

        if (n == NULL) // Check malloc worked ok
        {
            return 1;
        }

        strcpy(n->word, new_word);  // Set node.word to new word
        n->next = hashtable[hash_val]; // Set node.next to point same as current main array pointer
        hashtable[hash_val] = n; // set main array to point to newly inserted node
    }

    /* *********************************************************************
    ************************************************************************
                        PRINT ALL ENTRIES INTO HASHTABLE
    ************************************************************************
    ***********************************************************************/

    for (int i = 0; i < N; i++)  // Iterate over each main array element
    {
        if (hashtable[i] != NULL) // Skip if array element empty/NULL
        {
            node *tmp = hashtable[i]; // Temp node = first in linked list
            printf("%s\n", tmp->word); // Print word from this node

            while (tmp->next != NULL) // Set loop to move along linked list until nodes next is NULL
            {
                *tmp = *tmp->next; // Move onto next node in linked list
                printf("%s\n", tmp->word); // Print word from this node
            }
        }

    }

}

    /* *********************************************************************
    ************************************************************************
                                    FUNCTIONS
    ************************************************************************
    ***********************************************************************/

// Function to hash word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}
