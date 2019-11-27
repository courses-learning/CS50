// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Main hash table array of size N
node *hashtable[N];


/* *********************************************************************
************************************************************************
                HASH FUNCTION - DEFAULT FIRST LETTER
************************************************************************
***********************************************************************/

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}


/* *********************************************************************
************************************************************************
                DICTONARY LOAD TO MEMORY FUNCTION
             RETURNS TRUE IF SUCCESSFULL ELSE FALSE
************************************************************************
***********************************************************************/

bool load(const char *dictionary)
{
    /* *********************************************************************
                            INITIALISE HASHTABLE
    ***********************************************************************/

    // NULL values as placeholders
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    /* *********************************************************************
                OPEN CORRECT DICTIONARY FROM COMMAND LINE INPUT
    ***********************************************************************/

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    /* *********************************************************************
            ITERATION OVER WORDS FROM DICT FILE & LOAD INTO HASHTABLE
    ***********************************************************************/

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF) // Iterate over each new word from the dictionary until end of file
    {
        unsigned int hash_val = hash(word); // Get hash value for new word

        node *n = malloc(sizeof(node)); // Allocate node for new word - store pointer in n

        if (n == NULL) // Check malloc worked ok
        {
            return 1;
        }

        strcpy(n->word, word);  // Set node.word to new word
        n->next = hashtable[hash_val]; // Set node.next to point same as current main array pointer
        hashtable[hash_val] = n; // set main array to point to newly inserted node
    }


    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}


/* *********************************************************************
************************************************************************
    DICTONARY WORD COUNT FUNCTION - RETURNS NO OF WORDS LOADED INTO
                    DICTIONARY OR 0 IF NOT YET LOADED
************************************************************************
***********************************************************************/

unsigned int size(void)
{
    unsigned int count = 0;
    for (int i = 0; i < N; i++)  // Iterate over each main array element
    {
        if (hashtable[i] != NULL) // Skip if array element empty/NULL
        {
            node *tmp = hashtable[i]; // Temp node = first in linked list
            count++;
            // printf("%s\n", tmp->word); // Print word from this node

            while (tmp->next != NULL) // Set loop to move along linked list until nodes next is NULL
            {
                *tmp = *tmp->next; // Move onto next node in linked list
                count++;
                // printf("%s\n", tmp->word); // Print word from this node
            }
        }

    }

    return count; // will return 0 if not loaded otherwise no of words
}


/* *********************************************************************
************************************************************************
    DICTONARY CHECK FUNCTION - RETURNS TRUE IF WORD FOUND ELSE FALSE
************************************************************************
***********************************************************************/

bool check(const char *word)
{
    // Make copy of word so type not const
    char lower_word[strlen(word) + 1];
    strcpy(lower_word, word);

    // change copy of word to lowercase ready for hash
    for(int i = 0; i < strlen(word); i++)
    {
        lower_word[i] = tolower(lower_word[i]);
    }

    node *cursor = hashtable[hash(lower_word)]; // cursor to first node in hashtable @ hash value for lower word

    while (cursor != NULL) // loop to end of linked list i.e. when cursor becomes NULL
    {
        if (strcasecmp(lower_word, cursor->word) == 0) // compare words
        {
            return true; // match found
        }
        else
        {
            cursor = cursor->next; // move cursor to next linked list entry if no match
        }
    }

    return false; // no match found
}


/* *********************************************************************
************************************************************************
                            UNLOAD FUNCTION
************************************************************************
***********************************************************************/

bool unload(void)
{
    for (int i = 0; i < N; i++)  // Iterate over each main array element
    {
        if (hashtable[i] != NULL) // Skip if array element empty/NULL
        {
            node *cursor = hashtable[i]; // cursor node = first in linked list

            while (cursor != NULL) // Set loop to move cursor along linked list until NULL
            {
                node *tmp = cursor; // set tmp to node to be freed
                cursor = tmp->next; // Move cursor onto next node in linked list
                free(tmp);
            }
        }
    }
    return true;
}
