// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
unsigned int size_library;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int i;
    i = hash(word);
    // printf("%i ", i);

    for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char   palavra[LENGTH + 1];
    int    hash;

    strcpy(palavra, word);

    hash = tolower(palavra[0]) - 97;

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dicionario = NULL;
    dicionario = fopen(dictionary, "r");

    if (dicionario == NULL)
    {
        printf("falha ao abrir dicionario!");
    }
    else
    {
        printf("dicionario aberto com sucesso!");
    }

    int     idx, i = 1, x = 0;
    char    palavra[LENGTH + 1];

    while (fscanf(dicionario, "%s", palavra) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Falha na alocação de memória.\n");
            free(table);
            return false;
        }

        strcpy(n->word, palavra);
        n->next = NULL;

        idx = hash(n->word);
        if (idx == i)
        {
            table[idx] = NULL;
            table[idx] = n;
            i++;
        }
        else
        {
            n->next = table[idx];
            table[idx] = n;
        }
        x++;
    }

    fclose(dicionario);

    size_library = size();
    if (x == size_library)
    {
        return true;
    }

    return false;
}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int x = 0, i = 0;

    while (i < 26)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            x++;
        }
        i++;
    }

    if (x > 0)
    {
      return x;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int i = 0;

    // Liberar memória alocada
    for (int j = 0; j < 26; j++)
    {
        while (table[j] != NULL)
        {
            node *temp = table[j];
            table[j] = table[j]->next;
            free(temp);
            i++;
        }
    }

    if (i == size_library)
    {
        return true;
    }

    return false;
}