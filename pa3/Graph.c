//-----------------------------------------------------------------------------
// Graph.c
// Juwon Kim, jkim419, pa3
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define NIL 0
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF -100

typedef struct GraphObj{
   List* N;
   int* color;
   int* parent;
   int* distance;
   int order;
   int size;
   int source;
} GraphObj;
typedef GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
   Graph G=malloc(1 * sizeof(GraphObj));
   G->N=(List*)malloc((n+1) * sizeof(List));
   for(int i = 1; i <= n; i++){
      G->N[i] = newList();
   }
   int stor = n + 1;
   G->color = calloc(stor, sizeof(int));
   G->parent = calloc(stor, sizeof(int));
   G->distance = calloc(stor, sizeof(int));
   G->order = n;
   return G;
}
void freeGraph(Graph* pG){
   if(pG!=NULL && *pG!=NULL){
      for(int i=1; i<=getOrder(*pG);i++){
         freeList(&(*pG)->N[i]);
	  }
	  free((*pG)->N);
      free((*pG)->color);
      free((*pG)->distance);
	  free((*pG)->parent);
	  free(*pG);
      *pG = NULL;
   }
}

int getOrder(Graph G){
   if(G!=NULL){
      return G->order;
   } else{
      printf("Graph error: calling getOrder() with undefined Graph reference");
	  exit(EXIT_FAILURE);
   }
}
int getSize(Graph G){
   if(G!=NULL){
      return G->size;
   } else{
      printf("Graph error: calling getSize() with undefined Graph reference");
      exit(EXIT_FAILURE);
   }
}
int getSource(Graph G){             
   int valid;
   for(int i=1; i<=getOrder(G);i++){
      if(G->color[i]!=WHITE){
	     valid=1;
	  }
    }
	if(valid == 1){      
	   return G->source;
	} else{
	   return NIL;
	}
}
int getParent(Graph G, int u){
   if((u<1)||(u>getOrder(G))){
      printf("Graph error: calling getParent() with invalid u");
	  exit(EXIT_FAILURE);
   } else{
	   if(getSource(G)!=NIL){
	      return G->parent[u];
       } else{
          return NIL;
       }
   }
}
int getDist(Graph G, int u){
	if((u<1)||(u>getOrder(G))){
		printf("Graph error: calling getDist() with invalid u");
		exit(EXIT_FAILURE);
	} else{
		if(getSource(G)!=NIL){
		   return G->distance[u];
		} else{
			return INF;
		}
	}
}
void getPath(List L, Graph G, int u){
	if((u<1)||(u>getOrder(G))){
		printf("Graph error: calling getPath() with invalid destination vertex");
		exit(EXIT_FAILURE);
	} else if(getSource(G)==NIL){
		printf("Graph error: calling getPath() without calling BFS()");
		exit(EXIT_FAILURE);
	} else if(G==NULL){
		printf("Graph error: calling getPath() null Graph reference");
		exit(EXIT_FAILURE);
	}
    if(getSource(G)==u){
	    append(L, u);
	} else if(getParent(G, u)==NIL){
		//printf("%d is not reachable from %d", u,getSource(G));
		append(L, NIL);
	} else{
		getPath(L,G, getParent(G, u));
		append(L, u);
	}
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
	for(int i=1; i<=getOrder(G); i++){
		clear(G->N[i]);             //clear adjacency lists
	}
}
void addEdge(Graph G, int u, int v){
	if(((u<1)||(u>getOrder(G)))||((v<1)||(v>getOrder(G)))){
		printf("Graph error: calling addEdge() with invalid int");
		exit(EXIT_FAILURE);
	} else if(u==v){
		printf("Graph error: calling addEdge() with same vertices");
		exit(EXIT_FAILURE);
	} else{
		addArc(G, u, v);
		addArc(G, v, u);
		G->size-=1;
	}
}
void addArc(Graph G, int u, int v){
	if(((u<1) || (v<1)) || (u>getOrder(G)) || (v>getOrder(G)))){
		printf("Graph error: calling addArc() with invalid parameter");
		exit(EXIT_FAILURE);
	} else if(u == v){
		printf("Graph error: calling addArc() with two same vertices");
		exit(EXIT_FAILURE);
	} else{
		int a, len,valid;
		len = length(G->N[u]);
		valid=1;
		if(len!=0){
		   moveFront(G->N[u]);
		   for(int i=1; i<=len; i++){
		      a=get(G->N[u]);
			  if(v==a){
				  valid=0;
			  }
			  moveNext(G->N[u]);
		   } 
		   if(valid==1){
			   append(G->N[u], v);
			   sortList(G->N[u]);
				G->size+=1;
		   }
		} else{
			append(G->N[u], v);
			G->size+=1;
		}
	}
	
}

void BFS(Graph G, int s){
   G->source = s;
   for(int i=1; i<=getOrder(G); i++){
	   sortList(G->N[i]);
	   if(i!=s){
	      G->color[i]=WHITE;
	      G->distance[i]=INF;
		  G->parent[i]=NIL;
	   } 
   }
   G->color[s]=GRAY;
   G->distance[s]=0;
   G->parent[s]=NIL;
   List Q=newList();
   append(Q,s);
   int u;
   int v;
   while(length(Q)!=0){
	   moveFront(Q);
	   u=get(Q);
	   moveFront(G->N[u]);
	   for(int i=1;i<=length(G->N[u]);i++){
		   v=get(G->N[u]);
		   if(G->color[v]==WHITE){
		      G->color[v]=GRAY;
			  G->distance[v]=getDist(G,u)+1;
			  G->parent[v]=u;
			  append(Q, v);
		   }
		   moveNext(G->N[u]);
	   }
	   deleteFront(Q);
	   G->color[u]=BLACK;
   }
   freeList(&Q);
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	for(int i=1; i<=getOrder(G); i++){
		sortList(G->N[i]);
		fprintf(out, "%d: ", i);
		printList(out, G->N[i]);
		fprintf(out, "\n");
	}
}
