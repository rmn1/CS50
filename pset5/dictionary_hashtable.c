/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Hashtable implementation (change filename to "dictionary.c" before compiling)
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
  
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
  
#include "dictionary.h"
 
#define SIZE 100000
 
// hashtable struct
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
} node;
 
struct node* hashtable[SIZE] = {NULL}; // NEED TO SET SIZE OF TABLE
 
int dictionary_size = 0; // global variable to store size of dictionary (counted while loaded)
 
// djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(const char* str)
{
    unsigned long hash = 5381;
    int c;
 
    while ((c = *str++))
    {
        hash = (((hash << 5) + hash) + c) % SIZE; /* hash * 33 + c */
    }
 
    return hash;
}
 
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // store lower-case version of word checked in temp to ensure case-insensitivity
    int wordlen = strlen(word);
    char temp[wordlen+1];
    for (int i = 0; i < wordlen; ++i)
    {
        temp[i] = tolower(word[i]);
    }
    temp[wordlen] = '\0';
    
    // hash word to find correct element of hashtable to search   
    int index = hash(temp);
     
    if (hashtable[index] == NULL)
    {
        return false;
    }
 
    node* cursor = hashtable[index];
         
    // traverse through list and compare each dictionary word to word from text as long as word not found
    while (cursor != NULL && strcmp(temp, cursor->word) != 0)
    {
        cursor = cursor->next;
    }
    
    // if reached end of list - word was not found, thus misspelled
    if (cursor == NULL) return false;
    
    // otherwise - while loop was terminated because word was found
    return true;
}
 
/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* fp = fopen(dictionary, "r");
     
    if (fp == NULL) return false;
     
    // temp variable to store words as read from file before copying to node for insertion into list
    char temp_word[LENGTH+1];
     
    //while (fgets(current_word->word, LENGTH, fp) != NULL)
    while (fscanf(fp, "%s\n", temp_word) != EOF)
    {
        // get dictionary size while reading from dictionary
        ++dictionary_size;
         
        node* current_word = malloc(sizeof(node));
         
        // save all dictionary words as lower case to ensure case insensitivity
        for (int i = 0; i < strlen(temp_word); ++i)
        {
            temp_word[i] = tolower(temp_word[i]);
        }
 
        strcpy(current_word->word, temp_word);
                 
        // HASH current_word to obtain value of index of element in table to insert current_word
        int index = hash(temp_word);
         
        // INSERT current_word into hashtable at index of hash value         
        if (hashtable[index] == NULL)
        {
            hashtable[index] = current_word;
            current_word->next = NULL;
        }
        else
        {
            current_word->next = hashtable[index];
            hashtable[index] = current_word;
        }
         
        /* Sorting before insertion actually does not make it faster
        {
            node* prev = NULL;
            node* cursor = hashtable[index];
             
            while ((cursor != NULL) && (strcmp(current_word->word, cursor->word) < 0))
            {
                prev = cursor;
                cursor = cursor->next;
            }
             
            current_word->next = cursor;
             
            // no entries under this index yet - insert at beginning
            if (prev == NULL)
            {
                hashtable[index] = current_word;
            }
            // insert in middle or end
            else
            {
                prev->next = current_word;
            }  
        } */ 
    }
     
    fclose(fp);
    return true;
}
  
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dictionary_size) return dictionary_size;
     
    // if not loaded or size is 0
    return 0;
}
  
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (hashtable[i] != NULL)
        {
            node* cursor = hashtable[i];
             
            while (cursor != NULL)
            {
                node* temp = cursor;
                cursor = cursor->next;
                free(temp);
            }
        }
    }
     
    return true;
}