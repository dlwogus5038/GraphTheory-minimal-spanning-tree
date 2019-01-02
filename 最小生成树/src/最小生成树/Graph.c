#include "Graph.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>
Edge *New_Edge(Vertex ep1, Vertex ep2, double weight)
{
	Edge *edge = 0;
	edge = (Edge *)malloc(sizeof(Edge));
	edge->ep1 = ep1;
	edge->ep2 = ep2;
	edge->weight = weight;
	return edge;
}
Vertex Edge_AnOther(Edge *edge, Vertex pt)
{
	if (edge->ep1 == pt)
	{
		return edge->ep2;
	}
	if (edge->ep2 == pt)
	{
		return edge->ep1;
	}
	return -1;
}
int Edge_Include(Edge *edge, Vertex pt)
{
	return (edge->ep1 == pt) || (edge->ep2 == pt);
}
Graph *New_Graph()
{
	Graph *graph = 0;
	graph = (Graph *)malloc(sizeof(Graph));
	graph->vertexs = New_Array();
	graph->edges = New_Array();
	return graph;
}
void Delete_Graph(Graph *graph)
{
	Iterator seek = 0, end = 0;
	Edge *edge = 0;
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);
	for (seek = seek; seek != end; ++seek)
	{
		edge = (Edge *)(*seek);
		free(edge);
	}
	Delete_Array(graph->vertexs);
	Delete_Array(graph->edges);
	free(graph);
}
int Graph_AddVertex(Graph *graph, Vertex pt)
{
	if (Graph_ExistVertex(graph, pt))
	{
		return 0;
	}
	Array_PushBack(graph->vertexs, (Element)pt);
	return 1;
}
int Graph_AddEdge(Graph *graph, Vertex ep1, Vertex ep2, double weight)
{
	if (Graph_ExistVertex(graph, ep1) && Graph_ExistVertex(graph, ep2))
	{
		Edge *edge = 0;
		if (Graph_ExistEdge(graph, ep1, ep2))
		{
			return 0;
		}
		edge = New_Edge(ep1, ep2, weight);
		Array_PushBack(graph->edges, edge);
		return 1;
	}
	return 0;
}
int Graph_ExistVertex(Graph *graph, Vertex pt)
{
	Iterator seek = 0, end = 0;
	Vertex stored_pt = 0;
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);
	for (seek = seek; seek != end; ++seek)
	{
		stored_pt = (Vertex)(*seek);
		if (stored_pt == pt)
		{
			return 1;
		}
	}
	return 0;
}
int Graph_ExistEdge(Graph *graph, Vertex ep1, Vertex ep2)
{
	Iterator seek = 0, end = 0;
	Edge *stored_eg = 0;
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);
	for (seek = seek; seek != end; ++seek)
	{
		stored_eg = (Edge *)(*seek);
		if (Edge_Include(stored_eg, ep1) && Edge_Include(stored_eg, ep2))
		{
			return 1;
		}
	}
	return 0;
}
void Graph_View(Graph *graph,int check,VertexInfo *VI)
{
	FILE* pFile = NULL;
	if (check == 1)
		fopen_s(&pFile, "result(movie).json", "wt");
	Graph_ViewVertexs(graph,check,pFile,VI);
	Graph_ViewEdges(graph,check,pFile);
}
void Graph_ViewVertexs(Graph *graph,int check,FILE* pFile,VertexInfo *VI)
{
	Iterator seek = 0, end = 0;
	Vertex pt = 0;
	int count = 1;
	if (check == 0)
		printf("Total Vertex Number:%d\n", graph->vertexs->usage);
	//else
		//fprintf(pFile, "Vertex Number of Tree:%d\n", graph->vertexs->usage);
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);
	if (check != 0)
		fprintf(pFile, "{\n  \"nodes\": [\n");
	for (seek = seek; seek != end; ++seek)
	{
		pt = (Vertex)(*seek);
		if (check == 0)
			printf("%d\n", pt);
		else
		{
			if (VI != NULL)
			{
				if (seek != end - 1)
					fprintf(pFile, "    {\"id\": %d},\n", pt);
				else
					fprintf(pFile, "    {\"id\": %d}\n", pt);
			}
			else
			{
				if (seek != end - 1)
					fprintf(pFile, "    {\"id\": %d},\n", pt);
				else
					fprintf(pFile, "    {\"id\": %d}\n", pt);
			}
		}
	}
	if(check != 0)
		fprintf(pFile, "  ],\n");
}
void Graph_ViewEdges(Graph *graph,int check,FILE* pFile)
{
	Iterator seek = 0, end = 0;
	Edge *edge = 0;
	if (check == 0)
		printf("Total Edge Number:%d\n", graph->edges->usage);
	//else
		//fprintf(pFile,"Edge Number of Tree:%d\n", graph->edges->usage);
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);
	if (check != 0)
		fprintf_s(pFile, "  \"edges\": [\n");
	for (seek = seek; seek != end; ++seek)
	{
		edge = (Edge *)(*seek);
		if (check == 0)
			printf("(%d ,%d):%lf\n", edge->ep1, edge->ep2, edge->weight);
		else
		{
			if (seek != end - 1)
				fprintf(pFile, "    {\"source\": %d, \"target\": %d, \"value\": %lf},\n", edge->ep1, edge->ep2, edge->weight);
			else
				fprintf(pFile, "    {\"source\": %d, \"target\": %d, \"value\": %lf}\n", edge->ep1, edge->ep2, edge->weight);
		}
	}
	if (check != 0)
		fprintf_s(pFile, "  ]\n}");
}
void Graph_FindNeighvor(Graph *graph, Vertex ep, Array *neighvor)
{
	Iterator seek = 0, end = 0;
	Edge *edge = 0;
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);
	for (seek = seek; seek != end; ++seek)
	{
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, ep))
		{
			Vertex opt;
			opt = Edge_AnOther(edge, ep);
			Array_PushBack(neighvor, (Element)opt);
		}
	}
}
double Graph_GetWeight(Graph *graph, Vertex ep1, Vertex ep2)
{
	Iterator seek = 0, end = 0;
	Edge *edge = 0;
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);
	for (seek = seek; seek != end; ++seek)
	{
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, ep1) && Edge_Include(edge, ep2))
		{
			return edge->weight;
		}
	}
	return -1;
}
int Graph_GetVtCnt(Graph *graph)
{
	return graph->vertexs->usage;
}
Vertex Graph_GetFront(Graph *graph)
{
	Iterator front = Array_Begin(graph->vertexs);
	return (Vertex)front[0];
}