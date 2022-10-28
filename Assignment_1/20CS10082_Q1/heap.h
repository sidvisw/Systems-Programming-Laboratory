#ifndef HEAP_H
#define HEAP_H

// Definition for heap structure
typedef struct
{
	int list[101];
	int size;
} HEAP;

// Member functions
HEAP createHeap();
int findMin(HEAP H);
HEAP extractMin(HEAP H);
HEAP insertHeap(HEAP H, int k);
int isFullHeap(HEAP H);
int isEmptyHeap(HEAP H);

#endif