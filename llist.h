/* llist.h
 * Linked List data structure prototypes
 */

#ifndef LLIST_H
#define LLIST_H

typedef struct node {
  int code;
  struct node *next;
} *nodeptr;

typedef struct list {
  nodeptr head;
  nodeptr tail;
} *listptr;

/* Node double pointer parameter for pass by reference */
void add_node(nodeptr*, int);
void print_nodes(nodeptr*);

#endif /* LLIST_H */
