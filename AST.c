#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

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
AST newLeafAST(float val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val=val;
    t->boo=NULL;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

AST newLeafASTForBool(char* val){
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
 
  if(!strcmp(val,"True"))
    	t->boo="True";
  else if(!strcmp(val,"False"))
    	t->boo="False";
 
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
    if (t->left==NULL) printf(":%f: ",t->val); else printf(":%s: ",t->car);
    printAST(t->right);
    printf("] ");
  }
}

void affichageCode(AST t)
{	
  if(t->left == NULL) {
    if(t->boo != NULL)
      printf("CsteBo %s \n", t->boo);
    else   
      printf("CsteNb %f \n", t->val);
  }  
  else {
 
      affichageCode(t->left); 
      if(t->right != NULL)
        affichageCode(t->right);

         

      if(!strcmp(t->car,"+"))
        printf("AddiNb\n");
      else if(!strcmp(t->car,"*"))
        printf("MultNb\n");
      else if(!strcmp(t->car,"-"))
        printf("SubiNb\n");
      else if(!strcmp(t->car,"/"))
        printf("DiviNb\n");
      else if(!strcmp(t->car,"%"))
        printf("ModuNb\n");
      else if(!strcmp(t->car,"M"))
        printf("NegaNb\n");
      else if(!strcmp(t->car, ">="))
        printf("GrEqNb\n");
      else if(!strcmp(t->car,">"))
        printf("GrStNb\n");
      else if(!strcmp(t->car, "<="))
        printf("LoEqNb\n");
      else if(!strcmp(t->car,"<"))
        printf("LoStNb\n");
      else if(!strcmp(t->car,"=="))
        printf("Equals\n");
      else if(!strcmp(t->car,"!="))
        printf("NotEql\n");
      else if (strcmp(t->car, "!") == 0)
    		printf("Not \n");
      
  	 
      
    } 
     
}


void generateCodeInFile(AST t, char* file){
	FILE* fichier = NULL;
	fichier = fopen(file,"a+");
 
    if(t->left == NULL) {
       if(t->boo != NULL)
      fprintf(fichier,"CsteBo %s \n",t->boo); 
    else   
      fprintf(fichier,"CsteNb %f \n",t->val); 
    }  
    else {
 
      generateCodeInFile(t->left, file); 
      if(t->right != NULL)
        generateCodeInFile(t->right, file);

      if(!strcmp(t->car,"+"))
        fprintf(fichier,"AddiNb\n");
      else if(!strcmp(t->car,"*"))
        fprintf(fichier,"MultNb\n");
      else if(!strcmp(t->car,"-"))
        fprintf(fichier,"SubiNb\n");
      else if(!strcmp(t->car,"/"))
        fprintf(fichier,"DiviNb\n");
      else if(!strcmp(t->car,"%"))
        fprintf(fichier,"ModuNb\n");
      else if(!strcmp(t->car,"M"))
        fprintf(fichier,"NegaNb\n");
      else if(!strcmp(t->car, ">="))
        fprintf(fichier,"GrEqNb\n");
      else if(!strcmp(t->car,">"))
        fprintf(fichier,"GrStNb\n");
      else if(!strcmp(t->car, "<="))
        fprintf(fichier,"LoEqNb\n");
      else if(!strcmp(t->car,"<"))
        fprintf(fichier,"LoStNb\n");
      else if(!strcmp(t->car,"=="))
        fprintf(fichier,"Equals\n");
      else if(!strcmp(t->car,"!="))
        fprintf(fichier,"NotEql\n");
      else if (strcmp(t->car, "!") == 0)
    		fprintf(fichier,"Not \n");
      }
      
	fclose(fichier);
}
 
