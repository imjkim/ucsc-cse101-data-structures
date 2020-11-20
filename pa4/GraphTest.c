//-----------------------------------------------------------------------------
// GraphClient.c
// Juwon Kim, jkim419, pa4
// test file for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   Graph G = NULL;
   G = newGraph(10);
   addEdge(G, 1, 2);
   addEdge(G, 1, 3);
   addEdge(G, 3, 4);
   addEdge(G, 2, 4);
   addEdge(G, 2, 5);
   addEdge(G, 2, 6);
   addEdge(G, 3, 8);
   addEdge(G, 5, 6); 
   addEdge(G, 4, 6);
   addEdge(G, 5, 9);
   addEdge(G, 8, 9);
   addEdge(G, 6, 8);
   addEdge(G, 3, 6);
   addEdge(G, 6, 10);
   List L = newList();
   DFS(G,L);   
   fprintf(stdout, "\nPrinting stack for original graph\n");
   printList(stdout, L);
   Graph T=transpose(G);
   List TranList = newList();
   DFS(T, TranList);
   fprintf(stdout, "\nprinting stack for transposed graph\n");
   printList(stdout, L);
   int parent, discover, finish;
   int i;
   fprintf(stdout, "Adjacency lists for G:");
   fprintf(stdout, "\n");
   printGraph(stdout, G);
   for(i = 1; i<=length(L); i++){
 	  parent = getParent(G, i);
	  fprintf(stdout, "\nparent: %d ", parent);
   }
   for(i = 1; i<=length(L); i++){
	  discover = getDiscover(G, i);
	  fprintf(stdout, "\ndiscover: %d ", discover);
   }
   for(i = 1; i<=length(L); i++){
	  finish = getFinish(G,i);
	  fprintf(stdout, "\nfinish: %d ", finish);
   }
   for(i = 1; i<=length(L); i++){
 	  parent = getParent(T, i);
	  fprintf(stdout, "\nparent: %d ", parent);
   }
   for(i = 1; i<=length(L); i++){
	  discover = getDiscover(T, i);
	  fprintf(stdout, "\ndiscover: %d ", discover);
   }
   for(i = 1; i<=length(L); i++){
	  finish = getFinish(T,i);
	  fprintf(stdout, "\nfinish: %d ", finish);
   }
   //print graph T
   printf(stdout, "Adjacency lists for T:");
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   // Free objects 
   freeGraph(&T);
   freeList(&L);
   freeGraph(&G);

   return(0);
}