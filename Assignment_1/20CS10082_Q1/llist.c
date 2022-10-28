#include <stdio.h>
#include <stdlib.h>
// Include the header file for the linked list
#include "llist.h"

// Creating an empty list
// Parameters: none
// Returns: a pointer to the new list
LLIST createList()
{
	LLIST H = NULL;
	return H;
}

// Searching for a value in the list
// Parameters: the list, the value to search for
// Returns: 1 if the value is found, 0 if not
int searchList(LLIST H, int x)
{
	while (H != NULL)
	{
		if (H->value == x)
		{
			return 1;
		}
		H = H->next;
	}
	return 0;
}

// Inserting a value at the beginning of the list
// Parameters: the list, the value to insert
// Returns: the new list
LLIST insertAtFront(LLIST H, int k)
{
	NODEP ptr = (NODEP)malloc(sizeof(NODE));
	ptr->value = k;
	ptr->next = H;
	H = ptr;
	return H;
}

// Inserting a value at the end of the list
// Parameters: the list, the value to insert
// Returns: the new list
LLIST insertAtEnd(LLIST H, int k)
{
	NODEP ptr = H;
	if (ptr == NULL)
	{
		return insertAtFront(H, k);
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	NODEP node = (NODEP)malloc(sizeof(NODE));
	node->value = k;
	node->next = NULL;
	ptr->next = node;
	return H;
}

// Deleting a value from the head of the list
// Parameters: the list, the value to delete
// Returns: the new list
LLIST deleteFromFront(LLIST H, int *k)
{
	if (H == NULL)
	{
		printf("The list is empty...\nDeletion aborted...\n");
		return H;
	}
	NODEP temp = H;
	H = H->next;
	*k = temp->value;
	free(temp);
	return H;
}

// Deleting a value from the end of the list
// Parameters: the list, the value to delete
// Returns: the new list
LLIST deleteFromEnd(LLIST H, int *k)
{
	if (H == NULL)
	{
		printf("The list is empty...\nDeletion aboted...\n");
		return H;
	}
	if (H->next == NULL)
	{
		return deleteFromFront(H, k);
	}
	NODEP ptr = H;
	while (ptr->next->next != NULL)
	{
		ptr = ptr->next;
	}
	NODEP temp = ptr->next;
	ptr->next = ptr->next->next;
	*k = temp->value;
	free(temp);
	return H;
}

// Deleting a value from the list
// Parameters: the list, the value to delete
// Returns: the new list
LLIST deleteList(LLIST H, int k)
{
	NODEP ptr = H;
	if (H == NULL)
	{
		printf("The list is empty...\nDeletion aborted...\n");
		return H;
	}
	if (H->value == k)
	{
		NODEP temp = H;
		H = H->next;
		free(temp);
		return H;
	}
	while (ptr->next->value != k)
	{
		ptr = ptr->next;
	}
	NODEP temp = ptr->next;
	ptr->next = ptr->next->next;
	free(temp);
	return H;
}