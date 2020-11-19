//--------------------------------------------------------------------------
// Graph.c
// Juwon Kim, jkim419, pa4
// Implementation file for Graph ADT
//--------------------------------------------------------------------------

//directives
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

//macros
#define UNDEF 0
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -5

typedef struct GraphObj{
   List* L;
   int* color;
   int* parent;
   int* discover;
   int* finish;
   int* visit;
   int source;
   int size;
   int order;
} GraphObj;
typedef GraphObj* Graph;

Graph newGraph(int n){
   Graph G = malloc (sizeof(GraphObj));
   G->L = (List*)malloc((n+1) * sizeof(List));
   for(int i = 0; i <= n; ++i){
      G->L[i] = newList();
   }
   G->color = calloc(n+1, sizeof(int));
   G->parent = calloc(n+1, sizeof(int));
   G->discover = calloc(n+1, sizeof(int));
   G->finish  = calloc(n+1, sizeof(int));
   G->visit = calloc(n+1, sizeof(int));
   G->order = n;
   return G;
}

void freeGraph(Graph* pG){
   if(pG != NULL && pG != NULL){
      for(int i = 0; i <= getOrder(*pG); i++){
	     freeList(&(*pG)->L[i]);
	  }
	  free((*pG)->L);
	  free((*pG)->color);
	  free((*pG)->parent);
	  free((*pG)->discover);
	  free((*pG)->finish);
	  free(*pG);
	  *pG = NULL;
   }
}
/*** Access functions ***/
int getOrder(Graph G){
   if(G != NULL){
      if(G->order > 0){
	     return G->order;
	  } 
   } else{
      printf("Graph error: calling getOrder() with undefined Graph");
   }
   return 0;              //if G is not NULL it would return and exit the scope
}
int getSize(Graph G){
   if(G!=NULL){
      return G->size;
   } else{
      printf("Graph error: calling getSize() with undefined Graph reference");
      exit(EXIT_FAILURE);
   }
}

int getParent(Graph G, int u){ 
   if((u < 1) || (u > getOrder(G))){
      printf("Graph error: calling getParent() with invalid u");
      exit(EXIT_FAILURE);
   } else{
      if(G->source == 1){
         return G->parent[u];
   } else{
         return NIL;
      }
   }
}
int getDiscover(Graph G, int u){
   if((u<1)||(u>getOrder(G))){
      printf("Graph error: calling getDist() with invalid u");
      exit(EXIT_FAILURE);
   } else{
      if(G->source==1){
         return G->discover[u];
   } else{
         return UNDEF;
      }
   }
}
int getFinish(Graph G, int u){
   if((u<1)||(u>getOrder(G))){
      printf("Graph error: calling getDist() with invalid u");
      exit(EXIT_FAILURE);
   } else{
      if(G->source == 1){
		   return G->finish[u];
		} else{
			return UNDEF;
		}
	}
}
int getVisited(Graph G, int u){
   if((u<1)||(u>getOrder(G))){
      printf("Graph error: calling getDist() with invalid u");
      exit(EXIT_FAILURE);
   } else{
      if(G->source==1){
         return G->visit[u];
      } else{
         return UNDEF;
      }
   }
}
/*** Manipulation procedures ***/

void addEdge(Graph G, int u, int v){
   if(((u < 1) || (u > getOrder(G))) || ((v < 1) || (v > getOrder(G)))){
      printf("Graph error: calling addEdge() with invalid int");
      exit(EXIT_FAILURE);
   } else{
      addArc(G, u, v);
      addArc(G, v, u);
      G->size-=1;
   }
}
void addArc(Graph G, int u, int v){
	if(((u<1)||(u>getOrder(G)))||((v<1)||(v>getOrder(G)))){
		printf("Graph error: calling addArc() with invalid int");
		exit(EXIT_FAILURE);
	} else{
		int a, len,valid;
		len=length(G->L[u]);
		valid=1;
		if(len!=0){
		   moveFront(G->L[u]);
		   for(int i=1; i<=len; i++){
		      a=get(G->L[u]);
			  if(v==a){
				  valid=0;
			  }
			  moveNext(G->L[u]);
		   } 
		   if(valid==1){
			   prepend(G->L[u], v);
			   sortList(G->L[u]);
			   G->size+=1;
		   }
		} else{
			append(G->L[u], v);
			G->size+=1;
		}
	}
	
}

Graph transpose(Graph G){
	int n=getOrder(G);
	int len;
	int num;
	Graph T=newGraph(n);
	for(int i=1; i<=n; i++){
		len=length(G->L[i]);
		moveFront(G->L[i]);
		for(int j=1; j<=len; j++){	
			num=get(G->L[i]);
			append(T->L[num], i);
			moveNext(G->L[i]);
		}
	}
	T->size=getSize(G);
	return T;
	
}
Graph copyGraph(Graph G){
	int n=getOrder(G);
	Graph C=newGraph(n);
    C->size=G->size;
	for(int i=1; i<=n;i++){
	   C->L[i]=copyList(G->L[i]);
	   C->color[i]=G->color[i];
       C->parent[i]=G->parent[i];
       C->discover[i]=G->discover[i];
       C->finish[i]=G->finish[i];
	}
	return C;
}

void DFS(Graph G, List S){
   if(length(S)==getOrder(G)){
      int t;
	  int i;
	  int num;
	  for(i=1; i<=getOrder(G);i++){
		 G->color[i]=WHITE;
	     G->parent[i]=NIL;
	  }
	  t=0;
	  moveFront(S);
	  for(int j=1; j<=getOrder(G); j++){
		  num=get(S);
		  if(G->color[num]==WHITE){
		     t=visit(G, t, num);
	   	  }
		  moveNext(S);
	   }
	   int min, ind ,finish, current;
	   min=0;
	   G->source=1;
	   clear(S);
	   for(i=1;i<=getOrder(G);i++){
		   for(int j=1; j<=getOrder(G);j++){
			   current=getFinish(G,j);
			   if(getFinish(G,j)>min){
				  if(current<finish){
				     if(current>min){
					    finish=current;
						ind=j;
				     }
			      } else if(finish==0){
					  if(current>min){
					     finish=current;
					     ind=j;
					  }
				  }
			   } 
			}
			min = finish;
			prepend(S,ind);
			finish = 0;
	   }
    } else{
		printf("Graph error: calling DFS() with invalid List");
		exit(EXIT_FAILURE);
	}
}

int visit(Graph G, int time, int u){
	int num;
	int count;
	count = 0;
	time++;
	G->discover[u] = time;
	G->color[u] = GRAY;
	moveFront(G->L[u]);
	for(int i=1; i<=length(G->L[u]); i++){
		num=get(G->L[u]);
		if(G->color[num]==WHITE){
			G->parent[num]=u;
			time=visit(G, time, num);
		}
		moveNext(G->L[u]);
	}
	G->color[u] = BLACK;
	time++;
	G->finish[u] = time;
	count++;
	G->visit[u] = count;
	return time;
}

void printGraph(FILE* out, Graph G){
	for(int i=1; i<= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->L[i]);
		fprintf(out, "\n");
	}
}
