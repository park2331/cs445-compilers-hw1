/* tlist.h
 * Linked List data structure prototypes
 */

#ifndef TLIST_H
#define TLIST_H

#include "token.h"

typedef struct node {
  tokenptr t;
  char *filename;
  struct node *next;
} *nodeptr;

/* Node double pointer parameter for pass by reference */
void pop_node(nodeptr*);
void push_node(nodeptr*, char*);
void add_node(nodeptr*, tokenptr);
void print_nodes(nodeptr*);
void delete_all_nodes(nodeptr*); 
void print_stack(nodeptr *top);

#endif /* TLIST_H */
