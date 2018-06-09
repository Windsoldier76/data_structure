---
layout: post
title: "Ergodic Graph and Minimal Spanning Tree"
date: 2018-06-09 11:05:00
categories:
---

# Source Code

```
//Ergodic_Graph_and_Minimal_Spanning_Tree.cpp
#include <iostream>

using namespace std;

#define MaxInt 32767
#define MVNum 100
#define Status int
#define OK 1
#define ERROR 0

typedef int VerTexType;
typedef int ArcType;

typedef struct
{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;

int Locate(AMGraph G,VerTexType v)
{//find the location of the vertex in the graph
	int i;
	for (i = 0; i < G.vexnum; ++i)
		if (G.vexs[i] == v)
			return i;
}

Status CreateUDN(AMGraph &G)
{//create a new undirected network with adjacency matrix
	cout << "please input vexnum" << endl;
	cin >> G.vexnum;                             //the number of vertexs
	cout << "please input arcnum" << endl;
	cin >> G.arcnum;                             //the number of edges
	cout << "please input vexs" << endl;
	for (int i = 0; i < G.vexnum; ++i)
		cin >> G.vexs[i];                        //input every vertex
	for (int i = 0; i < G.vexnum; ++i)
		for (int j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;               //initialize the adjacency matrix
	for (int k = 0; k < G.arcnum; ++k)
	{
		int w, i, j;
		VerTexType v1, v2;
		cout << "please input v1, v2 and w" << endl;
		cin >> v1 >> v2 >> w;
		i = Locate(G, v1);
		j = Locate(G, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return OK;
}

void OutputUDN(AMGraph G)
{//output the information of the graph
	for (int i = 0; i < G.vexnum; ++i)
		cout << G.vexs[i] << " ";
	cout << endl;
	for (int i = 0; i < G.vexnum; ++i)
	{
		for (int j = 0; j < G.vexnum; ++j)
		{
			cout << G.arcs[i][j];
			if (G.arcs[i][j] == MaxInt)
				cout << "  ";
			else
				cout << "      ";
		}
		cout << endl;
	}//for
}

bool visited[MVNum];

void DFS_AM(AMGraph G, int v)//v is just the index
{//depth first search the graph
	cout << G.vexs[v] << " ";                //output the vertex
	visited[v] = true;                       //visit the vertex and mark in array
	for (int w = 0; w < G.vexnum; w++)       //check every row in adjacency matrix
		if ((G.arcs[v][w] != MaxInt) && (!visited[w]))
			DFS_AM(G, w);
}

struct
{
	VerTexType adjvex;
	ArcType lowcost;
}closedge[MVNum];                   //auxiliary array

void MiniSpanTree_Prim(AMGraph G, VerTexType u)
{//create the minimal spanning tree by prim algorithm
	int k = Locate(G, u);                           //k is the index of u
	for (int j = 0; j < G.vexnum; ++j)
		if (j != k)
			closedge[j] = { u,G.arcs[k][j] };       //initialize the close edge array
	closedge[k].lowcost = 0;
	for (int i = 1; i < G.vexnum; ++i)
	{
		for (int j = 0; j < G.vexnum; ++j)
			if ((closedge[k].lowcost > closedge[j].lowcost) && closedge[j].lowcost || !closedge[k].lowcost)  //find the lowest cost edge
				k = j;
		VerTexType u0, v0;
		u0 = closedge[k].adjvex;
		v0 = G.vexs[k];
		cout << u0 << "-" << v0 << endl;            //output
		closedge[k].lowcost = 0;
		for (int j = 0; j < G.vexnum; ++j)          //reselect the lowest cost edge
			if (G.arcs[k][j] < closedge[j].lowcost)
				closedge[j] = { G.vexs[k], G.arcs[k][j] };
	}//for
}

int main()
{
	AMGraph G;
	CreateUDN(G);
	cout << "===========================" << endl;
	OutputUDN(G);
	DFS_AM(G, 0);
	cout << endl;
	MiniSpanTree_Prim(G, 1);
	return 0;
}
```

# Input
```
6
10
1 2 3 4 5 6
1 2 6
1 3 1
1 4 5
2 3 5
2 5 3
3 5 6
3 6 4
3 4 5
4 6 2
5 6 6
```

# Output

```
1 2 3 4 5 6
32767  6      1      5      32767  32767
6      32767  5      32767  3      32767
1      5      32767  5      6      4
5      32767  5      32767  32767  2
32767  3      6      32767  32767  6
32767  32767  4      2      6      32767
1 2 3 4 6 5
1-3
3-6
6-4
3-2
2-5
```
