/* tlist.c
 * Linked List data structure code
 */
#include <stdlib.h>
#include <stdio.h>
#include "tlist.h"

/* Add token to linked list */
void add_node(nodeptr *head, tokenptr value) {
  nodeptr a = malloc(sizeof(struct node));
  a->t = value;
  a->next = NULL;
  if (*head == NULL) {
    *head = a;
  } else {
    nodeptr go = *head;
    while (go->next != NULL) {
      go = go->next;
    }
    go->next = a;
  }
}

void print_nodes(nodeptr *head) {
  nodeptr go = *head;
  while (go != NULL) {
    printf("TOKEN: %d\n",go->t->category);
    go = go->next;
  }
}

void delete_all_nodes(nodeptr *head) {
  nodeptr go = *head;
  while (go != NULL) {
    nodeptr del = go;
    go = go->next;
    free(del);
  }
}
