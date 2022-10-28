#include<stdio.h>
#include<stdlib.h>
#include<my_library.h>
#include "graph.h"

GRAPH readGraph(char*FName){
	GRAPH G;
	FILE* fp;
	fp=fopen(FName,"r");
	if(fp==NULL){
		printf("Error: File not found");
		exit(-1);
	}
	fscanf(fp,"%d %d",&G.numNodes,&G.numEdges);
	G.edges=(int**)malloc(G.numEdges*sizeof(int*));
	for(int i=0;i<G.numEdges;i++){
		G.edges[i]=(int*)malloc(3*sizeof(int));
	}
	for (int i = 0; i < G.numNodes; i++)
	{
		for (int j = 0; j < G.numNodes; j++)
		{
			G.adjMat[i][j]=0;
		}
	}
	for(int i=0;i<G.numEdges;i++){
		fscanf(fp,"%d %d %d",&G.edges[i][0],&G.edges[i][1],&G.edges[i][2]);
		G.adjMat[G.edges[i][0]][G.edges[i][1]]=G.edges[i][2];
		G.adjMat[G.edges[i][1]][G.edges[i][0]]=G.edges[i][2];
	}
	fclose(fp);
	return G;
}

void DFS_VISIT(GRAPH G,int node,int*visited){
	STACK S=createStack();
	S=push(S,node);
	visited[node]=1;
	printf("%d ",node);
	while(!isEmptyStack(S)){
		int v;
		S=pop(S,&v);
		for(int i=0;i<G.numNodes;i++){
			if(G.adjMat[v][i]!=0 && visited[i]==0){
				S=push(S,i);
				visited[i]=1;
				printf("%d ",i);
			}
		}
	}
}

void DFS(GRAPH G){
	int visited[100]={0};
	for(int i=0;i<G.numNodes;i++){
		if(visited[i]==0){
			DFS_VISIT(G,i,visited);
		}
	}
	printf("\n");
}

void BFS_VISIT(GRAPH G,int node,int*visited){
	QUEUE Q=createQueue();
	Q=enqueue(Q,node);
	visited[node]=1;
	printf("%d ",node);
	while(!isEmptyQueue(Q)){
		int v;
		Q=dequeue(Q,&v);
		for(int i=0;i<G.numNodes;i++){
			if(G.adjMat[v][i]!=0 && visited[i]==0){
				Q=enqueue(Q,i);
				visited[i]=1;
				printf("%d ",i);
			}
		}
	}
}

void BFS(GRAPH G){
	int visited[100]={0};
	for(int i=0;i<G.numNodes;i++){
		if(visited[i]==0){
			BFS_VISIT(G,i,visited);
		}
	}
	printf("\n");
}

// merge sort function to sort the edges based on their weights
void merge(int **edges,int **left,int **right,int size){
	int i=0,j=0,k=0;
	while(i<size/2 && j<size/2){
		if(left[i][2]<=right[j][2]){
			edges[k][0]=left[i][0];
			edges[k][1]=left[i][1];
			edges[k][2]=left[i][2];
			i++;
		}
		else{
			edges[k][0]=right[j][0];
			edges[k][1]=right[j][1];
			edges[k][2]=right[j][2];
			j++;
		}
		k++;
	}
	while(i<size/2){
		edges[k][0]=left[i][0];
		edges[k][1]=left[i][1];
		edges[k][2]=left[i][2];
		i++;
		k++;
	}
	while(j<size/2){
		edges[k][0]=right[j][0];
		edges[k][1]=right[j][1];
		edges[k][2]=right[j][2];
		j++;
		k++;
	}
}
void sort(int **edges,int size){
	if(size>1){
		int mid=(size/2);
		int **left=malloc(mid*sizeof(int*));
		for(int i=0;i<mid;i++){
			left[i]=(int*)malloc(3*sizeof(int));
			left[i][0]=edges[i][0];
			left[i][1]=edges[i][1];
			left[i][2]=edges[i][2];
		}
		int **right=malloc((size-mid)*sizeof(int*));
		for(int i=mid;i<size;i++){
			right[i-mid]=(int*)malloc(3*sizeof(int));
			right[i-mid][0]=edges[i][0];
			right[i-mid][1]=edges[i][1];
			right[i-mid][2]=edges[i][2];
		}
		sort(left,mid);
		sort(right,size-mid);
		merge(edges,left,right,size);
	}
}

//Kruskal's algorithm to find Minimum spanning tree using UNION_FIND data structure in my_library.h
void MST(GRAPH G){
	UNION_FIND UF=createUF(G.numNodes);
	int indices[100];
	for(int i=0;i<G.numNodes;i++){
		makeSetUF(UF,i,&indices[i]);
	}
	sort(G.edges,G.numEdges);
	long long sum=0;
	for(int i=0;i<G.numEdges;i++){
		int u=G.edges[i][0];
		int v=G.edges[i][1];
		if(findUF(UF,indices[u])!=findUF(UF,indices[v])){
			sum+=G.edges[i][2];
			printf("%d %d %d\n",u,v,G.adjMat[u][v]);
			unionUF(UF,u,v);
		}
	}
	printf("%lld\n",sum);
}