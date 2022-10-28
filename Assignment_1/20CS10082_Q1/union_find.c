#include <stdio.h>
#include <stdlib.h>
// Including the header file for the union find data structure
#include "union_find.h"

// Function to create a new union find data structure
// Parameter: size of the data structure
// Return: the created union find data structure
UNION_FIND createUF(int n)
{
	UNION_FIND F = {NULL, 0};
	F.UF = (NODE_PTR *)malloc(n * sizeof(NODE_PTR));
	for (int i = 0; i < n; i++)
	{
		F.UF[i] = NULL;
	}
	F.size = n;
	return F;
}

// Function to make singleton sets from the given data
// Parameter: the union find data structure
// Return: the union find data structure wit the singleton set
UNION_FIND makeSetUF(UNION_FIND F, int x, int *i)
{
	int j;
	for (j = 0; j < F.size; j++)
	{
		if (F.UF[j] == NULL)
		{
			*i = j;
			break;
		}
		if (F.UF[j]->value == x)
		{
			printf("%d is already in the set\n", x);
			*i = j;
			return F;
		}
	}
	if (j == F.size)
	{
		printf("The set is full\n");
		return F;
	}
	NODE_PTR new = (NODE_PTR)malloc(sizeof(node));
	new->value = x;
	new->parent = new;
	new->rank = 0;
	F.UF[j] = new;
	return F;
}

// Function to find the representative of the set containing x
// Parameter: the union find data structure and the index of the element
// Return: the representative of the set containing x
NODE_PTR findUF(UNION_FIND F, int i)
{
	NODE_PTR temp = F.UF[i];
	while (temp->parent != temp)
	{
		temp = temp->parent;
	}
	return temp;
}

// Function to union two sets containing x and y
// Parameter: the union find data structure and the index of the elements
// Return: the union find data structure with the union of the sets containing x and y
void unionUF(UNION_FIND F, int i, int j)
{
	NODE_PTR x = findUF(F, i);
	NODE_PTR y = findUF(F, j);
	if (x != y)
	{
		if (x->rank < y->rank)
		{
			x->parent = y;
		}
		else if (x->rank > y->rank)
		{
			y->parent = x;
		}
		else
		{
			x->parent = y;
			y->rank++;
		}
	}
}