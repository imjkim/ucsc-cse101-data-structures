//-----------------------------------------------------------------------------
// FindPath.c
// Juwon Kim, jkim419, pa3
// main program for pa3
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 100
int main(int argc, char * argv[]){
   FILE *in;
   FILE *out;
   if(argc!=3){
	   printf("Usage: %s <input file> <outputfile>\n", argv[0]);
	   exit(1);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in == NULL){
	   printf("Unable to open file %s for reading\n", argv[1]);
	   exit(1);
   }
   if(out == NULL){
	   printf("Unable to open file %s for writing\n", argv[2]);
	   exit(1);
   }
   int n;
   fscanf(in, "%d", &n);
   Graph G=newGraph(n); 
   int x, y;
   fscanf(in, "%d %d", &x,&y);
   while((x!=0)&&(y!=0)){
      addEdge(G,x,y);
	  fscanf(in, "%d %d", &x,&y);
   }
   printGraph(out, G);
   fprintf(out, "\n");
   fscanf(in, "%d %d", &x,&y);
   int d;
   int item;
   List L=newList();
   while((x!=0)&&(y!=0)){
      BFS(G,x);
	  d = getDist(G, y);
	  if(d == INF){   
         fprintf(out, "The distance from %d to %d is infinity\n", x, y);
		  fprintf(out, "No %d-%d path exists\n\n", x, y);
	  } else{
		 clear(L);
		 getPath(L, G, y);
		 moveFront(L);
		 if(get(L)==NIL){
			fprintf(out, "The distance from %d to %d is infinity\n", x, y);
			fprintf(out, "No %d-%d path exists\n\n", x, y);
		 } else{
			fprintf(out, "The distance from %d to %d is %d\n", x, y, d);
			fprintf(out, "A shortest %d-%d path is: ", x, y);
			for(int i=1; i<=length(L); i++){
				item = get(L);
				fprintf(out, "%d ", item);
				moveNext(L);
			}
			fprintf(out, "\n\n");
		 }
	  }  
	  fscanf(in, "%d %d", &x,&y);
   } 
   freeGraph(&G);
   freeList(&L);
   fclose(in);
   fclose(out);
   return(0);
}