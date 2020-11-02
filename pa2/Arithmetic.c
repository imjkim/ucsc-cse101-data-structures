//-----------------------------------------------------------------------------
// Arithmetic.c
// Juwon Kim, jkim419, pa2
// main program for pa2
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"
#define MAX_LEN 255

int main(int argc, char * argv[]){
   FILE *in;
   FILE *out;
   char buff[MAX_LEN];
   char * line;
   int pos1, pos2;
   if(argc!=3){
      printf("Usage: %s <input file> <outputfile>\n", argv[0]);
      exit(1);
   }
   //open in and out files
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   //check if the input output files are null or not
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   fgets(buff, MAX_LEN, in);	//we just need to read 4 lines but I found this easy
   line = malloc(MAX_LEN * sizeof(char));
   strcpy(line, "");
   sscanf(buff, "%4[^\n]", line);
   pos1=atoi(line);
   //fprintf(out, "length is: %d", pos1);
   free(line);
   
   BigInteger A;
   fgets(buff, MAX_LEN, in);	
   line = malloc(pos1 * sizeof(char));
   strcpy(line, "");
   sscanf(buff, "%999[^\n]", line);
   //fprintf(out, "\nline is: %s", line);
   if(line[strlen(line)-1] == '\n'){
	  line[strlen(line)-1] = '\0';
   }
             //error with my test case where string would include newline
	
   A=stringToBigInteger(line);
   free(line);
   
   fgets(buff, MAX_LEN, in);	
   line = malloc(MAX_LEN * sizeof(char));
   strcpy(line, "");
   sscanf(buff, "%4[^\n]", line);
   pos2=atoi(line);
   free(line);
   
   BigInteger B;
   fgets(buff, MAX_LEN, in);	
   line = malloc(pos2 * sizeof(char));
   strcpy(line, "");
   sscanf(buff, "%999[^\n]", line);
    //fprintf(out, "\nline is: %s", line);
   //fprintf(out, "\nline is: %s", line);
   B=stringToBigInteger(line);
   free(line);
   
   printBigInteger(out, A);            //A
   printBigInteger(out, B);			   //B
  // BigInteger AB=newBigInteger();
  // multiply(AB, A, B);
 //  printBigInteger(out, AB);
 //  freeBigInteger(&AB);
   BigInteger C=sum(A,B);
   printBigInteger(out, C);    	       //A+B
   freeBigInteger(&C);
   BigInteger D=diff(A,B);
   printBigInteger(out, D);            //A-B
   freeBigInteger(&D);
   BigInteger E=diff(A,A);
   printBigInteger(out, E);            //A-A
   freeBigInteger(&E);
   BigInteger F=sum(A,A);
   BigInteger G=sum(F,A);              //3A
   freeBigInteger(&F);
   BigInteger H=sum(B,B);              //2B
   BigInteger I=diff(G,H);             //3A-2B
   printBigInteger(out, I);
   freeBigInteger(&G);
   freeBigInteger(&H);
   freeBigInteger(&I);
   
   BigInteger K=prod(A,A);
   BigInteger L=prod(B,B);
   BigInteger KL=prod(A,B);
   printBigInteger(out, KL);           //AB
   freeBigInteger(&KL);
   printBigInteger(out, K);            //A^2
   printBigInteger(out, L);            //B^2
   
   BigInteger M=prod(K,K);			   //A^4
   BigInteger A1=sum(M,M);			   //2A^4
   BigInteger A2=sum(A1,M);			   //3A^4
   BigInteger A3=sum(A2,A2);
   BigInteger A4=sum(A3,A2);	       //9A^4
   
   BigInteger N=prod(L,L);   		   //B^2
   BigInteger O=prod(N,N);			   //B^4
   BigInteger P=prod(O,B);			   //B^5
   BigInteger B1=sum(P,P);
   BigInteger B2=sum(B1,B1);		   //4B^5
   BigInteger B3=sum(B2,B2);
   BigInteger B4=sum(B3,B3);
   BigInteger Q=sum(A4,B4);		       //9A^4+16B^5
   printBigInteger(out, Q);
   
   freeBigInteger(&A1);
   freeBigInteger(&B1);
   freeBigInteger(&A2);
   freeBigInteger(&B2);
   freeBigInteger(&A3);
   freeBigInteger(&B3);
   freeBigInteger(&A4);
   freeBigInteger(&B4);
    freeBigInteger(&K);
   freeBigInteger(&L);
    freeBigInteger(&M);
   freeBigInteger(&N);
    freeBigInteger(&O);
   freeBigInteger(&P);
    freeBigInteger(&Q);
  
   freeBigInteger(&A);
   freeBigInteger(&B);
   fclose(in);
   fclose(out);
   return(0);
}