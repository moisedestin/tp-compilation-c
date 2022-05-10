#include <stdio.h>
#include <stdlib.h>
#include "AST.h"
#include <string.h>

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char* car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->car=car;
    t->left=left;
    t->right=right;
    t->boo = NULL;

  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char* car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(char* val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val= val; 
    t->boo=NULL;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}
 

AST newLeafASTForBoolAndNan(char* val){
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */

    if(!strcmp(val,"True"))
      t->boo="True";
    else if(!strcmp(val,"False"))
      t->boo="False";
    else
    	t->boo="NaN";

    t->car=NULL;
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
    if (t->left==NULL) printf(":%s: ",t->val); else printf(":%s: ",t->car);
    printAST(t->right);
    printf("] ");
  }
}



