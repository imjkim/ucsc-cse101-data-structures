//-----------------------------------------------------------------------------
// BigInteger.c
// Juwon Kim, jkim419, pa2
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------
//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "List.h"
#include "BigInteger.h"

//Macro
#define BASE 1000000000
#define POWER 9

// Exported type -------------------------------------------------------------
// BigInteger reference type

typedef struct BigIntegerObj{
   int sign;
   List L;
}BigIntegerObj;
typedef BigIntegerObj* BigInteger;


// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
	BigInteger A=malloc(sizeof(struct BigIntegerObj));
	A->L=newList();
	A->sign=0;
	return(A);
}
// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
    if(pN!=NULL && *pN!=NULL){
	  freeList(&((*pN)->L));
      free(*pN);
      *pN = NULL;
   }
}
// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
	return (N)->sign;
}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
	if(equals(A,B)==1){						//equal
		return 0;
	} else{									//they are not equal
		if(sign(A)!=sign(B)){				//they have different signs
			if(sign(A)>sign(B)){
				return 1;
			} else{
				return -1;
			}
		} else{								//same sign
			if(sign(A)==1){
				if(length(A->L)==length(B->L)){
					moveFront(A->L);
					moveFront(B->L);
					while(index(A->L)!=-1){
						if(get(A->L)>get(B->L)){
							return 1;
						} else if(get(A->L)<get(B->L)){
							return -1;
						}
						moveNext(A->L);
						moveNext(B->L);
					}
				} else{
					if(length(A->L)>length(B->L)){
						return 1;
					} else{
						return -1;
					}
				}
			} else{
				if(length(A->L)==length(B->L)){
					moveFront(A->L);
					moveFront(B->L);
					while(index(A->L)!=-1){
						if(get(A->L)>get(B->L)){
							return -1;
						} else if(get(A->L)<get(B->L)){
							return 1;
						}
						moveNext(A->L);
						moveNext(B->L);
					}
				} else{
					if(length(A->L)>length(B->L)){
						return -1;
					} else{
						return 1;
					}
				}
			}
		}
	}		
	return 0;
}
// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
	int eq;
	long a;
	long b;
	eq=1;
	if(sign(A)==sign(B)){					//I took the approach of setting eq to 1 only if its equal
		if(length(A->L)==length(B->L)){
			moveFront(A->L);
			moveFront(B->L);
			for(int i=0; i<length(A->L); i++){
				a=get(A->L);
				b=get(B->L);
				if(a!=b){
					eq=0;
					break;
				}
				moveNext(A->L);
				moveNext(B->L);
			}
		} else{
			eq=0;
		}
	} else{
		eq=0;
	}
	return eq;
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
	clear(N->L);
	N->sign=0;
}
// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
	if(sign(N)==1){
		N->sign=-1;
	} else if(sign(N)==-1){
		N->sign=1;
	}
}
// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
	char str[POWER];
	long temp;
	int address;
	int digit;
	int len;
	len=strlen(s);
	
	//fprintf(stdout, "len= %d  ", len);
	BigInteger A=newBigInteger();
	if(s[0]==45){							// '-' ascii value
		A->sign=-1;							//just setting signs
	} else{
		A->sign=1;
	}
	if(s[0]==45 || s[0]==43){				//if the first digit is a sign, we gotta account for that
		s++;								//discard the first ch
		len-=1;
	}
	address= len % POWER;   				//modulus of power
	for(int i =0; i<POWER; i++){
		str[i]='\0';
	}
	if(address != 0){						//uneven
	   strncpy(str, s, address);
	   temp=atol(str);						//convert to long
	   append(A->L, temp);
	   s=s+address;  							//this is virtually getting rid of first few digits of s
	   len=len-address;
	}
	digit=len/POWER;
	for(int i=0; i<digit; i++){
		strncpy(str, s, POWER);
		temp=atol(str);
		append(A->L, temp);
		s+=POWER;							//again, get rid of characters we used
	}
	return (A);
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
	if((N==NULL)||(N->L==NULL)){
		printf("BigInteger Error: Cannot call copy() with null BigInteger reference");
		exit(EXIT_FAILURE);
	} 
	BigInteger A=newBigInteger();
	clear(A->L);
	if(length(N->L)!=0){
		moveFront(N->L);
		while(index(N->L)!=-1){
			append(A->L, get(N->L));
			moveNext(N->L);
		}
	}
	A->sign=N->sign;
	return (A);
}
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
	long n;
	long a, b, c;
	c=0;
	clear(S->L);
	moveBack(A->L);
	moveBack(B->L);
	if(sign(A)==sign(B)){
		while((index(A->L)!=-1)&&(index(B->L)!=-1)){
			a=get(A->L);
			b=get(B->L);
	        n = a + b + c;
			if(n >= BASE){
			   n -= BASE;
			   c = 1;
			} else{
			   c = 0;
			}
			prepend(S->L, n);
			movePrev(A->L);
			movePrev(B->L);
		}
		while(index(A->L)!=-1){				//this is when List A has more digits than B's
			a=get(A->L);
			n = a + c;
			if(n >= BASE){
			   n -= BASE;
			   c = 1;
			} else{
			   c = 0;
			}
			prepend(S->L, n);				//just keep adding the remainder of A list
			movePrev(A->L);
		}
		while(index(B->L)!=-1){				//vice versa
			b=get(B->L);
			n = b + c;
			if(n >= BASE){
			   n -= BASE;
			   c = 1;
			} else{
			   c = 0;
			}
			prepend(S->L, n);
			movePrev(B->L);
		}
		if(c!=0){						//add the carry(1) to head
			prepend(S->L, c);
		} 
		S->sign=sign(A);
	} else if((sign(A)==1)&&(sign(B)==-1)){
		if(equal((A->L),(B->L))){
			S->sign=0;
			prepend(S->L, 0);
		} else{
			B->sign=1;
			if(compare(A,B)==-1){
				moveBack(A->L);
				moveBack(B->L);
				while((index(A->L)!=-1)&&(index(B->L)!=-1)){
					a=get(A->L);
					b=get(B->L);
					if(b+c<a){
						b+=BASE;
						n=(b-a+c)%BASE;
						c=-1;
					} else{
						c=0;
						n=(b-a)%BASE;
					}
					prepend(S->L, n);
					movePrev(A->L);
					movePrev(B->L);
				}
				S->sign=-1;
			} else{
				moveBack(A->L);
				moveBack(B->L);
				while((index(A->L)!=-1)&&(index(B->L)!=-1)){
					a=get(A->L);
					b=get(B->L);
					if(a+c<b){
						a+=BASE;
						n=(a-b+c)%BASE;
						c=-1;
					} else{
						c=0;
						n=(a-b)%BASE;
					}
					prepend(S->L, n);
					movePrev(A->L);
					movePrev(B->L);
				}
				S->sign=1;
			}
			B->sign=-1;
			
		}	
   } else if((sign(A) == -1)&&(sign(B) == 1)){
      if(equal((A->L),(B->L))){
         S->sign = 0;
         prepend(S->L, 0);
      } else{
         A->sign = 1;
         if(compare(A,B) == 1){
            moveBack(A->L);
            moveBack(B->L);
            while((index(A->L) != -1) && (index(B->L) != -1)){
               a = get(A->L);
               b = get(B->L);
               if(a - c < b){
                  n = (a - c + BASE) - b;
                  c = 1;				  
               } else{
                  n = (a - c - b);
                  c = 0;
               }
               prepend(S->L, n);
               movePrev(A->L);
               movePrev(B->L);
             }
             S->sign=-1;
			} else{
				moveBack(A->L);
				moveBack(B->L);
				while((index(A->L)!=-1)&&(index(B->L)!=-1)){
					a=get(A->L);
					b=get(B->L);
					if(b+c<a){
						b+=BASE;
						n=(b-a+c)%BASE;
						c=-1;
					} else{
						n=(b-a+c)%BASE;
						c=0;
					}
					prepend(S->L, n);
					movePrev(A->L);
					movePrev(B->L);
				}
				S->sign=1;
			}
			A->sign=-1;		
		}	
	} 
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
	BigInteger S=newBigInteger();
	add(S, A, B);
	return S;
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
   long n, a, b, c;
   c = 0;
   clear(D->L);
   moveBack(A->L);
   moveBack(B->L);
   if(sign(A) == 1 && sign(B) == 1){						//case 1
      if(compare(A, B) == 0){								//subtracting same thing
         D->sign = 0;
         clear(D->L);
         append(D->L, 0);
      } else{
         if(compare(A, B) == -1){						//pos-pos<0
            moveBack(A->L);
            moveBack(B->L);
            while((index(A->L )!= -1)&&(index(B->L) != -1)){
               a = get(A->L);
               b = get(B->L);
               if(b+c < a){
                  b+=BASE;
                  n=(b-a+c)%BASE;
                  c=-1;
               } else{
                  c=0;
                  n=(b-a)%BASE;
               }
                  prepend(D->L, n);
                  movePrev(A->L);
                  movePrev(B->L);
               }
            D->sign=-1;
            while(index(B->L) != -1){
               b = get(B->L);
               if(c == 1){
                  n = b + c;
				  if(n != 0){
                     prepend(D->L, n);
                  }
               } else{
                  prepend(D->L, a);
			   } 
			   movePrev(A->L);
            } 
            D->sign = -1;	
            } else{										//pos-pos>0
               moveBack(A->L);
               moveBack(B->L);
               while((index(A->L)!=-1)&&(index(B->L)!=-1)){
                  a = get(A->L);
                  b = get(B->L);
               if(a-c < b){
                   n = (a-c-b) + BASE;
                   c = -1;
               } else{
                   n = (a-c-b);
                   c = 0;
               }
               prepend(D->L, n);
               movePrev(A->L);
               movePrev(B->L);
               }
               while(index(A->L) != -1){
                  a = get(A->L);
                  if(c == 1){
                     n = a - c;
				     if(n != 0){
                        prepend(D->L, n);
                     }
                  } else{
                     prepend(D->L, a);
			      } 
			      movePrev(A->L);
               }
               D->sign = 1;	
			}
		}
	} else if(sign(A)==1 && sign(B)==-1){				//case 2	
		moveBack(A->L);
		moveBack(B->L);
		while((index(A->L)!=-1)&&(index(B->L)!=-1)){
			a=get(A->L);
			b=get(B->L);
			n=(a+b+c)%BASE;
			prepend(D->L, n);
			c=(a+b+c)/BASE;
			movePrev(A->L);
			movePrev(B->L);
		}
		D->sign=1;
	} else if(sign(A)==-1 && sign(B)==1){				//case 3
		moveBack(A->L);
		moveBack(B->L);
		while((index(A->L)!=-1)&&(index(B->L)!=-1)){
			a=get(A->L);
			b=get(B->L);
			n = a + b + c;
			if(n > BASE){
			   n -= BASE;
			   c = 1;
			} else{
			   c = 0;
			}
			prepend(D->L, n);
			movePrev(A->L);
			movePrev(B->L);
		}
		while(index(A->L)!=-1){				//this is when List A has more digits than B's
			a = get(A->L);
			n = a + c;
			if(n > BASE){
			   n -= BASE;
			   c = 1;
			} else{
			   c = 0;
			}
			prepend(D->L, n);				//just keep adding the remainder of A list
			movePrev(A->L);
		}
		while(index(B->L) != -1){				//vice versa
			b = get(B->L);
			n = b + c;
			if(n > BASE){
			   n -= BASE;
			   c = 1;
			} else{
			   c = 0;
			}
			prepend(D->L, n);				//just keep adding the remainder of A list
			movePrev(B->L);
		}
		if(c > 0){
           prepend(D->L, c);
		   c = 0;
		}
		D->sign=-1;
	} else if(sign(A)==-1 && sign(B)==-1){				//case 4
		if(equal((A->L),(B->L))==1){
			D->sign=0;
			prepend(D->L, 0);
		}  else{
			if(compare(A,B)==-1){						
				moveBack(A->L);
				moveBack(B->L);
				while((index(A->L)!=-1)&&(index(B->L)!=-1)){
					a=get(A->L);
					b=get(B->L);
					if(a+c<b){
						a+=BASE;
						n=(a-b+c)%BASE;
						c=-1;
					} else{
						c=0;
						n=(a-b)%BASE;
					}
					prepend(D->L, n);
					movePrev(A->L);
					movePrev(B->L);
				}
				D->sign=-1;
				
			} else{										//pos-pos>0
				moveBack(A->L);
				moveBack(B->L);
				while((index(A->L)!=-1)&&(index(B->L)!=-1)){
					a=get(A->L);
					b=get(B->L);
					if(b+c<a){
						b+=BASE;
						n=(b-a+c)%BASE;
						c=-1;
					} else{
						c=0;
						n=(b-a)%BASE;
					}
					prepend(D->L, n);
					movePrev(A->L);
					movePrev(B->L);
				}
				D->sign=1;
			}
		}
	}
	
}
// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
	BigInteger S=newBigInteger();
	subtract(S,A,B);
	return S;
}
// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
    long carry, a, b, p;
   int count, ten;
   moveBack(A->L);
   clear(P->L);
   ten = 1;
   P->sign = 1;
   BigInteger S;
   S = newBigInteger();
   S->sign = 1;
   carry = 0;
   prepend(P->L, 0);
   while(index(A->L)!=-1){
	  a = get(A->L);
	  moveBack(B->L);
	  for(count = 1; count < ten; count++){
		 prepend(S->L, 0);
	  }
	  while(index(B->L)!=-1){
		 b = get(B->L);
		 p = a * b + carry;
		 if(p >= BASE){
			carry = p / BASE;
			p = p % BASE;
		 } else{
			 carry = 0;
		 }
		 prepend(S->L, p);
		 movePrev(B->L);
	  }
	  if(carry > 0){
		 prepend(S->L, carry);
		 carry = 0;
	  }
	  BigInteger PL = copy(P);
	     add(P, PL,S);
		 freeBigInteger(&PL);
	  clear(S->L);
	  ten++; 
	  
	  movePrev(A->L);
   }
   freeBigInteger(&S);
   if(sign(A) != sign(B)){
      P->sign = -1;
   }
   if((sign(B) == 0)||(sign(A)==0)){
      P->sign = 0;
   }
  /*  int len = length(A->L) + length(B->L);
   long pro[len];
   int i, j;
   long carry, a, b, d;
   moveBack(A->L);
   moveBack(B->L);
   clear(P->L);
   while(index(A->L) >= 0){
      carry = 0;
	  j = 0;
      a = get(A->L);
      while(index(B->L) >= 0){
         b = get(B->L);
         d = pro[i+j];
         d += (a * b) + carry;
		 pro[i+j] = (d % BASE);
		 carry = (d / BASE);
		 movePrev(B->L);
		 j++;
	  }
	  pro[i + length(B->L)] = carry;
	  movePrev(A->L);
	  i++;
   }
   for(int k = 0; k < len; k++){
      if((pro[k] != 0) || (k != (len - 1))){
         prepend(P->L, pro[k]);
	  }
   } 
   if(sign(A) == sign(B)){
      P->sign = 1;
   } else{
	  P->sign = -1;
   } */
	/* long a,b,c;
	long n;
	long pro;
	long bas;
	long t;
	long total;
	int top;
	int bot;
	long pow;
	c=0;
   clear(P->L);
   moveBack(A->L);
		moveBack(B->L);
		while(index(B->L)!=-1){
			b=get(B->L);
			while(index(A->L)!=-1){
				bot=length(A->L)-index(A->L);
                if(bot>=0){
					pow = 1;
				} for(int x=0; x < bot; x++){
					pow*=10;
				}
				bot = 0;
				a=get(A->L);
				n=(a*b)+c;
				if(n>=BASE){
					c=n/BASE;
					n=n%BASE;
					n=n*pow;
					pro+=n;
				} else{
					n=n*pow;
					pro+=n;
					c=0;
				}
				bas+=pro;
				pro=0;
				movePrev(A->L);
			}
			top=length(B->L)-index(B->L);
			if(top>=0){
					pow = 1;
				} for(int x=0; x < top; x++){
					pow*=10;
				}
				top = 0;
			total += bas*pow;
			movePrev(B->L);
   }
   t=total%BASE;
   while(t>0){
      t=total%BASE;
      prepend(P->L, t);
      t/=BASE;
   }
   if(sign(A)==sign(B)){
	   P->sign = 1;
   } else{
	   P->sign = -1;
   } */
}
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
	BigInteger S=newBigInteger();
	multiply(S, A,B);
	return S;
}
// Other operations -----------------------------------------------------------
// printBigInteger()./
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
	if(sign(N)==-1){
		fprintf(out, "%c", 45);						//print - sign
	} 
	moveFront(N->L);
	int zero;
	printList(stdout, N->L);
	while(index(N->L)!=-1){
		/*  if((index(N->L)==length(N->L)-1)&&(index(N->L)!=0)){
			fprintf(out, "%09ld", get(N->L));
		} else{
			fprintf(out, "%ld", get(N->L));
		} */
		if(index(N->L)==0){
			if(get(N->L)!=0){
				fprintf(out,"%ld", get(N->L));
			} else if(length(N->L)==1){
				fprintf(out,"0");
			} else{
				zero = 1;
			}
		} else{
			if(zero == 1){
				fprintf(out,"%ld", get(N->L));
				zero = 0;
			} else{
			   fprintf(out,"%09ld", get(N->L));
			}
		}
		moveNext(N->L);
	}
	fprintf(out, "\n\n");
}