#include "list.h"



typedef struct word Word; //This stores key, document list pairs

typedef struct hashtable ht;
typedef ht HashTable; //Hashtable datastructure


/*
 * purpose: Create a word object
 * input:   The word to be used as a key
 * output:  Word Object
 */
Word *create_word(char *word_name);

/*
 * purpose: Provides a hash number
 * input:   The key to be hashed and the size of the table
 * output:  A hash number to be used as an index
 */
unsigned int hashFunction(char *key, int tableSize);

/*
 * purpose: Creates a hashtable
 * input:   N/A
 * output:  A hashtable
 */
HashTable *create_hashtable();

/*
 * purpose: To act as a compare function for word objects
 * input:   The two words to be compared
 * output:  0 for equal and anything else means they are not equal
 */
int compare_values(const void* gen_word1, const void *gen_word2);

/*
 * purpose: insert a word and it's document name into the list
 * input:   The hashtable being used, a word key, the document name, and
 *          generic compare function
 * 
 * output:  N/A
 */
void hash_insert (HashTable *ht, char *new_key, char* doc_name, int (*gen_compare)(const void*, const void*));

/*
 * purpose: Search a hashtable for the document list
 * input:   A hashtable, a word key to search by, and a compare function
 * output:  A list of documents
 */
List *hash_find(HashTable *ht, char* search_key,  int (*gen_compare)(const void*, const void*));

