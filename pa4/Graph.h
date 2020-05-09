//-----------------------------------------------------------------------------
// Graph.h
// Juwon Kim, jkim419, pa4
// Header file for Graph ADT
//-----------------------------------------------------------------------------
//Standard Libraries

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define UNDEF 0
#define NIL -5
/*** Constructors-Destructors ***/
typedef struct GraphObj* Graph;

Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
int getVisited(Graph G, int u);
/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
int visit(Graph G, int time, int u);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
