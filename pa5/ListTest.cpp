//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

int main(){

   int i;
   List A, B, C, D, E;

   for(i=1; i<=10; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   
   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl; 
   cout << B.findNext(20) << endl; 
   cout << B.position() << endl;
   cout << B.findPrev(20) << endl;
   cout << B.position() << endl;
   cout << endl;

   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   cout << "A = " << A << endl;
   for( i=1; i<=15; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;

   E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;
   List F;
   F = A.concat(B);
   A = A;
   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << "E = " << E << endl;
   cout << "F = " << F << endl;
   A.clear();
   B.clear();
   A.insertBefore(1);
   A.insertBefore(2);
   A.moveFront();
   int curr = A.peekNext();
   for(int i = 0; i < first; i++){
      A.eraseAfter();
	  B.insertBefore(curr);
	  curr = A.peekNext();
   }
   A.moveFront();
   A.moveNext();
   B.moveFront();  
   for(int i = 0; i < L.size(); i++){
	  curr = B.peekNext();
      A.insertBefore(curr);
	  if(i < (L.size() -1)){
	     A.moveNext();
		 B.moveNext();
	  }
   }
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   A.clear();
   B.clear();
   
   for(int j = 0; j < 10; j++){
	   A.insertBefore(j);
   }
   A.moveFront();
   int curr = A.peekNext();
   for(int i = 0; i < first; i++){
      A.eraseAfter();
	  B.insertBefore(curr);
	  curr = A.peekNext();
   }
   A.moveFront();
   A.moveNext();
   B.moveFront();  
   for(int i = 0; i < L.size(); i++){
	  curr = B.peekNext();
      A.insertBefore(curr);
	  if(i < (L.size() -1)){
	     A.moveNext();
		 B.moveNext();
	  }
   }
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   return(0);
}