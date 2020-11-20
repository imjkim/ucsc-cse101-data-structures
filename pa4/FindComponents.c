//-----------------------------------------------------------------------------
// FindComponents.c
// Juwon Kim, jkim419, pa4
// executing program for pa4
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 101

int main(int argc, char * argv[]){
   FILE *in;
   FILE *out;
   if(argc!=3){
	   printf("Usage: %s <input file> <outputfile>\n", argv[0]);
	   exit(1);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in == NULL ){
	   printf("Unable to open file %s for reading\n", argv[1]);
	   exit(1);
   }
   if(out == NULL ){
	   printf("Unable to open file %s for writing\n", argv[2]);
	   exit(1);
   }
   int num;
   fscanf(in, "%d", &num);
   Graph G= newGraph(num); 
   int x, y;
   fscanf(in, "%d %d", &x,&y);
   while((x!=0)&&(y!=0)){
      addArc(G, x, y);
	  fscanf(in, "%d %d", &x,&y);
   }
   fprintf(out, "Adjacency list representation of G:");
   fprintf(out, "\n");
   printGraph(out, G);
   fprintf(out, "\n");
   
   Graph T=transpose(G);
   int s, i;
   List L = newList();
   for(i = 1; i <= getOrder(G); i++){
	   append(L, i);
   }
   DFS(G,L);   
   List copyL = copyList(L);
   DFS(T,L);
   s=0;
   for(i = 1; i<=length(L);i++){
	   if(getParent(T, i) == NIL){
		   s++;
	   }
   }
   fprintf(out, "G contains %d strongly connected components:", s);
   List P = newList();
   num = 0;
   int valid;
   valid=1;
   int temp;
   moveBack(L);
   moveFront(copyL);
   temp = get(copyL);
   int count;
   for(i = 1; i<= s; i++){           //s is number of scc
	 while (valid == 1){
	     prepend(P, get(L));
		 if(get(L) == temp){
			if(index(L)!=0){
			   movePrev(L);
			}
			valid = 0;
            break;
		 } 
		 if(index(L)!=0){
		    movePrev(L);
			count++;
		 } else{
			valid = 0;
			break;
		 }
	  }
	  valid = 1;
	  for(int j=0; j<=count; j++){
		  if(index(copyL)!=length(copyL)-1){
            moveNext(copyL);
		  }
	  }
	  count = 0;
	  temp = get(copyL);
	  fprintf(out, "\nComponent %d: ", i);
	  printList(out, P);
	  clear(P);
   }
   /* for(i = 1; i <= s; i++){
      fprintf(out, "\nComponent %d: ", i);
	  while(valid==1){
		 num = get(L);
         if(curr < num){
			curr = length(L) + 1;
		    valid = 0;
			break;
		 } 
		 if( curr == num ){             //first iteration
		    prepend(P, num);
		    movePrev(L);
		 } else{
			prepend(P, num);
			curr = num;
	        if(index(L) != 0){
			   movePrev(L);
			} else{
			   valid = 0;
			   break;
			}
		 }
	  } */
		/* printList(out,P);
		clear(P);
		valid = 1;
   }   */  
   freeList(&P);
   freeList(&L); 
   freeGraph(&T);
   freeGraph(&G);
   fclose(in);
   fclose(out);
   return(0);
}
