//-----------------------------------------------------------------------------
// Order.c
// Juwon Kim, jkim419, pa7
// main program for pa7
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"

#define MAX_LEN 256
int main(int argc, char * argv[]){
   FILE *in;
   FILE *out;
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
   Dictionary D =newDictionary(0);
   char input[BUFSIZ];
   
   while(fgets(input,BUFSIZ,in)!=NULL){
	   char* line;
	   line=malloc(MAX_LEN*sizeof(char));
	   strcpy(line,"");									//so that it doesnt give errors
	   sscanf(input, "%[^\n]",line);
	   insert(D,line,NULL);
	   free(line);
   }
   
   fprintf(out, "******************************************************\nPRE-ORDER:\n******************************************************\n");
   printDictionary(out, D, "pre");
   fprintf(out, "\n\n");
   fprintf(out, "******************************************************\nIN-ORDER:\n******************************************************\n");
   printDictionary(out, D, "in");
   fprintf(out, "\n\n");
   fprintf(out, "******************************************************\nPOST-ORDER:\n******************************************************\n");
   printDictionary(out, D, "post");
   
   freeDictionary(&D);
   fclose(in);
   fclose(out);
   return(0);
}