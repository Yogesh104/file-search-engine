#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node{            
    void *value;
    Node *next;
};

/*
 * purpose: create a new linked list
 * input:   nothing!
 * output:  an empty linked list 
 */
List *list_create()
{
   Node *dummy =  malloc(sizeof(Node));
   if (dummy == NULL)
     {
       fprintf(stderr, "Out of memory\n");
       exit(-1);
     }
    dummy->value = NULL;
    dummy->next = NULL;
    return dummy;
}

/*
 * purpose: print a linked list
 * input:   a description and the list to print!
 * output:  nothing [[ (why it prints stuff???) ]]
 */
void list_print(char *description, List *head, void (*gen_print)(const void*))
{
  printf("%s", description);
  if(head == NULL)
    {
      fprintf(stderr, " Search Query Not Found");
    }
   else 
    {
      Node *tmp; 
       // [[ head->next skips the dummy header ]] 
      for( tmp = head->next; tmp != NULL; tmp = tmp->next)
	gen_print(tmp->value);
      printf("\n");
    }
}

/*
 * purpose: insert a value into a linked list
 * input:   the head of the list and the value to insert!
 * output:  the updated list
 */
List *list_insert(List *head, void *new_value)
{
  Node *new_node = malloc(sizeof(Node));
  if (new_node == NULL) 
    {
      fprintf(stderr, "Out of memory\n");  
      exit(-1); 
    }
  
  new_node->value = new_value; 
  new_node->next = NULL;

 // head should not be null, but in case it is .... 
  if (head == NULL) 
    {
      head = list_create();
    }

 // we never insert before the dummy header, so only the 'insert middle 
 // and end' cases are needed!
  Node *tmp;
  for(tmp = head; tmp->next != NULL; tmp = tmp->next) {
    if (new_value < tmp->next->value) 
     {
       new_node->next = tmp->next; tmp->next = new_node;
       return head;
     } 
  }
  tmp->next = new_node;
  
  return head;
}

/*
 * purpose: search a linked list
 * input:   The head, generic value to search for, and compare function
 * output:  Node value
 */
void *search(List *head, void *search_node, int (*gen_compare)(const void*, const void*))
{
  Node *tmp;
  for( tmp = head->next; tmp != NULL; tmp = tmp->next)
    {	
      if(gen_compare(tmp->value, search_node) == 0)
	{
	
	  return tmp->value;
	}
     
    
    }

   return NULL;
}


