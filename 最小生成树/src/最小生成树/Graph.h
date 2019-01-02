#pragma once
#include "Array.h"
#include "Graph.h"
#include <stdio.h>
typedef int Vertex;
typedef struct _Edge Edge;
struct _Edge
{
	Vertex ep1;
	Vertex ep2;
	double weight;
};

typedef struct _Graph Graph;
struct _Graph
{
	Array *vertexs;
	Array *edges;
};
typedef struct _VertexInfo VertexInfo;
struct _VertexInfo
{
	int number;
	double x;
	double y;
	double z;
};

Graph *New_Graph();
void Delete_Graph(Graph *graph);
int Graph_AddVertex(Graph *graph, Vertex pt);
int Graph_AddEdge(Graph *graph, Vertex ep1, Vertex ep2, double weight);
int Graph_ExistVertex(Graph *graph, Vertex pt);
int Graph_ExistEdge(Graph *graph, Vertex ep1, Vertex ep2);
void Graph_View(Graph *graph,int check,VertexInfo *VI);
void Graph_ViewVertexs(Graph *graph,int check,FILE* pFile, VertexInfo *VI);
void Graph_ViewEdges(Graph *graph,int check,FILE* pFile);
void Graph_FindNeighvor(Graph *graph, Vertex ep, Array *neighvor);
double Graph_GetWeight(Graph *graph, Vertex ep1, Vertex ep2);
int Graph_GetVtCnt(Graph *graph);
Vertex Graph_GetFront(Graph *graph);
int Edge_Include(Edge *edge, Vertex pt);