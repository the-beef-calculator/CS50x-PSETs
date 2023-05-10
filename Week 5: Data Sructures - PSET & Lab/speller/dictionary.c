// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");

    if (f == NULL)
    {
        return false;
    }

    char dictWord[LENGTH + 1];

    while(!(fscanf(f,"%s",dictWord)))
    {
        //allocate memory for the node
        node *n = malloc(sizeof(node));

        //copy word that was read from scanf into node
        strcpy(n->word, dictWord);

        //insert node into hashtable if it is the first node
        if (table[hash(n->word) == NULL])
        {
            table[hash(n->word)] = n;
        }
        else

    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}

void insert(node* table[], node* node);
{
    if(table[hash(node->word)] == NULL)
    {
        table[hash(n->word)] = n;
        return;
    }

    else if(table[hash(node->word)]->next == NULL)
    {
        table[hash(n->word)] = n;
        return;
    }

    else
    {
        insert(table[], )
    }

}
