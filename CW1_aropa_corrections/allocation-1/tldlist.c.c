#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tldlist.h"
#include "date.h"

 struct tldnode {
    //basing this off of previous doubly linked list implementation based on ADS2 coursework I did
    char *tld;
    long nodeCount;
    TLDNode *rightChild;
    TLDNode *leftChild;
    TLDNode *next;
    TLDNode *prev;

};

struct tldlist {
    Date *begin;
    Date *end;
    long long total;
    TLDNode *root;
    TLDNode *head;
    TLDNode *tail;

};

struct tlditerator {
    TLDNode *currentNode;
};

char *strdup(const char *s) {
    char *newStr = malloc(strlen(s) + 1);

    if (newStr == NULL) {
        return NULL;
    }

    strcpy(newStr, s);

    return newStr;
}


TLDList *tldlist_create(Date *begin, Date *end) {
    TLDList *newList = malloc(sizeof(TLDList));

    if (!newList) {
        return NULL;
    }
    // initialising the new tldlist with variables from the tldlist struct
    newList->begin = begin;
    newList->end = end;
    newList->head = NULL;
    newList->root = NULL;
    newList->tail = NULL;
    newList->total = 0;

    return newList;
}

// helper function which recursively calls itself to free nodes and their left & right children
void freeNode(TLDNode *node) {
    if (node != NULL) {
        freeNode(node->rightChild);
        freeNode(node->leftChild);
        free(node->tld);
        free(node);
    }
}

void tldlist_destroy(TLDList *tld) {
    if (tld) {
        // calls the helper function freeNode to free all nodes memory from heap
        // starting at the root
        freeNode(tld->root);
        // frees rest of variables in tldlist struct & frees tld fully just to be safe
        // found out using valgrind that this freeing of the Date type begin & end variables
        // was creating double free error as it was freed twice with the tld that's below
//        free(tld->begin);
//        free(tld->end);
        free(tld);
    }
}

// helper function for tldlist_add which creates nodes for the BST
TLDNode *createNode(char *tld) {
    TLDNode *newNode = malloc(sizeof(TLDNode));

    if (!newNode) {
        return NULL;
    }

    // initialises all node attribute variables
    // uses strdup() to dynamically copy the top level domain string to the newNode variable
    newNode->tld = strdup(tld);

    if (newNode->tld == NULL) {
        freeNode(newNode);
        return NULL;
    }

    newNode->nodeCount = 1;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

// helper function for tldlist_add to actually inserts nodes in BST
TLDNode *insert_tldNode(TLDList *tld, TLDNode *root, char *codeWithoutDot) {
    TLDNode *newNode = NULL;
    //base case if there is no root in BST create it
    if (!root) {
        newNode = createNode(codeWithoutDot);

        //initialising and updating linked list based on BST
        //if there is no head pointer meaning tld list is empty point both
        //head and tail pointers to the newNode
        if (!tld->head) {
            tld->head = newNode;
            tld->tail = newNode;
        } else {
            // points both prev and next pointers to the node previous to tail
            // maintians the doubly linked list connection
            tld->tail->next = newNode;
            newNode->prev = tld->tail;
            tld->tail = newNode;
        }

        return newNode;
    }

    // using strcmp() to compare strings lexicographically then outputs result as int
    int compareNum = strcmp(codeWithoutDot, root->tld);

    // if the code is less than the root it is placed on the left side
    // if the code is greater than the root it is placed on the right side
    // else it already exists therefore we just increment its count
    if (compareNum < 0) {
        root->leftChild = insert_tldNode(tld, root->leftChild, codeWithoutDot);
    } else if (compareNum > 0) {
        root->rightChild = insert_tldNode(tld, root->rightChild, codeWithoutDot);
    } else {
        root->nodeCount++;
    }

    return root;
}

int tldlist_add(TLDList *tld, char *hostname, Date *d) {
    // uses date_compare() function implementation from date.c
    // checks if the hostname date is within the bounds of the date filter or not
    // if not the function returns 0 (exits)
    if (date_compare(d, tld->begin) < 0 || date_compare(d, tld->end) > 0) {
        return 0;
    }

    // constants to highlight the meaning of each number/char used
    const char dot = '.';
    const int maxCodeLen = 3;
    const int skipDot = 1;
    char *codeWithDot;
    char *codeWithoutDot;

    // converts the hostname string to lowercase to allow for case insensitivity
    for (int i = 0; i < strlen(hostname); i++) {
        hostname[i] = tolower(hostname[i]);
    }

    // strrchr() used to find the last occurence of the dot
    // this is then stored in another char* variable named codeWithoutDot
    // which moves the char array by 1 to skip the dot
    codeWithDot = strrchr(hostname, dot);
    codeWithoutDot = codeWithDot + skipDot;
    int codeLen = strlen(codeWithoutDot);

    // condition to check if the code in the domain is > 3 (limit of code as specified in requirements)
    // Or if there is no code without a dot it should exit
    if (codeLen > maxCodeLen || !codeWithoutDot) {
        return 0;
    }

    // calls the root to then insert this code as a node in the BST
    // and uses the pointers within the insert_tldNode() to highlight the use of the doubly linked list for later traversal
    tld->root = insert_tldNode(tld, tld->root, codeWithoutDot);
    tld->total++;

    return 1;
}


long tldlist_count(TLDList *tld) {
    return tld->total;
}

TLDIterator *tldlist_iter_create(TLDList *tld) {
    if (!tld) {
        return NULL;
    }

    TLDIterator *iterator = malloc(sizeof(TLDIterator));

    if (!iterator) {
        return NULL;
    }
    // sets the new iterator for the tldlist as the head of the doubly linked list
    iterator->currentNode = tld->head;

    return iterator;
}

TLDNode *tldlist_iter_next(TLDIterator *iter) {
    if (!iter || !iter->currentNode) {
        return NULL;
    }

    // calls the currentNode then uses the next pointer to traverse the linked list by one
    TLDNode *iterNext = iter->currentNode;
    iter->currentNode = iter->currentNode->next;

    // condition checks if there is no node in the next position it should return NULL
    if (!iterNext) {
        return NULL;
    }

    return iterNext;
}

char *tldnode_tldname(TLDNode *node) {
    if (!node) {
        return NULL;
    }
    char *tldNameNode = node->tld;
    return tldNameNode;
}

long tldnode_count(TLDNode *node) {
    if (!node) {
        return 1;
    }

    long tldNodeCount = node->nodeCount;

    return tldNodeCount;
}

void tldlist_iter_destroy(TLDIterator *iter) {
    free(iter);
}