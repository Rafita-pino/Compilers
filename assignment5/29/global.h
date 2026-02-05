/* global.h */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /* ... and for some standard routines, such as exit */
#include <string.h> /* ... and for string routines */
#include "calculator.tab.h"

#define MAX_ID_LENGTH  128  /* for the buffer size */
#define MAX_ARGS    3 /* maxs args for trees*/
#define NONE    NULL /* null pointer for tree nodes */
#define EOS    '\0'
#define MAX_SYMBOLS 100

extern int token_value;   /*  value of token attribute */  
extern int lineno;

extern struct TreeNode* root; /* root of the syntax tree */

struct symentry {  /*  form of symbol table entry  */
    char *lexeme; 
    int  token_type;    
    int value; /*  for save the value of the symbol  */
};

typedef struct TreeNode {
    int type; /* type of node */
    int leaf_value; /* value of node if leaf */
    struct TreeNode *children[MAX_ARGS]; /* pointers to children */
}TreeNode;

extern struct symentry symtable[];  /* symbol table  */

extern void init();  /*  loads keywords into symtable  */
extern void error(char* message);  /*  generates all error messages  */
extern int lexan();  /*  lexical analyzer  */
extern void parse();  /*  parses and translates expression list  */
extern int insert(char *s, int token_type);    /*  returns position of entry for s */
extern int lookup(char *s);         /* returns position of entry for s, or -1 if not found */
extern void emit (int token_type, int token_value);  /*  generates output  */
extern TreeNode* mkleaf(int type, int value); /* create a leaf node */
extern TreeNode* mknode(int type, TreeNode* c1, TreeNode* c2, TreeNode* c3); /* create a node with up to three children */
extern void printtree(TreeNode* p); /* print the syntax tree */

