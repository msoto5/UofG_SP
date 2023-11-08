#include "date.h"	/* will use the functions defined here */
#include "tldlist.h"	/* so functions conform to interface prototypes */
#include <stdlib.h>	/* use malloc()/free() */
#include <string.h>	/* use strcasecmp(), strdup() */

struct tldlist {
    long count;			/* number of adds that were successful */
    long nodes;			/* number of nodes in the tree */
    Date *begin, *end;	/* begin and end Dates */
    TLDNode *root;		/* root of the binary search tree */
};

// This solution uses a BST to represent the TLD node structure
struct tldnode {
    TLDNode *left, *right;	/* links to children */
    char *tld;			/* top level domain for this element */
    long count;			/* number of times it has been added */
};

struct tlditerator {
    long next;			/* index of next element */
    long size;			/* number of elements */
    TLDNode **first;	/* array of pointers to nodes */
};

/*
 * recursive search for node matching `tld'
 */
static TLDNode *search(char *tld, TLDNode *leaf) {
    int result;

    if (! leaf)
        return NULL;
    result = strcasecmp(tld, leaf->tld);
    if (result == 0)
        return leaf;
    else if (result < 0)
        return search(tld, leaf->left);
    else
        return search(tld, leaf->right);
}

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end) {
    TLDList *ans;

    if (date_compare(begin, end) > 0)
        return NULL;
    ans = (TLDList *)malloc(sizeof(TLDList));
    if (ans) {
        ans->count = 0;
    	ans->nodes = 0;
    	ans->root = NULL;
    	ans->begin = date_duplicate(begin);
    	ans->end = date_duplicate(end);
    }
    return ans;
};

/*
 * postfix traversal of tree to destroy nodes
 */
static void destroy(TLDNode *node) {
    if (node) {
        destroy(node->left);
    	destroy(node->right);
    	free(node->tld);
    	free(node);
    }
}

/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld) {
    if (! tld)
        return;
    destroy(tld->root);
    date_destroy(tld->begin);
    date_destroy(tld->end);
    free(tld);
}

/*
 * extract top level domain from `hostname'
 */
static void extract(char *hostname, char *tld, int size) {
    char *p = strrchr(hostname, '.');	/* find last instance of '.' */
    if (!p)
        p = hostname;
    else
        p++;
    /*
     * copy at most size-1 bytes into `tld'; always terminate with '\0'
     */
    while (--size > 0) {
        if (! (*tld++ = *p++))
            break;
    }
    *tld = '\0';	/* terminate string with EOS */
}

/*
 * insert node in tree; assumes that search() has already been called and
 * returned NULL
 */
static TLDNode *insert(TLDList *tldl, char *tld) {
    TLDNode *current, *parent, *p;
    int result;

    current = tldl->root;
    parent = NULL;
    while (current != NULL) {
        parent = current;
        result = strcasecmp(tld, current->tld);
    	if (result < 0)
            current = current->left;
    	else
            current = current->right;
    }
    p = (TLDNode *)malloc(sizeof(TLDNode));
    if (!p)
        return NULL;
    p->tld = strdup(tld);
    if (! p->tld) {
        free(p);
	return NULL;
    }
    p->count = 0;
    p->left = p->right = NULL;
    if (! parent)
        tldl->root = p;
    else if (strcasecmp(tld, parent->tld) < 0)
        parent->left = p;
    else
        parent->right = p;
    tldl->nodes++;		/* one more node added */
    return p;
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls within the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tldl, char *hostname, Date *d) {
    char theTLD[20];
    TLDNode *p;

    if (!tldl)
        return 0;
    if (date_compare(d, tldl->end) > 0 || date_compare(d, tldl->begin) < 0)
        return 0;
    extract(hostname, theTLD, sizeof(theTLD));
    if (! (p = search(theTLD, tldl->root)))
        p = insert(tldl, theTLD);
    if (! p)
        return 0;
    p->count++;
    tldl->count++;
    return 1;
}

/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tldl) {
    if (! tldl)
        return 0;
    return tldl->count;
}

/*
 * infix traversal of tree to populate array of pointers in iterator
 */
static void populate(TLDIterator *it, TLDNode *node) {
    if (node) {
        populate(it, node->left);
        it->first[it->next++] = node;
        populate(it, node->right);
    }
}

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tldl) {
    if (! tldl)
        return NULL;
    TLDIterator *ans;
    ans = (TLDIterator *)malloc(sizeof(TLDIterator));
    if (! ans)
        return NULL;
    ans->next = 0;
    ans->size = tldl->nodes;
    ans->first = (TLDNode **)malloc(tldl->nodes * sizeof(TLDNode *));
    if (! ans->first) {		/* allocation failure */
        free(ans);
	    return NULL;
    } else
        populate(ans, tldl->root);
    ans->next = 0;
    return ans;
}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter) {
    if (! iter || iter->next >= iter->size)
        return NULL;
    return iter->first[iter->next++];
}

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter) {
    if (iter) {
        free(iter->first);	/* must free array of pointers first */
        free(iter);		/* free iterator */
    }
}

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node) {
    if (! node)
        return NULL;
    return node->tld;
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node) {
    if (! node)
        return 0;
    return node->count;
}
