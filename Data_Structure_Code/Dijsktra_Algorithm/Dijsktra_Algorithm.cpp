#include <iostream>

using namespace std;

#define MaxInt 32767
#define MVNum 100
#define Status int
#define OK 1
#define ERROR 0

typedef char VerTexType;
typedef int ArcType;

typedef struct
{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;

int Locate(AMGraph G, VerTexType v)
{//find the location of the vertex in the graph
	int i;
	for (i = 0; i < G.vexnum; ++i)
		if (G.vexs[i] == v)
			return i;
}

Status CreateDN(AMGraph &G)
{//create a new directed network with adjacency matrix
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
	}
	return OK;
}

void ShortestPath_DIJ(AMGraph G, int v0)
{//calculate the shortest path from v0 to every other vertex of the graph by the dijsktra algorithm
	int n = G.vexnum;
	bool S[MVNum];
	int D[MVNum], Path[MVNum], v;
	for (v = 0; v < n; ++v)
	{
		S[v] = false;
		D[v] = G.arcs[v0][v];
		if (D[v] < MaxInt)
			Path[v] = v0;
		else
			Path[v] = -1;
	}
	S[v0] = true;
	D[v0] = 0;
	//initialization finished

	v = 0;
	for (int i = 1; i < n; ++i)           //calculate other vertexs
	{
		int min = MaxInt;
		for (int w = 0; w < n; ++w)
			if (!S[w] && D[w] < min)
			{
				v = w;
				min = D[w];               //choose the shortest path
			}
		S[v] = true;                      //join v into S
		for (int w = 0; w < n; ++w)       //new length of the shortest path
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];   //new D[w]
				Path[w] = v;                  //change the pioneer of w to v
			}//if
	}//for

	cout << "===========================" << endl;

	for (int i = 1; i < n; ++i)
	{
		int w = 0, j = i;
		cout << G.vexs[0] << " to " << G.vexs[i] << " :" << endl;   //output the begin and end vertexs
		int v1[MVNum];                                              //save the answer with an array v1
		v1[w] = j;
		while (Path[j])
		{
			++w;
			j = v1[w] = Path[j];                                    //save the path with the reserse order
		}
		cout << G.vexs[0];
		for (w; w >= 0; --w)                                        //reverse output the path to right order
			cout << "-" << G.vexs[v1[w]];
		cout << endl;
	}
}

int main()
{
	AMGraph G;
	CreateDN(G);
	ShortestPath_DIJ(G, 0);
	return 0;
}