//-----------------------------------------------------------------------------
// Lex.c
// Juwon Kim, jkim419, pa6
// main program for pa6
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"

#define MAX_LEN 100
int main(int argc, char * argv[]){
   FILE *in;
   FILE *out;
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
   //fseek(in, 0, SEEK_SET);
   Dictionary D=newDictionary(0);
   int n = 0;
   int count = 0;
   while(fgets(line,MAX_LEN, in)!= NULL){
	   count++;
   }
   char stringArray[count][MAX_LEN];
   fseek(in, 0, SEEK_SET);
   while(fgets(stringArray[n], MAX_LEN, in)!= NULL){
	   n++;
   }
   for(int x = 0; x < count; x++){
	   insert(D, stringArray[x], x);
   }
   printDictionary(out, D);
   /* fprintf(out, "******************************************************\n");
   fprintf(out, "PRE-ORDER:\n");
   fprintf(out, "******************************************************\n");
   printDictionary(out, D, "pre");
   fprintf(out, "******************************************************\n");
   fprintf(out, "IN-ORDER:\n");
   fprintf(out, "******************************************************\n");
   printDictionary(out, D, "in");
   fprintf(out, "******************************************************\n");
   fprintf(out, "POST-ORDER:\n");
   fprintf(out, "******************************************************\n");
   printDictionary(out, D, "post"); */
   freeDictionary(&D);
   fclose(in);
   fclose(out);
   return(0);
}