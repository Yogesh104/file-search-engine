

typedef struct node Node;
typedef Node List;     

/*
 * purpose: create a new linked list
 * input:   nothing!
 * output:  an empty linked list 
 */
List *list_create();

/*
 * purpose: print a linked list
 * input:   a description and the list to print!
 * output:  nothing
 */
void list_print(char *description, List *head, void (*gen_print)(const void*));

/*
 * purpose: insert a value into a linked list
 * input:   the head of the list and the value to insert!
 * output:  the updated list
 */
List *list_insert(List *head, void *new_value);

/*
 * purpose: search a linked list
 * input:   The head, generic value to search for, and compare function
 * output:  Node value
 */
void* search(List *head, void *search_node, int (*gen_compare)(const void*, const void*));

 
