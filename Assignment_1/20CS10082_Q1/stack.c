#include <stdio.h>
#include <stdlib.h>
// Include the llist and stack header file
#include "llist.h"
#include "stack.h"

// Create a new empty stack
// Parameters: none
// Returns: a pointer to the new stack
STACK createStack()
{
	STACK S = NULL;
	return S;
}

// Finds whether the stack is empty or not
// Parameters: S - the stack
// Returns: 1 if the stack is empty, 0 otherwise
int isEmptyStack(STACK S)
{
	if (S == NULL)
	{
		return 1;
	}
	return 0;
}

// Pushes an element onto the stack
// Parameters: S - the stack
//			   k - the element to be pushed
// Returns: 1 if the push was successful, 0 otherwise
STACK push(STACK S, int k)
{
	return insertAtFront(S, k);
}

// Pops an element off the stack
// Parameters: S - the stack, k - the pointer to store the popped element
// Returns: the new stack after the pop
STACK pop(STACK S, int *k)
{
	if (S == NULL)
	{
		printf("The stack is empty...\nDeletion aborted...\n");
		return S;
	}
	return deleteFromFront(S, k);
}