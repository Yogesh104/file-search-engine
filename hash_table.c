#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hash.h"

#define BUFFERSIZE 1024
#define BUFFERHASH 100000

//This stores key, document list pairs
struct word
{
  char *key;
  List *doc_list;
};

//Hashtable datastructure
struct hashtable
{
  List **table;
};

/*
 * purpose: Create a word object
 * input:   The word to be used as a key
 * output:  Word Object
 */
Word *create_word(char *word_name)
{
  Word *new_word = (Word*)malloc(sizeof(Word));
  
  new_word->key = (char*)malloc(sizeof(char) * BUFFERSIZE);
  
  new_word->doc_list = list_create();
  
  return new_word;
}

/*
 * purpose: Provides a hash number
 * input:   The key to be hashed and the size of the table
 * output:  A hash number to be used as an index
 */
unsigned int hashFunction(char *key, int tableSize)
{
  unsigned int hashValue, alpha = 31415,  beta = 27183;
  for (hashValue = 0; *key != 0;
       key++, alpha = alpha*beta % (tableSize-1))
    hashValue = (alpha*hashValue + *key) % tableSize;
  return hashValue;
}


/*
 * purpose: Creates a hashtable
 * input:   N/A
 * output:  A hashtable
 */
HashTable *create_hashtable()
{
  HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
  ht->table = (List**)malloc(sizeof(List*) * BUFFERHASH);
  
  int i;
   
  for(i=0; i < BUFFERHASH; i++)
    {
      ht->table[i] = list_create();
    }
  
  return ht;
}

/*
 * purpose: To act as a compare function for word objects
 * input:   The two words to be compared
 * output:  0 for equal and anything else means they are not equal
 */
int compare_values(const void* gen_word1, const void *gen_word2)
{
  Word* word2 = (Word*)gen_word2;
  
  Word* word1 = (Word*)gen_word1;

  int compare = strcmp(word1->key, word2->key);

  return compare;
}

/*
 * purpose: insert a word and it's document name into the list
 * input:   The hashtable being used, a word key, the document name, and
 *          generic compare function
 * 
 * output:  N/A
 */
void hash_insert (HashTable *ht, char *new_key, char* doc_name, int (*gen_compare)(const void*, const void*))
{
  
  Word* new_word = create_word(new_key);
  
  unsigned int index = hashFunction(new_key, BUFFERHASH);
  
  strcpy(new_word->key, new_key);
  
  Word *compare_word =(Word*) search( ht->table[index], new_word, compare_values);
  
  if(compare_word== NULL)
  {
    
    new_word->doc_list = list_create();
    
    compare_word =(Word*) search(ht->table[index], new_word, compare_values);
    
    new_word->doc_list = list_insert(new_word->doc_list, doc_name);
    ht->table[index] = list_insert(ht->table[index], new_word);    
  }
  
  else
    {
      
      char *compare_docs = (char *) search(compare_word->doc_list, doc_name, gen_compare);
      if(compare_docs == NULL)
  	{
	  compare_word->doc_list = list_insert(compare_word->doc_list, doc_name);
	}
     
    }
}

/*
 * purpose: Search a hashtable for the document list
 * input:   A hashtable, a word key to search by, and a compare function
 * output:  A list of documents
 */
List *hash_find(HashTable *ht, char* search_key,  int (*gen_compare)(const void*, const void*))
{
  
  unsigned int index = hashFunction(search_key, BUFFERHASH);
  
  Word* new_word =(Word*) malloc(sizeof(Word));
  char *doc_name =(char *)malloc(sizeof(char) * BUFFERSIZE);
  
  new_word->key = strdup(search_key);

  if (ht->table[index] == NULL)
    {
      return NULL;
    }
  else
    {
      Word *compare_word =(Word*) search(ht->table[index], new_word, compare_values);
      
      if(compare_word == NULL)
	{
	  return NULL; 
	}
      else
	{
	  return compare_word->doc_list;
	}
    }
}



