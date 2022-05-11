#ifndef _AST_H_
#define _AST_H_

/* unary-and-binary tree structure */
struct _tree {
   char* car;                    /* char for arithmetic operation */
  char* val;		 
  char* boo;
  char* ide;
  int taille;
  struct _tree* left;    	/* used for unary node but NULL if leaf */
  struct _tree* right;   	/* NULL if unary node or leaf*/
};

typedef struct _tree* AST;

char* chaine(char* c);
/* create an AST from a root value and two AST sons */
AST newBinaryAST(char* car, AST left, AST right);

/* create an AST from a root value and one AST son */
AST newUnaryAST(char* car, AST son);
AST newUnaryASTide(char* ide, char* incre);

AST newBinaryASTide(char* car, char* ide, AST son);
/* create an AST leaf from a value */
AST newLeafAST(char* val);

AST newLeafASTForBool(char* chaine);
AST newLeafASTide(char* chaine);

/* delete an AST */
void freeAST(AST t);

void affichageCode(AST t); 

char *commandForElement(AST t);
/* print an AST*/
void printAST(AST t);

void generateCodeInFile(AST t, char* file);


#endif // !_AST_H_
