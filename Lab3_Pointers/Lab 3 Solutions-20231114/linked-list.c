#include <stdlib.h>
#include <stdio.h>

struct node {
    char value;
    struct node * next;
};

struct node* create_node(char value) {
  struct node * node_ptr = malloc(sizeof(struct node));
  if (node_ptr==NULL)
    return NULL;
  node_ptr->value = value;
  node_ptr->next = NULL;
  return node_ptr;
}

void free_list(struct node* list) {
  if (!list)
    return;
  while (list->next) {
    struct node* head = list;
    list = list->next;
    free(head);
    head=NULL;
  }
}

void print_list(struct node* list) {
    while (list) {
      printf("%c-", list->value);
      list = list->next;
    }
    printf("\n");
}

int main () {
    char course[] = "Systems Programming";
    struct node* last_node = NULL;
    struct node* head = NULL;
    for (int i=0; course[i]!='\0'; i++) {
        struct node* new_node = create_node(course[i]);
        if(!new_node) {
            printf("Could not create new node\nExiting...\n");
            return -1;
        }
        if (last_node) {
            last_node->next = new_node;
        } else {
            head = new_node;
        }
        last_node = new_node;
    }
    print_list(head);
    free_list(head);
    head=NULL;
    print_list(head);
}