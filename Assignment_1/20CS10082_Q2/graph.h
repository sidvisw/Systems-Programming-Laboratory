#ifndef GRAPH_H
#define GRAPH_H

typedef struct
{
	int adjMat[100][100];
	int **edges;
	int numNodes;
	int numEdges;
}GRAPH;

GRAPH readGraph(char *);
void DFS(GRAPH);
void BFS(GRAPH);
void MST(GRAPH);

#endif