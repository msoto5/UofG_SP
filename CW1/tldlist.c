
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tldlist.h"

#define TLD_SIZE 4      /* Size of TLD String */

struct tldlist
{
    Date *begin;
    Date *end;
    TLDNode *root;  /* Root of the tree */
    long count;     /* Number of successful tldlist_add() calls */
};

struct tldnode
{
    unsigned long count;    /* Number of times the TLD was added */
    char tld[TLD_SIZE];     /* Top Level Domain */

    TLDNode *left;
    TLDNode *right;
    TLDNode *parent;        
};

struct tlditerator
{
    TLDNode *current;   /* Current node */
    TLDList *list;      /* List to iterate */
};

// Private function prototypes
TLDNode *tldnode_create(char *tld, TLDNode *parent);
void tldnode_destroy(TLDNode *node);
char *get_TLD_from_hostname(char *hostname);
int tldnode_add(TLDNode *node, char *tld);
TLDNode *tldnode_get_min(TLDNode *node);
TLDNode *tldnode_get_next(TLDNode *node);

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end)
{
    TLDList *l = NULL;

    /* Error control */
    if (!begin || !end || date_compare(begin, end) > 0)
    {
        return NULL;
    }

    l = (TLDList *)malloc(sizeof(TLDList));
    if (!l)
    {
        return NULL;
    }

    l->begin = begin;
    l->end = end;
    l->root = NULL;
    l->count = 0;

    return l;
}

/**
 * Generate a node structure
*/
TLDNode *tldnode_create(char *tld, TLDNode *parent)
{
    TLDNode *n = NULL;

    /* Error control */
    if (!tld)   /* parent can be NULL -> the root */
    {
        return NULL;
    }

    n = (TLDNode *)malloc(sizeof(TLDNode));
    if (!n)
    {
        return NULL;
    }

    n->count = 1;
    strncpy(n->tld, tld, TLD_SIZE);
    n->left = NULL;
    n->right = NULL;
    n->parent = parent;

    return n;
}

/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld)
{
    if (tld)
    {
        tldnode_destroy(tld->root);
        free(tld);
    }
}

/**
 * Frees a node structure
*/
void tldnode_destroy(TLDNode *node)
{
    if (node)
    {
        tldnode_destroy(node->left);
        tldnode_destroy(node->right);
        free(node);
    }
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *l, char *hostname, Date *d)
{
    char *tld;
    int ret;

    /* Error control */
    if (!l || !hostname || !d)
    {
        return 0; 
    }

    // Check if date is within range
    if (date_compare(d, l->begin) < 0 || date_compare(d, l->end) > 0)
    {
        return 0;
    }
    
    // Get TLD from hostname
    tld = get_TLD_from_hostname(hostname);
    if (!tld)
    {
        return 0;
    }

    // Add TLD to list
    if (!l->root)     // Tree is empty -> Add first element
    {
        l->root = tldnode_create(tld, NULL);
        if (!l->root)
        {
            return 0;
        }
        l->count++;
        ret = 1;
    }
    else
    {
        ret = tldnode_add(l->root, tld);
        if (ret)
        {
            l->count++;
        }
    }
    
    return ret;
}

/**
 * @brief Get the TLD from a hostname
 * 
 * @param hostname
 * @return pointer to string in heap (size = TLD_SIZE) if successful, NULL if not
*/
char *get_TLD_from_hostname(char *hostname)
{
    char *tld = NULL, *dot = NULL;
    
    dot = strrchr(hostname, '.');
    if (dot == NULL)
    {
        return NULL; // No dot found
    }

    tld = strndup(dot + 1, TLD_SIZE-1);
    if (tld == NULL)
    {
        return NULL;
    }

    return tld;
}

/**
 * @brief Recursive function that adds a TLDNode to the tree
 * 
 * @param node 
 * @param tld 
 * @return 1 if successful, 0 if not
*/
int tldnode_add(TLDNode *node, char *tld)
{
    int cmp;

    if (!node || !tld)
    {
        return 0;
    }

    cmp = strcmp(tld, node->tld);
    if (cmp < 0)
    {
        if (!node->left)
        {
            node->left = tldnode_create(tld, node);
            if (!node->left)
            {
                fprintf(stderr, "Error creating node\n");
                return 0;
            }

            return 1;
        }
        else
        {
            return tldnode_add(node->left, tld);
        }
    }
    else if (cmp > 0)
    {
        if (!node->right)
        {
            node->right = tldnode_create(tld, node);
            if (!node->right)
            {
                fprintf(stderr, "Error creating node\n");
                return 0;
            }

            return 1;
        }
        else
        {
            return tldnode_add(node->right, tld);
        }
    }
    else    /* Node already exist */
    {
        node->count++;
        return 1;
    }
}

/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld)
{
    if (!tld)
    {
        return 0;
    }
    return tld->count;
}

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld)
{
    TLDIterator *it = NULL;

    /* Error control */
    if (!tld)
    {
        return NULL;
    }

    it = (TLDIterator *)malloc(sizeof(TLDIterator));
    if (!it)
    {
        return NULL;
    }

    it->current = NULL;
    it->list = tld;

    return it;
}

/**
 * @brief Get the minimum node of a tree.
 * 
 * @param node
 * @return pointer to the minimum node if successful, NULL if not
*/
TLDNode *tldnode_get_min(TLDNode *node)
{
    TLDNode *act;

    if (!node)
    {
        return NULL;
    }

    act = node;
    while (act->left)
    {
        act = act->left;
    }
    
    return act;
}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter)
{
    TLDNode *act;

    if (!iter)
    {
        return NULL;
    }

    if (!iter->current)     /* First call */
    {
        iter->current = tldnode_get_min(iter->list->root);
        return iter->current;
    }
    /* If I have a right child -> Next = right child */
    else if (iter->current->right)   
    {
        iter->current = tldnode_get_min(iter->current->right);
        return iter->current;
    }
    /* No right child && no parent -> No more elements */
    else if (!iter->current->parent)    
    {
        return NULL;
    }
    /* No right child && parent && node is left child -> Next = parent */
    else if (iter->current->parent->left == iter->current)
    {
        iter->current = iter->current->parent;
        return iter->current;
    }
    /* No right child && parent && node is right child -> 
       Next = parent of the first parent (going up the tree) that is left child */
    else if (iter->current->parent->right == iter->current)
    {
        act = iter->current;
        while (act->parent->right == act)
        {
            act = act->parent;
            if (act->parent == NULL)
            {
                return NULL;
            }
            
        }
        iter->current = act->parent;
        return iter->current;
    }
    
    return NULL;
}

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter)
{
    if (iter)
    {
        free(iter);
    }
}

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node)
{
    if (!node)
    {
        return NULL;
    }
    
    return node->tld;
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node)
{
    if (!node)
    {
        return 0;
    }
    
    return node->count;
}