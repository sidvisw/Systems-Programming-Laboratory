#include <stdio.h>
#include <stdlib.h>
#include <my_library.h>
#include <graph_library.h>

// driver function
int main()
{
	char fileName[100];
	// read file name
	scanf("%[^\n]%*c", fileName);
	// store graph from the file
	GRAPH G = readGraph(fileName);
	printf("The DFS order of the given Graph is...\n");
	// print DFS order
	DFS(G);
	printf("The BFS order of the given Graph is...\n");
	// print BFS order
	BFS(G);
	printf("The MST of the given Graph is...\n");
	// print MST
	MST(G);
	return 0;
}