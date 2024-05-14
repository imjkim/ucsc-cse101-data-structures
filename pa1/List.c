
//-----------------------------------------------------------------------------
// List.c
// Juwon Kim, jkim419, pa1
// Implementation file for List ADT
//-----------------------------------------------------------------------------
//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj{
   int data; 
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;
typedef NodeObj* Item;

typedef struct ListObj{
   Item front;
   Item back;
   Item cursor;
   int index;
   int length;
} ListObj;
typedef ListObj* List;



List newList() {
   List L = malloc(1*sizeof(ListObj));
   L->index = -1;
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   return L;
}
Item newItem(int data){
   Item I = malloc(1*sizeof(NodeObj));
   I->data = data;
   return I;
}
void freeItem(Item* pN){
   if(pN!=NULL && *pN!=NULL){
      free(*pN);
      *pN = NULL;
   }
}
void freeList(List* pL) {
   if(pL!=NULL && *pL!=NULL){
      while(length(*pL)!=0){
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}
// Access functions -----------------------------------------------------------
int length(List L){
   if(L!=NULL){
	  return L->length;
   } else{
	  printf("List error: length() called on null List");
	  exit(EXIT_FAILURE);
   }
}

int index(List L){
   if(L->index<0){
      return -1;
   } else{
      return L->index;
   }
} 
int front(List L){          // Returns front element of L. Pre: length()>0
   if(length(L)>0){
      return L->front->data;
   } else{
      printf("List Error: calling front() on empty List");
      exit(EXIT_FAILURE);
   }
}   
int back(List L){           // Returns back element of L. Pre: length()>0
   if(length(L)>0){
      return L->back->data;
   } else{
      printf("List Error: calling back() on empty List");
      exit(EXIT_FAILURE);
   }
} 

int get(List L){            // Returns cursor element of L. Pre: length()>0, index()>=0
   if((length(L)>0) && index(L)>=0){
      int data;
      data = L->cursor->data;
      return data;
   } else{
      printf("List Error: calling get() on empty List or a List with undefined index");
      exit(EXIT_FAILURE);
   }
}  

int equals(List A, List B){
   int equal;
   if(A==NULL || B==NULL){
      printf("List Error: calling equals() on NULL List or Lists");
	  exit(EXIT_FAILURE);
   }
   if(A->length == B->length){
	  equal = 1;
   }
   Item a = A->front;
   Item b = B->front;
   while(equal && a!=NULL){
      equal = (a->data==b->data);
	  a = a->next;
	  b = b->next;
   }
   return equal;
} // Returns true (1) iff Lists A and B are in same
 // state, and returns false (0) otherwise.

void clear(List L){
   while(length(L) != 0){
      deleteFront(L);
   }
}  // Resets L to its original empty state.
void moveFront(List L){
   if(L->length != 0){
      L->cursor = L->front;
	  L->index = 0;
   }
}  // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveBack(List L){
   if(L->length != 0){
      L->cursor = L->back;
	  L->index = length(L)-1;
   }
} // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void movePrev(List L){
   if((L->cursor!=NULL)&&(L->cursor!=L->front)){
	  L->cursor = L->cursor->prev;
      L->index--;
   } else if((L->cursor!=NULL)&&(L->cursor==L->front)){
      L->cursor = NULL;
	  L->index = -1;
   } 
} // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
   if((L->cursor!=NULL)&&(L->cursor!=L->back)){
      L->index++;
	  L->cursor = L->cursor->next;
   } else if((L->cursor != NULL)&&(L->cursor = L->back)){
      L->index = -1;
	  L->cursor = NULL;
   }
} // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, int data){
   Item I = newItem(data);
   if(length(L) == 0){
      L->front = L->back = I;
   } else{
	  I->next = L->front;
	  L->front->prev = I;    //connect both ways
	  L->front = I;
	  if((index(L) >= 0)&&(L->cursor != NULL)){ 
		  L->index++;     //increment 
	  }
   }
   L->length+=1;
}
   
void append(List L, int data){
   Item I = newItem(data);
   if(length(L) == 0){
      L->front = L->back = I;
   } else{
	  I->prev = L->back;
      L->back->next = I;
	  L->back = I;
   }
   L->length++;
}

void insertBefore(List L, int data){
   if((length(L) > 0)&&(index(L) >= 0)){
      if(index(L) == 0){                              //if index is at the first Item, implement prepend()
         prepend(L, data);
      } else{
         Item new = newItem(data);
		 L->cursor->prev->next = new;
		 new->next = L->cursor;
		 new->prev = L->cursor->prev;
		 L->cursor->prev = new;
		 L->index++;
		 L->length++;
      } 
   } else{
      printf("List error: insertBefore() called on an empty list");
      exit(EXIT_FAILURE);
   }
}
 
 // Pre: length()>0, index()>=0
void insertAfter(List L, int data){
   if((length(L) > 0)&&(index(L) >= 0)){
	  if(index(L) == length(L)-1){                      //if index is at the last Item, just implement append()
		  append(L, data);
	  } else{
		  Item new = newItem(data);
		  new->next = L->cursor->next;
		  new->prev = L->cursor;
		  L->cursor->next = new;
          L->length++;     
	  }		   
   } else{
      printf("List error: insertBefore() called on an empty list");
      exit(EXIT_FAILURE);
   }
} // Insert new element after cursor.
 // Pre: length()>0, index()>=0
void deleteFront(List L){
   if(length(L)>0){
      if(length(L) == 1){
         freeItem(&L->front);
		 L->back = NULL;
		 if(index(L) == 0){
			L->index=-1;
			L->cursor = NULL;
		 }
	  } else{
         Item new = L->front->next;
         freeItem(&L->front);  
         L->front = new;
		 if(index(L) == 0){
			L->index = -1;
			L->cursor = NULL;
		 } else{
			L->index--;
		 }
      }
      L->length-=1;
   } else{ 
      printf("deleteFront() called on empty list");
      exit(EXIT_FAILURE);
   }
} // Delete the front element. Pre: length()>0
void deleteBack(List L){
   if(length(L) > 0){
      if(length(L) == 1){
         freeItem(&L->front);
		 L->back=NULL;
		 if(index(L) == 0){
			 L->index = -1;
			 L->cursor = NULL;
		 }
      } else{
         Item new = L->back->prev;
         freeItem(&L->back);
         L->back = new;
		 if(index(L) == length(L)-1){
			L->index = -1;
			L->cursor = NULL;
		 }
      }
      L->length--;
   } else{
      printf("List error: deleteBack() called on empty list");
      exit(EXIT_FAILURE);
   }
} // Delete the back element. Pre: length()>0
void delete(List L){                                  //if List is not empty, make index and cursor undefined
   if((length(L) > 0)&&(index(L) >= 0)){
      if(L->cursor == L->front){                        //if cursor is the front, execute deleteFront() function
         deleteFront(L);
		 L->index = -1;
		 L->cursor = NULL;
      } else if(L->cursor == L->back){
         deleteBack(L);
		 L->index = -1;
		 L->cursor = NULL;
      } else{
         Item before = L->front;
         for(int i=1; i<index(L); i++){
            before = before->next;
         }
         Item after = before->next->next;
         freeItem(&before->next);
         before->next = after; 
		 after->prev = before;
		 L->cursor = NULL;
		 L->length--; 
		 L->index = -1;
      }
   } else{
      printf("List error: delete() called on empty list or a list with undefined cursor");
      exit(EXIT_FAILURE);   
   }
}  // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
   Item this;
   if(L != NULL){
	  this = L->front;
      while(this != NULL){
		 printf("%d ", this->data);
		 this = this->next;
	  }
   } else{
	  printf("List Error: calling printList() on NULL list");
	  exit(EXIT_FAILURE);
   }
}
// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
List copyList(List L){
   List new = newList();
   Item current = L->front;
   for(int i=0; i < L->length; i++){
      append(new, current->data);                //append the items
	  current = current->next;
   }
   return new;
}
