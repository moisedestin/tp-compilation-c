#include <stdio.h>
#include <stdlib.h>
#include "AST.h"

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

void affichageCode(AST t)
{	
  if(t->left == NULL) {
    printf("CsteNb %d \n",t->val); 
  }  
  else {
 
      affichageCode(t->left); 
      if(t->right != NULL)
        affichageCode(t->right);

    
     switch(t->car){
          case '+' :
            printf("AddiNb\n"); 
            break;
          case '*' :
            printf("MultNb\n"); 
            break;
          case '-' :
            printf("SubiNb\n"); 
            break;
          case 'M' :
            printf("NegaNb\n"); 
            break; 
        }	 
      
    } 
     
}


void generateCodeInFile(AST t, char* file){
	FILE* fichier = NULL;
	fichier = fopen(file,"a+");
 
    if(t->left == NULL) {
      fprintf(fichier,"CsteNb %d \n",t->val); 
    }  
    else {
 
      generateCodeInFile(t->left, file); 
      if(t->right != NULL)
        generateCodeInFile(t->right, file);
 
    	switch(t->car){
			case '+' :
				fprintf(fichier, "AddiNb\n");
        break;
			case '*' :
				fprintf(fichier, "MultNb\n"); 
        break;
			case '-' :
				fprintf(fichier, "SubiNb\n");
        break;
			 case 'M' :
            fprintf(fichier,"NegaNb \n"); 
            break; 
		  }	
    }
	fclose(fichier);
}
 