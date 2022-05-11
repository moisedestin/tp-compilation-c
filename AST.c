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
    t->ide = NULL;

    if(t->right != NULL)
    	if(!strcmp(t->car,"If") && strcmp(t->car,"IfElse")){
	    	t->taille = 2 + right->taille;
    	}
   	else
   		t->taille = 1 + left->taille + right->taille;	 
    else 
    	t->taille = 1 + left->taille;
   
    if(t->right != NULL && t->right->car && !strcmp(t->right->car,"IfElse"))
   	 t->taille -= 1; 
    else if(t->left != NULL && t->left->car && !strcmp(t->left->car,"IfElse"))
    	 t->taille -= 1;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char* car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

AST newUnaryASTide(char* ide, char* incre){
	return newBinaryASTide(incre, ide, NULL);
}

/* create an AST from a root value, a variable and one AST son */
AST newBinaryASTide(char* car, char* ide, AST son)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){
    t->ide = chaine(ide);
    if(son != NULL)
   	 t->taille = 1 + son->taille;
    else{ 
    	t->taille = 1;
    	if(!strcmp(car,"++"))
    		t->taille = 4;
    }
    t->car=car;
    t->boo = NULL;
    t->left= son;
    t->right= NULL;
  } else printf("MALLOC! ");
  return t;
}


/* create an AST leaf from a value */
AST newLeafAST(char* val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val=chaine(val);
    t->boo=NULL;
    t->taille = 1;
    t->ide=NULL;
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
    t->taille = 1;
    t->ide=NULL;
    t->car=NULL;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

AST newLeafASTide(char* chaine){
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	
    t->boo = NULL;
    char c[11] = {'+','*','-','/','<','>','=','!',';','(',')'};
    char* ch;
    ch = strtok(chaine,c);
    t->ide=ch;
    t->taille = 1;
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

char* chaine(char* c){
	char* ch = (char*)malloc(strlen(c)*sizeof(char));
	for(int i = 0; i<strlen(c);i++){
		if(c[i] != '='){
			ch[i]=c[i];
		}		
		else{
		 	ch[i]=c[i];
			return ch;
		}
	}
	return ch;
}

void affichageCode(AST t)
{	
   if (t->left!=NULL){ 
    	 
    	if(!strcmp(t->car,"Else"))
	    	printf("Jump %d \n",t->taille-1); 
    	  affichageCode(t->left);
    }
    if (t->right!=NULL){ 
    	if(!strcmp(t->car,"If"))
	    	printf("ConJmp %d \n",t->taille-1); 
    	  affichageCode(t->right);
    	
    }
    
    if(t->left == NULL){

      if(t->boo == NULL && (t->ide == NULL)){
        char c[9] = {'+','*','/','<','>','=','!',';'};
              char c2[9] = {'+','*','-','/','<','>','=','!',';'};
              
              if(!strstr(t->val,"e-"))
            strtok(t->val,c2);
          else
            strtok(t->val,c);
            printf("CsteNb %s \n",t->val);
      }
	    	
      else if (t->ide == NULL ){
        if(strcmp(t->boo,"NaN"))
          printf("CsteBo %s \n",t->boo); 
      }
	    else if (t->boo == NULL )  {
		
      if(strstr(t->ide, "++")){
        strtok(t->ide,"++");
        printf("GetVar %s\n",t->ide);
        printf("CstNb 1\n");
        printf("AddiNb\n");
        printf("SetVar %s\n", t->ide);
      }
      else
        printf("GetVar %s \n",t->ide);
	}
    } 	  
    
  
  else {

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
      else if (!strcmp(t->car, "=") && t->ide != NULL) {
    		strtok(t->ide,"=");
    		printf("SetVar %s \n",t->ide); 
    	}
  	 
      
    } 
     
}


void generateCodeInFile(AST t, char* file){
	FILE* fichier = NULL;
	fichier = fopen(file,"a+");
 
    if (t->left!=NULL){
    	if(!strcmp(t->car,"Else")){
	    	FILE* fichier = NULL;
		fichier = fopen(file,"a+");
	    	fprintf(fichier,"Jump %d \n",t->taille-1);
	    	fclose(fichier);
	}
    	generateCodeInFile(t->left,file); 
    	
    }
    if (t->right!=NULL){ 
    	if(!strcmp(t->car,"If")){
    	       FILE* fichier = NULL;
	       fichier = fopen(file,"a+");
	       fprintf(fichier,"ConJmp %d \n",t->taille-1);
	       fclose(fichier);
	} 
    	generateCodeInFile(t->right,file);
    }
   
    if(t->left == NULL){
    	if(t->boo == NULL && (t->ide == NULL)){
    		char c[9] = {'+','*','/','<','>','=','!',';'};
	        char c2[9] = {'+','*','-','/','<','>','=','!',';'};
	        
	        if(!strstr(t->val,"e-"))
  			strtok(t->val,c2);
  		else
  			strtok(t->val,c);
  		FILE* fichier = NULL;
	        fichier = fopen(file,"a+");
  		fprintf(fichier,"CsteNb %s \n",t->val);
  		fclose(fichier);
    	}
	else if (t->ide == NULL){
		if(strcmp(t->boo,"NaN")){
			FILE* fichier = NULL;
	        	fichier = fopen(file,"a+");
			fprintf(fichier,"CsteBo %s \n",t->boo);
			fclose(fichier);
		}
	}
	else if (t->boo == NULL) {
		if(strstr(t->ide, "++")){
			strtok(t->ide,"++");
			FILE* fichier = NULL;
	        	fichier = fopen(file,"a+");
			fprintf(fichier,"GetVar %s\n",t->ide);
			fprintf(fichier,"CstNb 1\n");
			fprintf(fichier,"AddiNb\n");
			fprintf(fichier,"SetVar %s\n", t->ide);
			fclose(fichier);
		}
		else{
			FILE* fichier = NULL;
	        	fichier = fopen(file,"a+");
			fprintf(fichier,"GetVar %s\n",t->ide); 
			fclose(fichier);
		}
	} 	
    } 
     	 

    else {
  

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
      else if (!strcmp(t->car, "=") && t->ide != NULL) {
    		strtok(t->ide,"=");
    		printf("SetVar %s \n",t->ide); 
    	}

      }
      
	fclose(fichier);
}
 
