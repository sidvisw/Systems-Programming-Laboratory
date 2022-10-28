#ifndef STACK_H
#define STACK_H

// Using the LLIST Data Structure
typedef LLIST STACK;

// Member Functions
STACK createStack();
int isEmptyStack(STACK);
STACK push(STACK, int);
STACK pop(STACK, int *);

#endif