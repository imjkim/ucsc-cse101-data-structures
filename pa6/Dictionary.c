//-----------------------------------------------------------------------------
// Dictionary.c
// Juwon Kim, jkim419, pa5
// Implementation file for Dictionary ADT 
//-----------------------------------------------------------------------------
//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Dictionary.h"

// Exported type --------------------------------------------------------------
typedef struct NodeObj{
	KEY_TYPE key;
    VAL_TYPE value;
	struct NodeObj* left;
	struct NodeObj* right;
	struct NodeObj* parent;
} NodeObj;
typedef struct NodeObj* Node;

typedef struct DictionaryObj{
   int unique;
   Node root;
   Node current;
   int size;
} DictionaryObj;
typedef struct DictionaryObj* Dictionary;

Node newNode(KEY_TYPE k, VAL_TYPE v){
   Node N = (NodeObj*) malloc(1*sizeof(NodeObj));
   N->key=k;
   N->value=v;
   N->left=NULL;
   N->right=NULL;
   return N;
}
// freeNode()
// Destructor for private Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
void freeAllNodes(Node* N){    //this function takes in a root node and frees the entire tree
   if((*N)->left !=NULL){
	   freeAllNodes(&((*N)->left));
   }
   if((*N)->right!=NULL){
	   freeAllNodes(&((*N)->right));
   }
   free(*N);
}
// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique){
	Dictionary D= (DictionaryObj*)malloc(1*sizeof(DictionaryObj));
    D->root=NULL;
	D->unique = unique;
    D->size=0;
    return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
	 if(pD!=NULL && *pD!=NULL){
        Node head=(*pD)->root;
		if(head != NULL){
			freeAllNodes(&head);
		}
		free(*pD);
		*pD = NULL;
   }
}


// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
	if(D==NULL){ 
		printf("Dictionary Error: calling size() on null Dictionary reference ");
		exit(EXIT_FAILURE);
	} else{
		return D->size;
	}
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
	if(D==NULL){
		printf("Dictionary Error: calling size() on null Dictionary reference ");
		exit(EXIT_FAILURE);
	} else{
		return D->unique;
	}
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
	if(D==NULL){
      fprintf(stderr, "Dictionary Error: lookup() called on NULL Dictionary reference");
	  exit(EXIT_FAILURE);
   } else {
	  Node current=D->root;
	  if(current ==NULL){
		  return VAL_UNDEF;
	  }
	  while((current!=NULL)&&(KEY_CMP(current->key,k)!=0)){
		  if(KEY_CMP(current->key, k)<0){	//current key is less than k
			  current=current->right;
		  } else{
			  current=current->left;
		  }
	  }
	  if(current!=NULL){
		  return current->value;
	  } else{
	      return VAL_UNDEF;
	  }
   }  
}

// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
	if (getUnique(D)==1 && lookup(D, k)!= VAL_UNDEF){
        printf("Dictionary Error: unique insert does not allow duplicated keys");
        exit(EXIT_FAILURE);
    }
	if(size(D) == 0){
		D->root = newNode(k,v);
	} else{
       Node current = D->root;
	   Node prev = NULL;
       while(current != NULL){
           prev = current;
           if(KEY_CMP(current->key, k)<= 0){
              current = current->right;
           }else{
              current = current->left;
           }
       }
       Node new = newNode(k,v);
	   new->parent = prev;
       if(KEY_CMP(k, prev->key)< 0){
          prev->left = new;
       } else{
          prev->right = new;
       }
	}
	D->size++;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
    if(D==NULL){
		fprintf(stderr, "Dictionary Error: delete() called on NULL Dictionary reference\n");
	  exit(EXIT_FAILURE);
	} else if(lookup(D,k) == VAL_UNDEF){
		printf("Dictionary Error: delete() called with an invalid key");
		exit(EXIT_FAILURE);
	}
	Node point;
	point=D->root;
	Node parent;
	parent=NULL;
	Node new;
    /* while(point!=NULL){
		if(KEY_CMP(point->key,k)==0){
			break;
		}
		parent=point;
		if(KEY_CMP(point->key,k)<=0){
			point = point->right;
		} else{
			point = point->left;
		}
	}
	printf(KEY_FORMAT, point->key);
	if((point->left == NULL) && (point->right == NULL)){
	   freeNode(&point);
	} else if(point->left == NULL){
	   if(point == parent->left){
		   new = point->right;
		   parent->left = new;
		   new->parent = parent;
		   freeNode(&point);
	   } else if(point == parent->right){
		   new = point->right;
		   parent->right = new;
		   new->parent = parent;
		   freeNode(&point);
	   } else{
		  D->root = point->right;
		  freeNode(&point);
	   }
	} */
	while(point!=NULL){
		
		if(KEY_CMP(point->key,k)==0){
			break;
		}
		parent=point;
		if(KEY_CMP(point->key,k)<=0){
			point = point->right;
		} else{
			point = point->left;
		}

	}
	new=point;
	if(point->left!=NULL && point->right!=NULL){	//has two children
		Node left=point->left;
		while(left->right!=NULL){
			left=left->right;
		}
		left->right=point->right;
		new= point->left;
	} else if(point->left==NULL){					//have right child
		new=point->right;
	} else{											//have left child
		new=point->left;
	}
	if(point==D->root){
		D->root=new;
	} else{
		if(parent->left==point){
			parent->left=new;
		} else{
			parent->right=new;
		}
	}
	if(D->current == point){
		D->current = NULL;
	}
	D->size--;
}
// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void empty(Node* N){
	if((*N)->left != NULL){
		empty(&((*N)->left));
	}
	if((*N)->right != NULL){
		empty(&((*N)->right));
	}
	free(*N);
	*N=NULL;
}
void makeEmpty(Dictionary D){
	Node current=D->root;
	if(current!=NULL){
		empty(&current);
	}
	D->current=NULL;
	D->size=0;
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D){
	if(D->root==NULL){
		return VAL_UNDEF;
	}
	Node current = D->root;
	while(current->left != NULL){
		current = current->left;
	}
	D->current = current;
	return currentVal(D);
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
	Node current =D->root;
	if(current == NULL){
		return VAL_UNDEF;
	}
	while(current != NULL && current->right != NULL){
		current = current->right;
	}
	D->current = current;
	return currentVal(D);

}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
	if(D->current==NULL){
		return KEY_UNDEF;
	} else{
		return D->current->key;
	}
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
	if(D->current==NULL){
		return VAL_UNDEF;
	} else{
		return D->current->value;
	}
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D){
	if(D->current==NULL){
		return VAL_UNDEF;
	} 
	Node current = D->current;
	if(current->right != NULL){
		current = current->right;
		while(current->left != NULL){
			current = current->left;
		}
		D->current = current;
		return currentVal(D);
	} else{
		Node parent = current->parent;
		if(KEY_CMP(current->key, parent->key) < 0){
			D->current = current->parent;
			return currentVal(D);
		} else{
			if(parent != D->root){
			   while(parent->parent != NULL){
				   parent = parent->parent;
				   if(KEY_CMP(current->key, parent->key) < 0){
			          D->current = parent;
			          return currentVal(D);
		           }
			   }
			}
		}
	}
	/* Node current = D->current;
	if(current->right != NULL){
	   D->current= current->right;
	  return currentVal(D);
	} else if(current->parent != NULL){
	   if(KEY_CMP(current->key, current->parent->key) < 0){
	      D->current= current->parent;
	      return currentVal(D);
	   } else{
		  Node parent = current->parent;
		  while(parent->parent != NULL){
			 if(KEY_CMP(current->key, parent->parent->key) < 0){
				D->current = parent->parent;
				break;
			 }
			 parent = parent->parent;
		  }
	   }
	} */
	D->current = NULL;
	return VAL_UNDEF;

}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D){
	if(D->current==NULL){
		return VAL_UNDEF;
	}
	Node current = D->current;
	if(current->left != NULL){
	   D->current= current->left;
	  return currentVal(D);
	} else if(current->parent != NULL){
	   if(KEY_CMP(current->key, current->parent->key) >= 0){
	      D->current= current->parent;
	      return currentVal(D);
	   }
	}
	D->current = NULL;
	return VAL_UNDEF;

}



// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
    for(beginForward(D); currentVal(D)!=VAL_UNDEF; next(D)){
      fprintf(out, KEY_FORMAT, currentKey(D));
    }
}
