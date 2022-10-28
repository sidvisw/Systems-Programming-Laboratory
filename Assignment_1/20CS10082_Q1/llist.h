#ifndef LLIST_H
#define LLIST_H

// Node definition for linked list
typedef struct _NODE
{
	int value;
	struct _NODE *next;
} NODE;

typedef NODE *NODEP;

typedef NODEP LLIST;

// Member functions of linked list
LLIST createList();
int searchList(LLIST, int);
LLIST insertAtFront(LLIST, int);
LLIST insertAtEnd(LLIST, int);
LLIST deleteFromFront(LLIST, int *);
LLIST deleteFromEnd(LLIST, int *);
LLIST deleteList(LLIST, int);

#endif