#include <stdio.h>
#include <stdlib.h>
#include "AST.h"
#include <string.h>

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->car=car;
    t->left=left;
    t->right=right;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(int val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val=val;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

/* delete an AST */
void freeAST(AST t)
{
  if (t!=NULL) {
    freeAST(t->left);
    freeAST(t->right);
    free(t);
  }
}

/* infix print an AST*/
void printAST(AST t)
{
  if (t!=NULL) {
    printf("[ ");
    printAST(t->left);
    /* check if node is car|val */
    if (t->left==NULL) printf(":%d: ",t->val); else printf(":%c: ",t->car);
    printAST(t->right);
    printf("] ");
  }
}


/* infix print an AST*/
int displayValueAst(AST t)
{
  int result = 0; 
  // int right = 0;
  if (t!=NULL) {
    if (t->left==NULL){
      return t->val; 
    }  
    else if(strcmp(&t->car, "M") == 0){
      return - displayValueAst(t->left);
    }
    else {
       int farleft = displayValueAst(t->left);
       int farright = displayValueAst(t->right); 
                  //  printf(&t->car);
 
      switch (t->car)
     {
         case '+':
            result = farleft + farright;
            break;
         case '-':
            result = farleft - farright;;
            break;
         case '*':
            result = farleft * farright;
            break;  
    }
      

    }
  } 

 
  return result;
}

