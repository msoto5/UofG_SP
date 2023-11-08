#include "date.h"
#include "tldlist.h"
#include <stdlib.h>
#include <string.h>


// Structure definition for the TLD list, including the count of TLDs and the date range.
struct tldlist {
    long count;			// Total number of TLDs in the list
    long nodes;			// Number of nodes in binary search tree
    Date *begin, *end;	// The Date range 
    TLDNode *root;		// Root node of the binary search tree
};

// Structure definition for a node in the TLD binary search tree.
struct tldnode {
    TLDNode *left, *right;	      // Pointers to left and right children nodes
    char *tld;			         // Pointer to the TLD string
    long count;			        // Count of occurrences for this TLD
};
// Iterator structure to traverse the TLD nodes in order.
struct tlditerator {
    long next;		// The next node to be accessed in the iterator
    long size;			// Total size of the array
    TLDNode **first;	 // Pointer to the first element
};


// Function to create and initialize a TLDList within a given date range.
TLDList *tldlist_create(Date *begin, Date *end) {


// Check if the date range is valid; if not
    if (date_compare(begin, end) > 0) {
        return NULL;
    }


    TLDList *newTLDList = (TLDList *)malloc(sizeof(TLDList));


    if (newTLDList == NULL) {
        return NULL;
    }

// Initialize the new TLDList with zero counts and NULL root node and duplicate the begin and end dates for the list's date range
    newTLDList->count = 0;
    newTLDList->nodes = 0;
    newTLDList->root = NULL;
    newTLDList->begin = date_duplicate(begin);
    newTLDList->end = date_duplicate(end);

 // If date duplication fails, clean up and return NULL
    if (newTLDList->begin == NULL || newTLDList->end == NULL) {
        date_destroy(newTLDList->begin);
        date_destroy(newTLDList->end);
        free(newTLDList);
        return NULL;
    }

    return newTLDList;
}

// Function to recursively destroy nodes in the TLD tree.
void destroy_tldnode(TLDNode *node) {
    if (node == NULL) {
        return;
    }
    
    destroy_tldnode(node->left);
    destroy_tldnode(node->right);

    
    free(node->tld);
    free(node);
}

// Function to destroy a TLDList and free all associated memory.
void tldlist_destroy(TLDList *tld) {
    if (tld == NULL) {
        return;
    }
    
    destroy_tldnode(tld->root);

   
    date_destroy(tld->begin);
    date_destroy(tld->end);

    
    free(tld);
}


// Function to extract the TLD from a given hostname.
static void extract_tld(char *hostname, char *tld_str, int buffer_size) {
    char *last_dot = strrchr(hostname, '.');
    if (last_dot && *(last_dot + 1)) {
        last_dot++;
        strncpy(tld_str, last_dot, buffer_size - 1);
        tld_str[buffer_size - 1] = '\0';  
    } else {
        tld_str[0] = '\0'; 
    }
}


// Function to insert a TLD into the binary search tree.
static TLDNode *insert_node(TLDList *tld_list, char *tld) {

    // Initialize pointers for traversing the tree and for keeping track of the parent node.
    TLDNode *current_node, *parent_node, *new_node;
    int comparison_result;


    // Start with the root of the tree.
    current_node = tld_list->root;
    parent_node = NULL;


    // Traverse the tree to find the correct insertion point.
    while (current_node != NULL) {

        parent_node = current_node;


        comparison_result = strcasecmp(tld, current_node->tld);

        if (comparison_result < 0)
            current_node = current_node->left;


        else if (comparison_result > 0)
            current_node = current_node->right;


        else {
            return current_node;  
        }
    }

    // Allocate memory for a new node since TLD does not exist yet.
    new_node = (TLDNode *)malloc(sizeof(TLDNode));
    if (!new_node)
        return NULL;


    // Duplicate the TLD string for the new node.
    new_node->tld = strdup(tld);
    if (!new_node->tld) {
        free(new_node);
        return NULL;
    }

    new_node->count = 0;

    new_node->left = new_node->right = NULL;

    if (!parent_node)
        tld_list->root = new_node;

    else if (strcasecmp(tld, parent_node->tld) < 0)
        parent_node->left = new_node;

    else
        parent_node->right = new_node;

    tld_list->nodes++;

    return new_node;
}

// Function to add a hostname's TLD to the TLD list if it falls within the date range.
int tldlist_add(TLDList *tld_list, char *hostname, Date *date) {

    char tld_buffer[20];

    TLDNode *target_node;

    if (!tld_list || !hostname || !date)
        return 0;

    if (date_compare(date, tld_list->end) > 0 || date_compare(date, tld_list->begin) < 0)
        return 0;

    extract_tld(hostname, tld_buffer, sizeof(tld_buffer));


    if (tld_buffer[0] == '\0')  
        return 0;

    target_node = insert_node(tld_list, tld_buffer);

    if (!target_node)
        return 0;

    target_node->count++;
    tld_list->count++;

    return 1;
}

// Function to get the count of all TLDs within the list.
long tldlist_count(TLDList *tld) {
    if (tld == NULL) {
        return 0;
    }
    return tld->count;
}
// Recursive helper function to fill an array with pointers to TLD nodes (used for iteration).
void fill_array(TLDNode *node, TLDNode **array, long *index) {
    if (node == NULL) {
        return;
    }
    fill_array(node->left, array, index);
    array[(*index)++] = node;
    fill_array(node->right, array, index);
}

// Create an iterator for the TLD list.
TLDIterator *tldlist_iter_create(TLDList *tld) {
    if (tld == NULL) {
        return NULL;
    }
    TLDIterator *iter = (TLDIterator *)malloc(sizeof(TLDIterator));
    if (iter == NULL) {
        return NULL;
    }
    iter->first = (TLDNode **)malloc(sizeof(TLDNode *) * tld->nodes);
    if (iter->first == NULL) {
        free(iter);
        return NULL;
    }
    iter->next = 0;
    iter->size = tld->nodes;
    long index = 0;
    fill_array(tld->root, iter->first, &index);
    return iter;
}
// Get the next element from the iterator.
TLDNode *tldlist_iter_next(TLDIterator *iter) {
    if (iter == NULL ) {
        return NULL;
    }

    if (iter->next >= iter->size) {
        return NULL;
    }
    return iter->first[iter->next++];
}

// Destroy the iterator and free its resources.
void tldlist_iter_destroy(TLDIterator *iter) {
   
    if (iter) {
        free(iter->first);  
        iter->first = NULL;
        iter->next = iter->size = 0;
        free(iter);  
    }
}
// Retrieve the TLD from a node.
char *tldnode_tldname(TLDNode *node) {
    if (node == NULL) {
        return NULL;
    }
    return node->tld;
}
// Retrieve the count from a node.
long tldnode_count(TLDNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->count;  
}




