
//-----------------------------------------------------------------------------
// List.c
// Juwon Kim, jkim419, pa4
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
   L->index=-1;
   L->front=L->back=NULL;
   L->length=0;
   return L;
}
Item newItem(int data){
   Item I=malloc(1*sizeof(NodeObj));
   I->data=data;
   return(I);
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
   return L->length;
}

int index(List L){
   if(L->index<0){
      return -1;
   } else{
      return L->index;
   }
} 
int front(List L){
   if(length(L)>0){
      return L->front->data;
   } else{
      printf("List Error: calling front() on empty List");
      exit(EXIT_FAILURE);
   }
}    // Returns front element of L. Pre: length()>0
int back(List L){
   if(length(L)>0){
      return L->back->data;
   } else{
      printf("List Error: calling back() on empty List");
      exit(EXIT_FAILURE);
   }
} // Returns back element of L. Pre: length()>0

int get(List L){
   if((length(L)>0) && index(L)>=0){
      int data;
      data=L->cursor->data;
      return data;
   } else{
      printf("List Error: calling get() on empty List or a List with undefined index");
      exit(EXIT_FAILURE);
   }
}  // Returns cursor element of L. Pre: length()>0, index()>=0
void sortList(List L){
	int b;
	Item current=L->front;
	Item index=NULL;
	if(current==NULL){
	} else{
		while(current!=0){
			index=current->next;
			while(index!=NULL){
				if((current->data) > (index->data)){
					b=current->data;
					current->data=index->data;
					index->data=b;
				}
				index=index->next;
			}
			current=current->next;
		}
	}
}
void sortList2(List L){
	int b;
	Item current=L->front;
	Item index=NULL;
	if(current==NULL){
	} else{
		while(current!=0){
			index=current->next;
			while(index!=NULL){
				if((current->data) < (index->data)){
					b=current->data;
					current->data=index->data;
					index->data=b;
				}
				index=index->next;
			}
			current=current->next;
		}
	}
}
int equals(List A, List B){
   int eq;
   eq=0;
   int len;
   Item a=NULL;
   Item b=NULL;
   if(A==NULL || B==NULL){
      printf("List Error: calling equals() on NULL List");
	  exit(EXIT_FAILURE);
   }
   eq=(length(A)==length(B));
   len=length(A);
   a=A->front;
   b=B->front;
   while(eq && (len>0)){
      eq = (a->data==b->data);
	  len--;
	  a=a->next;
	  b=b->next;
   }
   return eq;
} // Returns true (1) iff Lists A and B are in same
 // state, and returns false (0) otherwise.

void clear(List L){
   while(length(L)!=0){
      deleteFront(L);
   }
}  // Resets L to its original empty state.
void moveFront(List L){
   if(L->length!=0){
      L->cursor=L->front;
	  L->index=0;
   }
}  // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveBack(List L){
   if(L->length!=0){
      L->cursor=L->back;
	  L->index=length(L)-1;
   }
} // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void movePrev(List L){
   if((L->cursor!=NULL)&&(L->cursor!=L->front)){
	  L->cursor=L->cursor->prev;
      L->index-=1;
   } else if((L->cursor!=NULL)&&(L->cursor==L->front)){
      L->cursor=NULL;
	  L->index=-1;
   } 
} // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
   if((L->cursor!=NULL)&&(L->cursor!=L->back)){
      L->index+=1;
	  L->cursor=L->cursor->next;
   } else if((L->cursor!=NULL)&&(L->cursor=L->back)){
      L->index=-1;
	  L->cursor=NULL;
   }
} // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, int data){
   Item I = newItem(data);
   if(length(L)==0){
      L->front=L->back=I;
   } else{
	  I->next=L->front;
	  L->front->prev=I;    //set bidirectional links
	  L->front=I;
	  if((index(L)>=0)&&(L->cursor!=NULL)){ 
		  L->index+=1;     //increase the index for a new element is before the index
	  }
   }
   L->length+=1;
}
       // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void append(List L, int data){
   Item I = newItem(data);
   if(length(L)==0){
      L->front=L->back=I;
   } else{
	  I->prev=L->back;
      L->back->next=I;
	  L->back=I;
   }
   L->length+=1;
}
       // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.

void insertBefore(List L, int data){
   if((length(L)>0)&&(index(L)>=0)){
      if(index(L)==0){                              //if index is at the first Item, implement prepend()
         prepend(L, data);
      } else{
         Item new=newItem(data);
		 L->cursor->prev->next=new;
		 new->next=L->cursor;
		 new->prev=L->cursor->prev;
		 L->cursor->prev=new;
		 L->index+=1;
		 L->length+=1;
      } 
   } else{
      printf("List error: insertBefore() called on an empty list");
      exit(EXIT_FAILURE);
   }
}
       // Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int data){
   if((length(L)>0)&&(index(L)>=0)){
	  if(index(L)==length(L)-1){                      //if index is at the last Item, just implement append()
		  append(L, data);
	  } else{
		  Item I=newItem(data);
		  I->next=L->cursor->next;
		  I->prev=L->cursor;
		  L->cursor->next=I;
           L->length+=1;     
	  }		   
   } else{
      printf("List error: insertBefore() called on an empty list");
      exit(EXIT_FAILURE);
   }
} // Insert new element after cursor.
 // Pre: length()>0, index()>=0
void deleteFront(List L){
   if(length(L)>0){
      if(length(L)==1){
         freeItem(&L->front);
		 L->back=NULL;
		 if(index(L)==0){
			L->index=-1;
			L->cursor=NULL;
		 }
	  } else{
         Item new=L->front->next;
         freeItem(&L->front);  
         L->front=new;
		 if(index(L)==0){
			L->index=-1;
			L->cursor=NULL;
		 } else{
			L->index-=1;
		 }
      }
      L->length-=1;
   } else{ 
      printf("deleteFront() called on empty list");
      exit(EXIT_FAILURE);
   }
} // Delete the front element. Pre: length()>0
void deleteBack(List L){
   if(length(L)>0){
      if(length(L)==1){
         freeItem(&L->front);
		 L->back=NULL;
		 if(index(L)==0){
			 L->index=-1;
			 L->cursor=NULL;
		 }
      } else{
         Item new=L->back->prev;
         freeItem(&L->back);
         L->back=new;
		 if(index(L)==length(L)-1){
			L->index=-1;
			L->cursor=NULL;
		 }
      }
      L->length-=1;
   } else{
      printf("List error: deleteBack() called on empty list");
      exit(EXIT_FAILURE);
   }
} // Delete the back element. Pre: length()>0
void delete(List L){                                  //if List is not empty, make index and cursor undefined
   if((length(L)>0)&&(index(L)>=0)){
      if(L->cursor==L->front){                        //if cursor is the front, execute deleteFront() function
         deleteFront(L);
		 L->index=-1;
		 L->cursor=NULL;
      } else if(L->cursor==L->back){
         deleteBack(L);
		 L->index=-1;
		 L->cursor=NULL;
      } else{
         Item before=L->front;
         for(int i=1; i<index(L); i++){
            before=before->next;
         }
         Item after=before->next->next;
         freeItem(&before->next);
         before->next=after; 
		 after->prev=before;
		 L->cursor=NULL;
		 L->length-=1; 
		 L->index=-1;
      }
   } else{
      printf("List error: delete() called on empty list or a list with undefined cursor");
      exit(EXIT_FAILURE);   
   }
}  // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
   Item N = NULL;
   if(L==NULL){
      printf("List Error: calling printList() on NULL list");
	  exit(EXIT_FAILURE);
   }
   for(N = L->front; N!=NULL; N=N->next){
      fprintf(out, "%d ", N->data);
   }
}
// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
List copyList(List L){
   List new= newList();
   Item current= L->front;
   for(int i=0; i<L->length; i++){
      append(new, current->data);                 //append the front Item and the following nodes until it reaches end of the list
	  current=current->next;
   }
   return new;
}
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
