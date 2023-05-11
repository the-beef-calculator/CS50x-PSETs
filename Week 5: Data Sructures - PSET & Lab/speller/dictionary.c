// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
void insert(node* n);
int wordCount = 0;
void freeLinkedList(node* n);
// Returns true if word is in dictionary, else false
bool check(const char *word)
{


    int index = hash(word);

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
   //initializing hash table
   for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        if (table[i] == NULL)
        {
            printf("Memory allocation failed.");
            return false;
        }
        table[i]->next = NULL;
    }



    FILE *f = fopen(dictionary, "r");

    if (f == NULL)
    {
        return false;
    }

    char dictWord[LENGTH + 1];

    while((fscanf(f,"%s",dictWord)) == 1)
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
    return (wordCount != 0 ? wordCount : 0);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    if(table[0] == NULL)
    {
        return false;
    }

    int i = N-1;

    while (i >= 0)
    {
        freeLinkedList(table[i]->next);
        i--;
    }

    return true;

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


    //insert the node at the beginning of the linked list
    new_node->next = table[index]->next;
    table[index]->next = new_node;


}

void freeLinkedList(node* cursor)
{

    node *temp;
    while (cursor != NULL)
    {
        temp = cursor;
        cursor = cursor->next;
        free(temp);
    }

}

