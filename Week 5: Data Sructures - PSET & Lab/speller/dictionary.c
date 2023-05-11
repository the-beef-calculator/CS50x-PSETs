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
const unsigned int N = 52;

// Hash table
node *table[N];
void insert(node* n);
int wordCount = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    int index = table[hash(word)];
    node *cursor = table[index]->next;

    while(cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
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

        //insert node
        insert(n);
        wordCount++;

    }


    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return (wordCount != 0 ? size : 0);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}

void insert(node* new_node)
{
    if (new_node == NULL)
    {
        printf("Cannot insert. New node seems to be null.");
        return;
    }
    //store in a variable for cleaner look
    int index = hash(new_node->word);

   //if the index is empty, insert the node
    if(table[index]->next == NULL)
    {
        table[index]->next = new_node;
        return;
    }

    //insert the node at the beginning of the linked list
    new_node->next = table[index]->next;
    table[index]->next = new_node;


}
