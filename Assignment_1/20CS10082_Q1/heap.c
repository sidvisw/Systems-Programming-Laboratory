#include <stdio.h>
#include <stdlib.h>
// Include the heap header file
#include "heap.h"

// Function to create a new heap
// Parameter: none
// Return: the created heap
HEAP createHeap()
{
	HEAP H;
	H.size = 0;
	return H;
}

// Functionto check if the heap is full
// Parameter: the heap
// Return: 1 if the heap is full, 0 otherwise
int isFullHeap(HEAP H)
{
	if (H.size == 100)
	{
		return 1;
	}
	return 0;
}

// Function to check if the heap is empty
// Parameter: the heap
// Return: 1 if the heap is empty, 0 otherwise
int isEmptyHeap(HEAP H)
{
	if (H.size == 0)
	{
		return 1;
	}
	return 0;
}

// Functiuon to get the topmost element of the heap
// Parameter: the heap
// Return: the topmost element of the heap
int findMin(HEAP H)
{
	if (isEmptyHeap(H))
	{
		printf("The heap is empty...\n");
		return -10000009;
	}
	return H.list[1];
}

// Function to extract the topmost element of the heap
// Parameter: the heap
// Return: the modified heap
HEAP extractMin(HEAP H)
{
	if (isEmptyHeap(H))
	{
		printf("The heap is empty...\n");
		return H;
	}
	H.list[1] = H.list[H.size];
	H.size--;
	int i = 1;
	while (i * 2 <= H.size)
	{
		int child = i * 2;
		if (child < H.size && H.list[child + 1] < H.list[child])
		{
			child++;
		}
		if (H.list[child] < H.list[i])
		{
			int temp = H.list[i];
			H.list[i] = H.list[child];
			H.list[child] = temp;
			i = child;
		}
		else
		{
			break;
		}
	}
	return H;
}

// Function to insert an element into the heap
// Parameter: the heap, the element to be inserted
// Return: the modified heap
HEAP insertHeap(HEAP H, int k)
{
	if (isFullHeap(H))
	{
		printf("The heap is full...\n");
		return H;
	}
	H.size++;
	H.list[H.size] = k;
	int i = H.size;
	while (i > 1 && H.list[i] < H.list[i / 2])
	{
		int temp = H.list[i];
		H.list[i] = H.list[i / 2];
		H.list[i / 2] = temp;
		i /= 2;
	}
	return H;
}