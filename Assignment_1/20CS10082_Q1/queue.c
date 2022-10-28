#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#include "queue.h"

// Create a new empty queue
// Parameter: none
// Return: pointer to the new queue
QUEUE createQueue()
{
	QUEUE Q = {NULL, NULL};
	return Q;
}

// Check if the queue is empty
// Parameter: pointer to the queue
// Return: 1 if the queue is empty, 0 otherwise
int isEmptyQueue(QUEUE Q)
{
	if (Q.front == NULL)
	{
		return 1;
	}
	return 0;
}

// Add an element to the queue
// Parameter: pointer to the queue, element to be added
// Return: the new queue
QUEUE enqueue(QUEUE Q, int k)
{
	LLIST new = createList();
	new = insertAtFront(new, k);
	if (Q.front == NULL)
	{
		Q.front = new;
		Q.rear = new;
	}
	else
	{
		Q.rear->next = new;
		Q.rear = new;
	}
	return Q;
}

// Remove an element from the queue
// Parameter: pointer to the queue, the pointer to store the removed element
// Return: the new queue
QUEUE dequeue(QUEUE Q, int *k)
{
	if (Q.front == NULL)
	{
		printf("Queue is empty\n");
		return Q;
	}
	LLIST temp = Q.front;
	if (Q.front == Q.rear)
	{
		Q.front = NULL;
		Q.rear = NULL;
	}
	else
	{
		Q.front = Q.front->next;
	}
	*k = temp->value;
	free(temp);
	return Q;
}