/* tlist.c
 * Linked List data structure code
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tlist.h"
#include "token.h"

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

void push_fname(nodeptr *head, char *fname) {
  nodeptr a = malloc(sizeof(struct node));
  a->filename = malloc(sizeof(fname)+1);
  a->next = NULL;

  strcpy(a->filename, fname);
  if (*head == NULL) {
    *head = a;
  } else {
    a->next = *head;
  }
}

void pop_fname(nodeptr *head) {
  nodeptr popped;
  popped = *head;
  *head = (*head)->next;
  free(popped);
}

void print_nodes(nodeptr *head) {
  nodeptr go = *head;
  while (go != NULL) {
    //    printf("TOKEN: %d\n",go->t->category);
    print_token(go->t);
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
