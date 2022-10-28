#ifndef QUEUE_H
#define QUEUE_H

// Definition of the Queue struct
typedef struct
{
	LLIST front;
	LLIST rear;
} QUEUE;

// Member functions
QUEUE createQueue();
int isEmptyQueue(QUEUE);
QUEUE enqueue(QUEUE, int);
QUEUE dequeue(QUEUE, int *);

#endif