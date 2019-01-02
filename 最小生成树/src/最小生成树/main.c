#include "Prim.h"
#include <stdio.h>
#include <stdlib.h>

Graph * InitSimulation();
VertexInfo * InitVertexInfo();
int main()
{
	Graph *origin = 0;
	Graph *mstree = 0;
	VertexInfo *VI = 0;

	VI = InitVertexInfo();
	origin = InitSimulation();
	mstree = Prim(origin);
	Graph_View(mstree,1,VI);

	Delete_Graph(origin);
	Delete_Graph(mstree);
	return 0;
}
VertexInfo * InitVertexInfo()
{
	FILE *read;
	VertexInfo *VI = 0;
	int Vnumber;
	int VIindex;
	int i;
	errno_t err;

	if (err = fopen_s(&read, "Online Social Network Vertices.txt", "r") != 0)
		return NULL;
	fscanf_s(read, "%d\n", &Vnumber);
	VI = (VertexInfo*)malloc(sizeof(VertexInfo)*(Vnumber + 1));

	for (i = 0; i < Vnumber; i++)
	{
		fscanf_s(read, "%d", &VIindex);
		fscanf_s(read, " \"%d\" %lf %lf %lf", &VI[VIindex].number, &VI[VIindex].x, &VI[VIindex].y, &VI[VIindex].z);
	}

	return VI;
}
Graph * InitSimulation()
{
	FILE *read;
	Graph *graph = New_Graph();
	int v, e;
	int Vs, Ve;
	int i;
	double data;

	fopen_s(&read, "movie.txt", "r");
	fscanf_s(read, "%d %d", &v, &e);

	for (i = 0; i < e; i++)
	{
		fscanf_s(read, "%d %d %lf", &Vs, &Ve, &data);
		Graph_AddVertex(graph, Vs);
		Graph_AddVertex(graph, Ve);
		Graph_AddEdge(graph, Vs, Ve, data);
	}

	Graph_View(graph,0,NULL);
	return graph;

}