// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

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

// Represents a hash table
node *hashtable[N];

// Dictionary size
int dictcount = 0;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        node *newnode = malloc(sizeof(node));
        if (!newnode)
        {
            return 1;
        }
        strcpy(newnode->word, word);

        // Test emptiness of hashtable[N]
        if (hashtable[hash(word)] == NULL)
        {
            hashtable[hash(word)] = newnode;
            newnode->next = NULL;
        }
        else
        {
            // If there is already a node in hashtable[N]
            newnode->next = hashtable[hash(word)];
            hashtable[hash(word)] = newnode;
        }

        dictcount++;

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (dictcount > 0)
    {
        return dictcount;
    }
    else
    {
        return false;
    }

    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    node *comp = hashtable[hash(word)];

    while (comp != NULL)
    {
        int result = strcasecmp(comp->word, word);

        if (result == 0)
        {
            return true;
        }
        else
        {
            comp = comp->next;
        }
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *reader;

        reader = hashtable[i];

        while (reader)
        {
            node *tmp = reader;
            reader = reader->next;
            free(tmp);
        }

        // clean the hashtable
        hashtable[i] = NULL;
    }

    return true;
}
