//-----------------------------------------------------------------------------
// Graph.h
// Juwon Kim, jkim419, pa3
// Header file for Graph ADT
//-----------------------------------------------------------------------------
//Standard Libraries

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define INF -100
#define NIL 0
/*** Constructors-Destructors ***/
typedef struct GraphObj* Graph;

Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
