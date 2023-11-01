
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tldlist.h"

#define TLD_SIZE 4

struct tldlist
{
    Date *begin;
    Date *end;
    TLDNode *root;
    long count;
};

struct tldnode
{
    unsigned long count;
    char tld[TLD_SIZE];

    TLDNode *left;
    TLDNode *right;
    TLDNode *parent;
};

struct tlditerator
{
    TLDNode *current;
    TLDList *list;
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

    // Error control
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
 * Initialise a node structure
*/
TLDNode *tldnode_create(char *tld, TLDNode *parent)
{
    TLDNode *n = NULL;

    // Error control
    if (!tld)
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

    //printf("TLDLIST_ADD START:\n"); fflush(stdout);
    // Error control
    if (!l || !hostname || !d)
    {
       // printf("Error control\n"); fflush(stdout);
        return 0; 
    }

    //printf("aaaaaaaaa\n"); fflush(stdout);

    // Check if date is within range
    if (date_compare(d, l->begin) < 0 || date_compare(d, l->end) > 0)
    {
       // printf("Date out of range\n"); fflush(stdout);
        return 0;
    }
    
    // Get TLD from hostname
    tld = get_TLD_from_hostname(hostname);
    if (!tld)
    {
       // printf("No TLD found\n"); fflush(stdout);
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
    //printf("tldnode_add -> %s\n", tld); fflush(stdout);
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

char *get_TLD_from_hostname(char *hostname)
{
    char *tld = NULL;
    //printf("hostname -> %s\n", hostname);
    char* dot = strrchr(hostname, '.');
    if (dot == NULL) {
        return NULL; // No dot found in the hostname
    }

    //printf("hostname -> %s\tdot -> %s\n", hostname, dot+1);
    tld = strndup(dot + 1, TLD_SIZE-1);
    //printf("tld -> %s\n", tld);
    if (tld == NULL) {
        return NULL; // Memory allocation failed
    }

    return tld;
}

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
    else
    {
        node->count++;
        //printf("node %s->count -> %ld\n", node->tld, node->count);
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
    //printf("tldlist_iter_next\n"); fflush(stdout);
    if (!iter)
    {
        return NULL;
    }

    if (!iter->current)
    {
        //printf("No current\n"); fflush(stdout);
        iter->current = tldnode_get_min(iter->list->root);
        return iter->current;
    }
    else if (iter->current->right)
    {
        //printf("Busco el minimo de mi hijo derecho\n"); fflush(stdout);
        iter->current = tldnode_get_min(iter->current->right);
        return iter->current;
    }
    else if (!iter->current->parent)
    {
        //printf("No hay padre\n"); fflush(stdout);
        return NULL;
    }
    else if (iter->current->parent->left == iter->current)
    {
        //printf("Soy el hijo izquierdo\n"); fflush(stdout);
        iter->current = iter->current->parent;
        return iter->current;
    }
    else if (iter->current->parent->right == iter->current)
    {
        //printf("Soy el hijo derecho\n"); fflush(stdout);
        act = iter->current;
        while (act->parent->right == act)
        {
            //printf("act -> %s\n", act->tld);
            act = act->parent;
            if (act->parent == NULL)
            {
                return NULL;
            }
            
        }
        iter->current = act->parent;
        return iter->current;
    }
    //printf("Soy bobo\n"); fflush(stdout);
    return NULL;
}

// TLDNode *tldnode_get_next(TLDNode *node)
// {
//     if (!node)
//     {
//         return NULL;
//     }

//     if (node->right)
//     {
//         node = tldnode_get_min(node->right);
//         return node;
//     }
//     else if (!node->parent)
//     {
//         return NULL;
//     }
//     else if (node->parent->left == node)
//     {
//         node = node->parent;
//         return node;
//     }
//     else if (node->parent->right == node)
//     {
//         node = tldnode_get_next(node->parent, 1);
//         return node;
//     }
//     else
//     {
//         return NULL;
//     }
// }

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