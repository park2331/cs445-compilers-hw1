/* tlist.c
 * Linked List data structure code
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tlist.h"
#include "token.h"


void print_stack(nodeptr *top) {
  if(*top == NULL) {
    printf("EMPTY STACK\n");
    
  } else {
    nodeptr temp;
    temp = *top;
    while (temp != NULL) {
      printf("%s\n",temp->filename);
      temp = temp->next;
    }
  }
}

void pop_node(nodeptr *top) {
  nodeptr temp;
  temp = *top;
  *top = (*top)->next;
  free(temp);
}

/* Push node on char* stack for filenames */
void push_node(nodeptr *top, char *fname) {
  nodeptr temp = (nodeptr)malloc(sizeof(struct node));
  temp->filename = malloc(sizeof(fname)+1);
  temp->next = NULL;
  strcpy(temp->filename, fname);

  if(top == NULL) {
    *top = temp;
  } else {
    temp->next = *top;
    *top = temp;
  }
}

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
