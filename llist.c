/* llist.c
 * Linked List data structure code
 */
#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

void add_node(nodeptr *head, int value) {
  nodeptr a = malloc(sizeof(struct node));
  a->code = value;
  a->next = NULL;
  if (*head == NULL) {
    *head = a;
  } else {
    nodeptr t = *head;
    while (t->next != NULL) {
      t = t->next;
    }
    t->next = a;
  }
}

void print_nodes(nodeptr *head) {
  nodeptr t = *head;
  while (t != NULL) {
    printf("%d\n",t->code);
    t = t->next;
  }
}
