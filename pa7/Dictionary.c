//-----------------------------------------------------------------------------
// Dictionary.c
// Juwon Kim, jkim419, pa7
// Implementation file for Dictionary ADT 
//-----------------------------------------------------------------------------
//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

#define COL_TYPE int
#define MAX_LENGTH 255
#define RED 0
#define BLACK 1

// Exported type --------------------------------------------------------------
struct NodeObj{
	KEY_TYPE key;
    VAL_TYPE value;
	COL_TYPE color;
	struct NodeObj* left;
	struct NodeObj* right;
	struct NodeObj* parent;
};
typedef struct NodeObj* Node;

struct DictionaryObj{
   int unique;
   Node root;
   Node current;
   Node nil;
   int size;
};

Node newNode(KEY_TYPE k, VAL_TYPE v){
   Node N = malloc(1*sizeof(struct NodeObj));
   N->key=malloc(MAX_LENGTH * sizeof(KEY_TYPE));
   strcpy(N->key, k);
   N->value=v;
   N->left=NULL;
   N->right=NULL;
   N->parent=NULL;
   N->color=RED;
   return N;
}
// freeNode()
// Destructor for private Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
   }
}
void freeAllNodes(Dictionary D, Node N){    //this function takes in a root node and frees the entire tree
   if((N)->left != D->nil){
	   freeAllNodes(D, N->left);
   }
   if((N)->right!=D->nil){
	   freeAllNodes(D, N->right);
   }
   free(N->key);
   free(N);
}
// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique){
	Dictionary D= malloc(1*sizeof(struct DictionaryObj));
	D->nil=newNode("-1", VAL_UNDEF);
	D->nil->color=BLACK;
	D->unique=unique;
	D->root=D->nil;
	D->current=D->nil;
    D->size=0;
    return D;
}
Node findNode(Dictionary D, KEY_TYPE k);
Node minimum(Dictionary D, Node x);
Node maximum(Dictionary D, Node x);
void deleteFixUp(Dictionary D, Node x);
void insertFixUp(Dictionary D, Node x);
void rotateLeft(Dictionary D, Node x);
void rotateRight(Dictionary D, Node x);
void printPreOrder(FILE* out, Dictionary D, Node x);
void printInOrder(FILE* out,Dictionary D, Node x);
void printPostOrder(FILE* out, Dictionary D, Node x);
// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
	 if(pD!=NULL && *pD!=NULL){
        Node head=(*pD)->root;
		if(head!=(*pD)->nil){	
			freeAllNodes((*pD), head);				//frees current node
		}
		free((*pD)->nil->key);	
		free((*pD)->nil);
		free(*pD);
		(*pD) = NULL;
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
void rotateLeft(Dictionary D, Node x){
	Node y;
	y=x->right;
	x->right=y->left;
	if(y->left!=D->nil){
		y->left->parent=x;
	}
	y->parent = x->parent;
	if(x->parent==D->nil){
		D->root=y;
	} else if(x==x->parent->left){
		x->parent->left=y;
	} else{
		x->parent->right=y;
	}
	y->left=x;
	x->parent=y;
}
void rotateRight(Dictionary D, Node x){
	Node y;
	y=x->left;
	x->left=y->right;
	if(y->right != D->nil){
		y->right->parent=x;
	}
	y->parent=x->parent;
	if(x->parent== D->nil){
		D->root=y;
	} else if(x==x->parent->right){
		x->parent->right=y;
	}else{
		x->parent->left=y;
	}
	y->right=x;
	x->parent=y;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
	Node current=D->root;
	while(current!=D->nil){
		if(KEY_CMP(k,current->key)==0){
		   return current->value;
	    } else if(KEY_CMP(k,current->key)<0){
			current=current->left;
		} else{
			current=current->right;
		}
	}
	return VAL_UNDEF;
}

Node findNode(Dictionary D, KEY_TYPE k){
	Node n=D->root;
	while(n!=NULL){
		if(KEY_CMP(k, n->key)==0){
		   return n;
	    } else if(KEY_CMP(k, n->key)<0){
			n=n->left;
		} else{
			n=n->right;
		}
	}
	return n;
}

// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
	Node y=D->nil;
	Node x=D->root;
	if((getUnique(D)==1)&&(lookup(D, k) != VAL_UNDEF)){
		printf("Dictionary Error: insert called with duplicate keys on unique Dictionary");
		exit(EXIT_FAILURE);
	}
	Node z=newNode(k,v);
	while(x!=D->nil){
		y=x;
		if(KEY_CMP(k, x->key)<0){
			x=x->left;
		} else{
			x=x->right;
		}
	}
	z->parent=y;
	if(y==D->nil){
		D->root=z;
	} else if(KEY_CMP(k, y->key)<0){
		y->left=z;
		z->parent=y;
	} else{
		y->right=z;
		z->parent=y;
	}
	z->left=D->nil;
	z->right=D->nil;
	z->color=RED;
	insertFixUp(D, z);
	D->size++;
} 


//insertFixUp()
void insertFixUp(Dictionary D, Node z){
	Node y;
	while(z->parent->color == RED){
		if(z->parent == z->parent->parent->left){		//parent of z is a left child
			y=z->parent->parent->right;
			if(y->color==RED){
				z->parent->color=BLACK;
				y->color = BLACK;
				z->parent->parent->color= RED;
				z=z->parent->parent;
			} else{
				if(z==z->parent->right){				//z is a right child
					z=z->parent;
					rotateLeft(D,z);
				}
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				rotateRight(D, z->parent->parent);
			}
		} else{											//parent of z is a right child
			y=z->parent->parent->left;
			if(y->color==RED){
				z->parent->color=BLACK;
				y->color=BLACK;
				z->parent->parent->color=RED;
				z=z->parent->parent;
			} else{
				if(z==z->parent->left){					//z is a left child
					z=z->parent;
					rotateRight(D,z);
				}
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				rotateLeft(D,z->parent->parent);
			}
		}
	}
	D->root->color=BLACK;
}

void transplant(Dictionary D, Node u, Node v){
	if(u->parent==D->nil){
		D->root=v;
	} else if(u == u->parent->left){
		u->parent->left=v;
		v->parent= u->parent;
	} else{
		u->parent->right=v;
		v->parent= u->parent;
	}
}
// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
	if(lookup(D,k)!=VAL_UNDEF){
		Node z=findNode(D,k);
		if(z==D->current){
			D->current=D->nil;
		}
		Node y=z;
		Node x;
		int color=y->color;
		if(z->left == D->nil){
			x=z->right;
			transplant(D, z, z->right);
		} else if(z->right == D->nil){
			x=z->left;
			transplant(D, z, z->left);
		} else{
			y= minimum(D, z->right);
			color=y->color;
			x=y->right;
			if(y->parent==z){
				x->parent =y;
			} else{
				transplant(D, y, y->right);
				y->right = z->right;
				y->right->parent=y;
			}
			transplant(D,z,y);
			y->left=z->left;
			y->left->parent=y;
			y->color=z->color;
		}
		if(color == BLACK){
			deleteFixUp(D, x);
		}
		free(z->key);
		free(z);
		D->size--;
	} else{
		printf("Dictionary error: calling delete with wrong key");
		exit(EXIT_FAILURE);
	}
}
Node minimum(Dictionary D, Node x){
	Node y=x;
	while(y->left != D->nil){
		y=y->left;
	} 
	return y;
}
Node maximum(Dictionary D, Node x){
	Node y=x;
	while(y->right != D->nil){
		y=y->right;
	} 
	return y;
}
void deleteFixUp(Dictionary D, Node x){
	Node w;
	while(x!=D->root && x->color == BLACK){
		if(x==x->parent->left){
			w=x->parent->right;
			if(w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				rotateLeft(D, x->parent);
				w=x->parent->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = x->parent;
			} else{
				if(w->right->color == BLACK){
					w->left->color=BLACK;
					w->color=RED;
					rotateRight(D, w);
					w=x->parent->right;
				}
				w->color=x->parent->color;
				x->parent->color=BLACK;
				w->right->color= BLACK;
				rotateLeft(D, x->parent);
				x=D->root;
			}
		} else{
			w=x->parent->left;
			if(w->color == RED){
			} 
			if(w->right->color == BLACK && w->left->color == BLACK){
				w->color = RED;
				x=x->parent;
			} else{
				if(w->left->color == BLACK){
					w->right->color = BLACK;
					w->color = RED;
					rotateLeft(D, w);
					w=x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rotateRight(D, x->parent);
				x= D->root;
			}
		}
	}
	x->color=BLACK;
}
// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
	Node r=D->root;
	if(r!=D->nil){
		freeAllNodes(D, r);
	}
	D->current=D->nil;
	D->root=D->nil;
	D->size=0;
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D){
	if(D==NULL){
		return VAL_UNDEF;
    }
    if(D->root== D->nil){
        return VAL_UNDEF;
    }
    D->current = minimum(D, D->root);
	return currentVal(D); 
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
	Node root=D->root;
	if(root==D->nil){
		return VAL_UNDEF;
		
	}
	D->current=maximum(D,root);
	return currentVal(D); 
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
	if(D->current==D->nil){
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
	if(D->current==D->nil){
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
	Node current=D->current;
	if(current->right != D->nil){
		current=minimum(D,current->right);
		D->current=current;
		return currentVal(D);
	} 
	Node parent=current->parent;
	while((parent!=D->nil) && (current==parent->right)){
		current=parent;
		parent=parent->parent;
	}
	D->current=parent;
	return currentVal(D);
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D){
	Node current=D->current;
	if(current->left != D->nil){
		current=maximum(D,current->left);
		D->current=current;
		return currentVal(D);
	} 
	Node parent=current->parent;
	while((parent!=D->nil) && (current==parent->left)){
		current=parent;
		parent=parent->parent;
	}
	D->current=parent;
	return currentVal(D);
}

void printPreOrder(FILE* out,Dictionary D, Node x){
	fprintf(out, KEY_FORMAT "\n",x->key);
	if(x->left!=D->nil){
	   printPreOrder(out,D, x->left);
	}
	if(x->right!=D->nil){
	   printPreOrder(out,D, x->right);
	}
}
void printInOrder(FILE* out,Dictionary D,Node x){
	if(x->left!=D->nil){
	   printInOrder(out,D, x->left);
	}
	fprintf(out, KEY_FORMAT "\n", x->key);
	if(x->right!=D->nil){
	   printInOrder(out, D,x->right);
	}
}
void printPostOrder(FILE* out, Dictionary D, Node x){
	if(x->left!=D->nil){
	   printPostOrder(out,D, x->left);
	} 
	if(x->right!=D->nil){
	   printPostOrder(out, D,x->right);
	}
	fprintf(out, KEY_FORMAT "\n", x->key);
}
// Other operations -----------------------------------------------------------

// printDictionary()
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printDictionary(FILE* out, Dictionary D, const char* ord){
	Node root=D->root;
	if(strcmp(ord, "pre")==0){
		printPreOrder(out,D, root);
	} else if(strcmp(ord, "post")==0){
		printPostOrder(out, D, root);
	} else if(strcmp(ord, "in")==0){
		printInOrder(out, D, root);
	}
} 

