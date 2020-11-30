//-----------------------------------------------------------------------------
// Shuffle.cpp
// Juwon Kim, jkim419, pa5
// main program for Dictionary ADT 
// compile:
//
//      g++ -std=c++11 -Wall -o FileIO FileIO.cpp
//
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include "List.h"
#include <iomanip>

using namespace std;

#define MAX_LEN 300
void shuffle(List& D){
   int n = D.size();
   int first = n / 2;
   D.moveFront();
   List L;
   L.moveFront();
   int curr = D.peekNext();
   for(int i = 0; i < first; i++){
      D.eraseAfter();
	  L.insertBefore(curr);
	  curr = D.peekNext();
	  //cout << "c" << endl;
   }
   D.moveFront();
   D.moveNext();
   L.moveFront();  
   //cout << "a" << endl;
   for(int i = 0; i < L.size(); i++){
	  curr = L.peekNext();
      D.insertBefore(curr);
	  if(i < (L.size() -1)){
	     D.moveNext();
		 L.moveNext();
	  }
	  //cout << "b" << endl;
   }
   L.clear();
}

int main(int argc, char * argv[]){

   int n, count;
   char* token;
   count = 0;
   // check command line for correct number of arguments
   if( argc != 2 ){
      cout << "Shuffle takes in only 1 argument. Please use a positive integer";
      return(EXIT_FAILURE);
   }

   // store the number into a variable
   token=argv[1];
   n = atoi(token);
   List D;
   cout << "deck size       shuffle count" << endl;
   cout << "------------------------------" << endl;
   for(int i = 1; i <= n; i++){
	   cout << " "<< setw(16) << left << i;
	   for(int j = 1; j <= i; j++){  
	      D.insertBefore(j);
	   }
	   List L;
	   L = List(D);
	   L = D;
	   while(true){
		  shuffle(D);
		  count++;
          if(L == D){
		     cout << count << endl;
			 break;
          }
	   }
	   D.clear();
	   D.moveFront();
	   count = 0;
   }
   return(EXIT_SUCCESS);
}