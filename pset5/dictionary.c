/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Hashtable size
#define SIZE 200000

// Node structure for linked list
typedef struct node 
{
    char word[46];
    struct node* next; 
} node;

// creates a hashtable
node *hashtable[SIZE] = {NULL};

/**
 * Creates and returns a empty node
 */
node *createNode()
{
    node *newNode = (node*)calloc(1, sizeof(node));
    if(newNode == NULL) return false;
  
    return newNode;
}

/**
 * Hashing function for hashtable (lose lose - http://www.cse.yorku.ca/~oz/hash.html)
 */
int hash(const char* word)
{
   int hash = 0;
    
   for(int i = 0; word[i] != '\0'; i++)
   {
      hash += word[i];
   }

   return hash;
}

int sizeOfDictionary = 0; // keeps track of dictionary size      

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char temp[46];
    int len = 0;
    for(int i = 0; word[i] != '\0'; i++){
        temp[i] = tolower(word[i]);
        len++;
    }
    temp[len] = '\0';
    
    int i = hash(temp);
    
    if(hashtable[i] == NULL)
        return false;
    
    node *iterator = hashtable[i];
    
    while(iterator != NULL)
    {
        if(strcmp(iterator->word, temp) == 0)
            return true;
        iterator = iterator->next;
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    char word[46];
    
    FILE *dic = fopen(dictionary, "r");
    if(dic == NULL) return false;
    
    while(fscanf(dic, "%s\n", word) != EOF)
    {   
        node *newNode = createNode();
        
        strcpy(newNode->word, word);
        
        int i = hash(word);
        
        if(hashtable[i] == NULL)
        {
            hashtable[i] = newNode;
            newNode->next = NULL;
        }
        else
        {
            newNode->next = hashtable[i];
            hashtable[i] = newNode;
        }
        
        sizeOfDictionary++; 
    }
    
    fclose(dic);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(sizeOfDictionary > 0)
        return sizeOfDictionary;
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i <= sizeOfDictionary; i++)
    {
        while(hashtable[i] != NULL)
        {
            node* iterator = hashtable[i];
            hashtable[i] = iterator->next;
            free(iterator);
        }  
    }
    return true;
}
