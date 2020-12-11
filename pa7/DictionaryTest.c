//-----------------------------------------------------------------------------
// DictionaryTest.c
// Juwon Kim, jkim419, pa7
// test file for Dictionary ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

int main(){
   
   int i, n=26;
   Dictionary A = newDictionary(0);   //2 dictionaries which are unique or non unique
   Dictionary B = newDictionary(1);
   char* wordBank[] = {"a", "e", "c", "t", "s"}
   char* word[] = { "n","z","w","k","i","c","l","d","t","a", 
                    "e","y","b","h","v","f","s","m","x","r",
                    "o","u","p","g","j","q" };
   VAL_TYPE a;
   VAL_TYPE b;
   VAL_TYPE C;
   
   insert(A, wordBank[0];
   insert(A, wordBank[2];
   insert(A, wordBank[3];
   printDictionary(stdout, A, "pre");
   
   makeEmpty(A);
   printDictionary(stdout, A, "post");
   
   for(i=0; i<n; i++){
      insert(A, word[i], i);
   }
   printDictionary(stdout, A, "pre");
   
   for(i=n-1; i>=0; i--){
      insert(B, word[i], i);
   }
   int size = size(B);
   printf("size of B: %d", size);
   printDictionary(stdout, B, "pre");
   delete(D, "k");
   printDictionary(stdout, B, "pre");
   printf("\n\n");

   // reverse iteratation over B 
   printf("reverse B:\n");
   for(y=beginReverse(B); currentVal(B)!=VAL_UNDEF; y=prev(B)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(B), y);
   }
   printf("\n\n");


   // print Dictionary A ----------------------------------
   printf("Dictionary A (%sunique keys):\n", (getUnique(A)?"":"non-"));
   printDictionary(stdout, A, "pre");
   printf("\n");

   // print Dictionary B
   printf("Dictionary B (%sunique keys):\n", (getUnique(B)?"":"non-"));
   printDictionary(stdout, B, "pre");
   printf("\n");


   // delete keys from A ----------------------------------
   for(i=0; i<n; i+=2){
      delete(A, word[i]);
   }

   // print Dictionary A after deletions
   printf("Dictionary A (%sunique keys):\n", (getUnique(A)?"":"non-"));
   printf("after deletions:\n");
   printDictionary(stdout, A, "pre");
   printf("\n");


   // delete keys from B ----------------------------------
   for(i=1; i<n; i+=2){
      delete(B, word[i]);
   }

   // print Dictionary B after deletions
   printf("Dictionary B (%sunique keys):\n", (getUnique(B)?"":"non-"));
   printf("after deletions:\n");
   printDictionary(stdout, B, "pre");
   printf("\n");


   // insert duplicates into A ----------------------------
   for(i=1; i<n; i+=2){
      insert(A, word[i], i);
   }
    
   // free heap memory ------------------------------------
   freeDictionary(&A);
   freeDictionary(&B);

   return(0);
}
