#ifndef UNION_FIND_H
#define UNION_FIND_H

// UnionFind node structure
typedef struct _node
{
	struct _node *parent;
	int rank, value;
} node;

// typder to NODE_PTR
typedef node *NODE_PTR;

// UNION_FIND Set structure
typedef struct _UNION_FIND
{
	NODE_PTR *UF;
	int size;
} UNION_FIND;

//	Member functions
UNION_FIND createUF(int);
UNION_FIND makeSetUF(UNION_FIND, int, int *);
NODE_PTR findUF(UNION_FIND, int);
void unionUF(UNION_FIND, int, int);

#endif