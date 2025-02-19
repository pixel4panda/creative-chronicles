// "Speller" assignment for CS50 2025 
// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// Alphabetical order first 2 letters 26 * 27 (including apostrophe as second letter)
const unsigned int N = 702;

// Hash table
node *table[N];

// Dictionary size
int word_count = 0;

// Assisting functions _byPixel4Panda
// Adds node to hash table
void add_node(unsigned int h, char *prompt)
{
    // Assign space in memory for node
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("Error adding node.\n");
        return;
    }

    // Populate node
    strcpy(n->word, prompt);
    n->next = NULL;

    // Place node in the beginning of the list
    n->next = table[h];
    table[h] = n;

    return;
}

// End of assisting functions _byPixel4Panda

// Assignment functions _byPixel4Panda
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain its index
    unsigned int h = hash(word);
    // Go to table[h] and search word in the list
    for (node *n = table[h]; n != NULL; n = n->next)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
    }

    // Checked the entire list and the word is not there
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash number composed of 2 first letters h0 and h1
    unsigned int h, h0, h1;

    // All words will have a first letter, which is not apostrophe
    h0 = (tolower(word[0]) - 'a') * 27;

    // If it is a single letter word
    if (word[1] == '\0' || word[1] == '\n')
    {
        h1 = 0;
    }
    // If the second letter is actually an apostrophe
    else if (word[1] == '\'')
    {
        h1 = 26;
    }
    else
    {
        h1 = tolower(word[1]) - 'a';
    }

    // Add them together
    h = h0 + h1;

    return h;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return false;
    }

    // Read each word
    char buffer[LENGTH + 1];
    while (fscanf(source, "%s", buffer) != EOF)
    {
        // Hash word
        unsigned int h = hash(buffer);
        // Prepend it to list in designated node
        add_node(h, buffer);
        word_count++;
    }

    // Close file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Circle through the entire table
    for (int i = 0; i < N; i++)
    {
        // Creates temporary node to avoid leaks
        node *temp = table[i];
        // Keeps deleting the front member of the list and reseting its top
        while (temp != NULL)
        {
            temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
