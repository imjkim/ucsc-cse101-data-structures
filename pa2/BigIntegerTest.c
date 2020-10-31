/****************************************************************************************
*  BigIntegerTest.c
*  Juwon Kim, jkim419, pa2
*  Test client for BigInteger ADT
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"


int main(){
   char s[]="1111";
   BigInteger A=stringToBigInteger(s);
   BigInteger B=copy(A);
   printf("%d",equals(A,B));
   BigInteger C = prod(A,B);
   printBigInteger(stdout, C);
   /* char s[52]="6523485630758234007488392857982374523487612398700554";
   BigInteger A =stringToBigInteger(s);
   printList(stdout,A->L); */
   freeBigInteger(&A);
   freeBigInteger(&B);
   freeBigInteger(&C);
   return 1;
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/