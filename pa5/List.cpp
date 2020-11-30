//-----------------------------------------------------------------------------
// List.cpp
// Juwon Kim, jkim419, pa5
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include"List.h"

using namespace std;


List::Node::Node(int x){
   data=x;
   next=nullptr;
   prev=nullptr;
}

// Class Constructors & Destructors ----------------------------------------
  
// Creates new List in the empty state.
List::List(){
   frontDummy=new Node(0);
   backDummy= new Node(0);
   beforeCursor=frontDummy;
   afterCursor=backDummy;
   pos_cursor=0;
   num_elements=0;
}

   // Copy constructor.
List::List(const List& L){
   frontDummy = new Node(0);
   backDummy= new Node(0);
   pos_cursor=0;
   num_elements=0;
   beforeCursor=frontDummy;
   afterCursor=backDummy;
   if(L.num_elements>0){
      Node* B=L.frontDummy;
	  B = B->next;
      for(int i = 0; i < L.num_elements; i++){         //if there is a node after frontDummy
	     insertBefore(B->data);
		 B=B->next;
      }
	  moveFront();
      for(int i=0; i < L.pos_cursor;i++){
	     moveNext();
      }
   }
}
   // Destructor
   List::~List(){
      clear();
	  num_elements = pos_cursor = 0;
	  delete frontDummy;
	  delete backDummy;
   }

   // Access functions --------------------------------------------------------

   // isEmpty()
   // Returns true if this List is empty, false otherwise.
   bool List::isEmpty(){
	   if(size() == 0){
		   return true;
	   }
	   return false;
   }

   // size()
   // Returns the size of this List.
   int List::size(){
      return num_elements;
   }

   // position()
   // Returns the position of the cursor in this List. The value returned
   // will be in the range 0 to size().
   int List::position(){
      return pos_cursor;
   }

   // Manipulation procedures -------------------------------------------------

   // moveFront()
   // Moves cursor to position 0 in this List.
   void List::moveFront(){
      beforeCursor=frontDummy;
	  afterCursor=frontDummy->next;
      pos_cursor=0;
   }

   // moveBack()
   // Moves cursor to position size() in this List.
   void List::moveBack(){
	  beforeCursor=backDummy->prev;
      afterCursor=backDummy;
      pos_cursor=size();
   }

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<size()
   int List::peekNext(){
      if(position() < size()){
		 return afterCursor->data;
	  } else{
	     printf("List error: calling peekNext() with invalid position");
		 exit(EXIT_FAILURE);
	  }
   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   int List::peekPrev(){
      if(position()>0){
	     return beforeCursor->data;
	  } else{
	     printf("List error: calling peekPrev() with invalid position");
		 exit(EXIT_FAILURE);
	  }
   }   

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<size() 
   int List::moveNext(){
      if(position() < size()){
	     beforeCursor=afterCursor;
		 afterCursor=afterCursor->next;
		 pos_cursor++;
		 return beforeCursor->data;
	  } else{
	     printf("List error: calling moveNext() with invalid position");
		 exit(EXIT_FAILURE);
	  }
   }

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
   int List::movePrev(){
      if(position()>0){
	     afterCursor=beforeCursor;
		 beforeCursor=beforeCursor->prev;
		 pos_cursor--;
		 return afterCursor->data;
	  } else{
	     printf("List error: calling movePrev() with invalid position");
		 exit(EXIT_FAILURE);
	  }
   }

   // insertAfter()
   // Inserts x after cursor.
   void List::insertAfter(int x){
	   Node* newNode = new Node(x);
	   newNode->prev = beforeCursor;
	   newNode->next = afterCursor;
	   if(size() == 0){
		   frontDummy->next = newNode;
		   backDummy->prev = newNode;
		   beforeCursor = frontDummy;
		   newNode->next = backDummy;
	   } else if(position() == size()){
		   backDummy->prev = newNode;
		   beforeCursor->next = newNode;
	   } else{
		   beforeCursor->next = newNode;
		   afterCursor->prev = newNode;
	   }
	   afterCursor = newNode;
	   num_elements++;
	   /* if(position() == size()){
		   cout<< "1" <<endl;
		   newNode->next = afterCursor;
		   newNode->prev = beforeCursor;	   
	   } else{
		   cout << "2" << endl;
		   newNode->next= afterCursor;
           afterCursor->prev = newNode;
		   newNode->prev = beforeCursor;
		   beforeCursor->next = newNode;	  
	   }
	   afterCursor = newNode;
	   num_elements++;
	    */
   }

   // insertBefore()
   // Inserts x before cursor.
   void List::insertBefore(int x){
       Node* newNode = new Node(x);
	   newNode->prev = beforeCursor;
	   newNode->next = afterCursor;
	   if(size() == 0){
		   frontDummy->next = newNode;
		   backDummy->prev = newNode;
		   afterCursor = backDummy;
	   } else if(position() == 0){
		   frontDummy->next = newNode;
		   afterCursor->prev = newNode;
	   } else{
		    beforeCursor->next = newNode;
		    afterCursor->prev = newNode;
	   }
	   beforeCursor = newNode;
	   pos_cursor++;
	   num_elements++;
	/*    newNode->prev = beforeCursor;
	   newNode->next = afterCursor;
	   cout << "3" << endl;
	   beforeCursor = newNode;
	   pos_cursor++;
	   num_elements++; */
   }
	  /* Node* curr=frontDummy;
	  for(int i=0; i<position(); i++){
	     curr=curr->next;
	  }
	  Node* newNode = new Node(x);
      newNode->next=curr;
	  if(curr->prev==nullptr){
		  newNode->prev=frontDummy;
		  frontDummy->next=newNode;
	  } else{
		  newNode->prev=curr->prev;
		  curr->prev->next=newNode;
	  }
	  curr->prev=newNode;
	  num_elements++; */

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<size()
   void List::eraseAfter(){
      if(position()>=size()){     
	     cerr << "List error: calling eraseAfter with a wrong position" <<endl;
		 exit(EXIT_FAILURE);
	  }
	  Node* N=afterCursor;
	  afterCursor=N->next;
      beforeCursor->next = afterCursor;     
	  afterCursor->prev=beforeCursor;
	  num_elements--;
	  delete N;
   }

   // eraseBefore()()
   // Deletes element before cursor.
   // pre: position()>0
   void List::eraseBefore(){
      if(position()<=0){     
	     cerr << "List error: calling eraseBefore with a wrong position" <<endl;
		 exit(EXIT_FAILURE);
	  }
	  pos_cursor -= 1;
	  Node* N=beforeCursor;
	  beforeCursor=N->prev;
	  afterCursor->prev=beforeCursor;
	  beforeCursor->next=afterCursor;
	  num_elements--;
	  delete N;
   }

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of the element x.
   // If x is found, places the cursor immediately after the found element (so 
   // eraseBefore() would remove the found element), and returns the final 
   // cursor position. If x is not found, places the cursor at position size(),
   // and returns -1. 
   int List::findNext(int x){
	   Node* B=beforeCursor;
	   Node* N=afterCursor;
	   while(N!= backDummy){
		   pos_cursor++;
		   if(N->data==x){
              B=B->next;
		      N=N->next;
			  break;
		   }   
		   B=B->next;
		   N=N->next;
	   }
	   beforeCursor=B;
	   afterCursor=N;
	   if(B->data == x){
		   return pos_cursor;
	   } else{
		   pos_cursor=size();
		   return -1;
	   }
   }

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of the element x.
   // If x is found, places the cursor immediately before the found element (so 
   // eraseAfter() would remove the found element), and returns the final 
   // cursor position. If x is not found, places the cursor at position 0, and 
   // returns -1. 
   int List::findPrev(int x){
	   Node* B=beforeCursor;
	   Node* N=afterCursor;
	   while(B != frontDummy){
		   pos_cursor -=1;
		   if(B->data==x){
			   B=B->prev;
			   N=N->prev;
			   break;
		   }   
		   B=B->prev;
		   N=N->prev;
	   }
	   beforeCursor=B;
	   afterCursor=N;
	   if(N->data == x){
		   return pos_cursor;
	   } else{
		   pos_cursor=0;
		   beforeCursor = frontDummy;
		   afterCursor = frontDummy->next;
		   return -1;
	   }
   }

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique data
   // values. The order of the remaining elements is obtained by retaining
   // the frontmost occurrance of each element, and removing all other 
   // occurances. The cursor is not moved with respect to the retained 
   // elements, i.e. it lies between the same two retained elements that it 
   // did before cleanup() was called.
   void List::cleanup(){
	   int pos = pos_cursor;
	   moveFront();
	   moveNext();
	   Node* N = beforeCursor;
	   while(N->next != backDummy){
		   while(findNext(N->data)!= -1){
			   if(pos_cursor <= pos){
				   pos--;
			   }
			   eraseBefore();
		   }
		   moveFront();
		   N = N->next;
		   findNext(N->data);
	   }
	   pos_cursor = pos; 
   }

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void List::clear(){
      while(size()>0){
	     Node* front=frontDummy->next;
		 frontDummy->next=front->next;
		 num_elements--;
		 delete front;
	  }
	  pos_cursor = 0;
   }

   // concat()
   // Returns a new List consisting of the elements of this List, followed
   // the elements of L. The returned List's cursor will be at its front
   // (position 0).
   List List::concat(const List& L){
	   List newL;
       Node* N;
	   N = frontDummy;
	   N = N->next;
       for(int i = 0; i < size(); i++){
          newL.insertBefore(N->data);
		  N = N->next;
	   }
	   Node* M; 
	   M=L.frontDummy;
	   M = M->next;
	   newL.moveBack();
	    for(int i = 0; i < L.num_elements; i++){
		   newL.insertBefore(M->data);
		   M=M->next;
	   }
	   newL.moveFront();
	   return newL;
   }


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   string List::to_string(){
      Node* N = nullptr;
	  string str = "(";
	  N=frontDummy;  //set N as front node
	 while(N!=nullptr){   //iterate through the list while the node is not null
	     str += std::to_string(N->data);
		 if(N->next!=nullptr){
			str+=", ";
		 }
		 N=N->next;
	  }
	  str+=")";
	  return str;
   }

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool List::equals(const List& R){
      bool equal;
	  equal=(this->num_elements == R.num_elements);
	  Node* N;
	  N=this->frontDummy;
	  Node* M;
	  M=R.frontDummy;
	  while(equal &&  N!=nullptr){
	     equal=(N->data == M->data);
		 N=N->next;
		 M=M->next;
	  }
	  return equal;
   }


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
   std::ostream& operator<<( std::ostream& stream, List& L ){
      return stream << L.List::to_string();
   }

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged are unchanged.
   bool operator==( List& A, const List& B ){
      return A.List::equals(B);
   }

   // operator=()
   // Overwrites the state of this List with state of L.
   List& List::operator=( const List& L ){
	   if(this!=&L){
		   List copy=L;
		   std::swap(frontDummy, copy.frontDummy);
		   std::swap(backDummy, copy.backDummy);
		   std::swap(beforeCursor, copy.beforeCursor);
		   std::swap(afterCursor, copy.afterCursor);
		   std::swap(pos_cursor, copy.pos_cursor);
		   std::swap(num_elements, copy.num_elements);
	   }
	   return *this;
   }
