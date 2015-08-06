/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Trie implementation (change filename to "dictionary.c" before compiling)
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

#define ALPHABET_SIZE 27

unsigned int dictionary_size = 0;

// TRIE
typedef struct node
{
    bool is_word;
    struct node* children[ALPHABET_SIZE];
} node;

// init trie
struct node* root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // store lower-case version of word checked in temp to ensure case-insensitivity
    int wordlen = strlen(word);
    //char current_word[LENGTH+1] = word;
    int letter;
    
    struct node* cursor = root;    

    for (int i = 0; i < wordlen; ++i)
    {
        if (isalpha(word[i]))
        {
            letter = tolower(word[i]) - 'a';
        }
        else if (word[i] == '\'')
        {
            letter = ALPHABET_SIZE - 1;
        }
        // word[wordlen] = '\0';
        
        if (cursor->children[letter] == NULL)
        {
            return false;
        }
        cursor = cursor->children[letter];
    }

    return cursor->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL) return false;

    // variable to store words as read from file
    char current_word[LENGTH+1];
    
    root = calloc(1,sizeof(node));
    
    
    while (fscanf(fp, "%s\n", current_word) != EOF)
    {
        // get dictionary size while reading from dictionary
        ++dictionary_size;
        
        int letter;
        int wordlen = strlen(current_word);
        struct node* cursor = root;

        // save all dictionary words as lower case to ensure case insensitivity
        // traverse trie and add word
        for (int i = 0; i < wordlen; ++i)
        {
            if (isalpha(current_word[i]))
            {
                current_word[i] = tolower(current_word[i]);
                letter = current_word[i] - 'a';
            }
            else if (current_word[i] == '\'')
            {
                letter = ALPHABET_SIZE - 1;
            }
            else
            {
                return false;
            }
            current_word[wordlen] = '\0';
            
            if (cursor->children[letter] == NULL)
            {
                cursor->children[letter] = calloc(1,sizeof(node));
            }
            
            cursor = cursor->children[letter];
        }
        
        cursor->is_word = true;
    }
        
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionary_size;
}

void free_node(struct node* cursor) 
{
    if (cursor == NULL) return;
    
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (cursor->children[i] != NULL)
        {
            free_node(cursor->children[i]);
        }
    }
    
    free(cursor); 
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    free_node(root);
    
    return true;
}