/* tlist.h
 * Linked List data structure prototypes
 */

#ifndef TLIST_H
#define TLIST_H

#include "token.h"

typedef struct node {
  tokenptr t;
  struct node *next;
} *nodeptr;

typedef struct list {
  nodeptr head;
  nodeptr tail;
} *listptr;

/* Node double pointer parameter for pass by reference */
void add_node(nodeptr*, tokenptr);
void print_nodes(nodeptr*);
void delete_all_nodes(nodeptr*); 

#endif /* TLIST_H */
