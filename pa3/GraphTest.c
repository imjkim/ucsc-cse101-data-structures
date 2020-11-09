//-----------------------------------------------------------------------------
// GraphClient.c
// Juwon Kim, jkim419, pa3
// test file for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   Graph G = NULL;
   G = newGraph(6);
   addEdge(G, 1, 2);
   addEdge(G, 1, 3);

   addEdge(G, 2, 6);
   addEdge(G, 4, 5);
   addEdge(G, 5, 6); 

   printGraph(stdout, G);
   
  
   // Free objects 
  
   freeGraph(&G);

   return(0);
}