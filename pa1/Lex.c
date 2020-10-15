//-----------------------------------------------------------------------------
// Lex.c
// Juwon Kim, jkim419, pa1
// executing program that handles list
//-----------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "List.h"
#define MAX_LEN 100
int main(int argc, char * argv[]){
   int count, index;
   FILE *in, *out;
   char line[MAX_LEN];
   if(argc!=3){
	   printf("Usage: %s <input file> <outputfile>\n", argv[0]);
	   exit(1);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
	   printf("Unable to open file %s for reading\n", argv[1]);
	   exit(1);
   }
   if( out==NULL ){
	   printf("Unable to open file %s for writing\n", argv[2]);
	   exit(1);
   }
   count = 0;
   while(fgets(line,MAX_LEN, in)!= NULL){
	   count++;
   }
   int n;
   char stringArray[count][MAX_LEN];
   char output[count][MAX_LEN];
   fseek(in, 0, SEEK_SET);
   n = 0;
   while(fgets(line,MAX_LEN, in)!= NULL){
	   strcpy(stringArray[n], line);
	   strcpy(output[n], line);
	   n++;
   }
   int x, y;
   List L=newList();
   char string[MAX_LEN];
   //int used[count];
   for(x=0; x<count; x++){
	  strcpy(string,stringArray[x]);
	  for(y=0; y<count; y++){
         if(strcmp(stringArray[y],string)<0){
			 strcpy(string,stringArray[y]);
		 }
	  }
	  for(y=0; y<count; y++){
		  if(strcmp(stringArray[y],string)==0){
			 append(L,y);
		     strcpy(stringArray[y], "}");
		  }
	  }
   }
   moveFront(L);
   for(int i=0; i<count; i++){
	   index = get(L);
	   fprintf(out, "%s\n", output[index]);
	   moveNext(L);
   }
   freeList(&L);
   fclose(in);
   fclose(out);
   return(0);
}
