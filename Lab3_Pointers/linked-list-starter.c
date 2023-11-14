#include <stdlib.h>
#include <stdio.h>

struct node {
    char value;
    struct node * next;
};

struct node* create_node(char value) {
    // TODO: allocate memory space and initialise struct members
    struct node *n = NULL;

    n = (struct node *) malloc(sizeof(struct node));
    if (!n)
    {
        return NULL;
    }

    n->value = value;
    n->next = NULL;
    
    return n;
}

void free_list(struct node* list) {
    // TODO: free all allocated memory space starting from the head of the list

    struct node *p;

    while (list)
    {
        p = list->next;
        free(list);
        list = p;
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