#include "Prim.h"
#include <stdio.h>
Graph *Prim(Graph *origin);

int SelectVertex(Graph *mstree, Graph *origin);
Graph *Prim(Graph *origin)
{
	Graph *mstree = 0;
	Vertex vt;
	int check = 0;
	mstree = New_Graph();
	vt = Graph_GetFront(origin);
	Graph_AddVertex(mstree, vt);
	while (Graph_GetVtCnt(mstree)<Graph_GetVtCnt(origin))
	{
		check = SelectVertex(mstree, origin);
		if (check == 0)
			break;
	}
	return mstree;
}
int IsOnlyOneInclude(Edge *edge, Array *selected);
int SelectVertex(Graph *mstree, Graph *origin)
{
	Array *selected = mstree->vertexs;
	Array *ori_edges = origin->edges;
	Edge *selectedge = 0;

	Iterator seek = 0, end = 0;
	Edge *edge = 0;
	seek = Array_Begin(ori_edges);
	end = Array_End(ori_edges);

	for (seek = seek; seek != end; ++seek)
	{
		edge = (Edge *)(*seek);
		if (IsOnlyOneInclude(edge, selected))
		{
			if (selectedge)
			{
				if (selectedge->weight>edge->weight)
				{
					selectedge = edge;
				}
			}
			else
			{
				selectedge = edge;
			}
		}
	}
	if (selectedge != NULL)
	{
		Graph_AddVertex(mstree, selectedge->ep1);
		Graph_AddVertex(mstree, selectedge->ep2);
		Graph_AddEdge(mstree, selectedge->ep1, selectedge->ep2, selectedge->weight);
		return 1;
	}
	return 0;
}

int IsOnlyOneInclude(Edge *edge, Array *selected)
{
	Iterator seek = 0, end = 0;
	int cnt = 0;
	Vertex vt;
	seek = Array_Begin(selected);
	end = Array_End(selected);
	for (seek = seek; seek != end; ++seek)
	{
		vt = (Vertex)(*seek);
		if (Edge_Include(edge, vt))
		{
			cnt++;
		}
	}
	return cnt == 1;
}