#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "list.h"

#define BUFFERSIZE 1024


/*
 * purpose: To clean a word of punctuation and symbols
 * input:   A word
 * output:  The word without punctuation or symbols
 */
char *clean_word(char *input) {
 int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)          
    {
        if (isalnum(input[i]))                           
            output[j]=input[i];                     
        else
            j--;                                     
    }
    output[j]=0;
    return output;
}

/*
 * purpose: To act as a compare function for char objects
 * input:   The two words to be compared
 * output:  0 for equal and anything else means they are not equal
 */
int compare_words(const void* gen_word1, const void *gen_word2)
{
  
  char* word1 = (char*)gen_word1;
  char* word2 = (char*)gen_word2;

  int compare = strcmp(word1, word2);
  if(compare==0)
    {
      return 0;
    }
  else if(compare > 0 )
    {
      return 1;
    }
  else
    {
      return -1;
    }
}

/*
 * purpose: Is used to help print the linked list
 * input:   The word to be printed
 * output:  N/A
 */
void print_word(const void* gen_word1)
{
  char *word1 = (char*)gen_word1;
  printf("%s ", word1);
}

/*
 * purpose: Indexing and Querying is done in Main
 */
int main(int argc, char *argv[])
{

  if(argc < 2)
    {
      fprintf(stderr, "Hashtable <stoplist> <documents>");
      exit(1);
    }

  HashTable *stop_words = create_hashtable();
  
 
  
  char *str_stop;
  char stopWord[BUFFERSIZE];
  
  FILE* stop_file = NULL;//FILE POINTER SET TO NULL
     
     
  stop_file = fopen(argv[1], "r");
  
  int a = 0;
  if(stop_file == NULL){//IF FILE DOESNT EXIST END PROGRAM
    printf("Could not open the file");
    exit(-1);
  }
   //Creating a hashtable of "stop words" in this loop 
  while(fscanf(stop_file, "%s",stopWord) != EOF)
    {
      
      char *str_stop = (char*)malloc(sizeof(char) * BUFFERSIZE);
      str_stop = strdup(&stopWord[0]);
      
      str_stop = clean_word(str_stop);
 
      hash_insert(stop_words, str_stop, argv[1], compare_words); 
      
    }
  

  
  
  
  int i;
  char *str;
  char theWord[BUFFERSIZE];
  HashTable* hasht = create_hashtable();
  FILE* in_file = NULL;//FILE POINTER SET TO NULL
  List* stop_list = list_create();
  for(i = 2; i < argc; i++)
    {
      
      in_file = fopen(argv[i], "r");
      
      int a = 0;
      if(in_file == NULL){//IF FILE DOESNT EXIST END PROGRAM
	printf("Could not open the file");
	exit(-1);
      }
      //Indexing the hashtable in this loop
      while(fscanf(in_file, "%s",theWord) != EOF)
	{
	  
	  char *str = (char*)malloc(sizeof(char) * BUFFERSIZE);
	  str = strdup(&theWord[0]);
	  
	  str = clean_word(str);
	  
	  stop_list = hash_find(stop_words, str, compare_words);
	   if(stop_list == NULL)
	     {
	       
	       hash_insert(hasht, str, argv[i], compare_words); 
	     }
	   
	}
    }

  //This hashtable only handles single word queries!
  char *query = (char *)malloc(sizeof(char) * BUFFERSIZE);
  printf("What is your single word query: \n");
  scanf("%s",query); 
  List *finding = hash_find(hasht, query, compare_words);
  printf("\n");
  list_print("YOUR DOCUMENTS: ", finding, print_word);

}
