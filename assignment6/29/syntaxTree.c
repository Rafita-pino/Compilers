/*syntaxTree.c*/

#define MAX_ARGS 3
#include "global.h"


TreeNode* mkleaf(int type, int value){ 
    TreeNode* p = (TreeNode*) malloc(sizeof(TreeNode));
    p->type = type;
    p->leaf_value = value;
    for(int i=0;i<MAX_ARGS;i++){
        p->children[i] = NONE;
    }
    
    return p;
}

TreeNode* mknode(int type, TreeNode* left, TreeNode* middle, TreeNode* right) {
    TreeNode* p = (TreeNode*) malloc(sizeof(TreeNode));
    p->type = type;
    p->children[0] = left;
    p->children[1] = middle;
    p->children[2] = right;
    return p;
}

int execute(TreeNode *p) {
    if (p == NONE) return 0;  

    switch(p->type) {
        case NUM:
            return p->leaf_value;

        case ID:
            return symtable[p->leaf_value].value;

        case '=': {
            int val = execute(p->children[2]); // evaluate right-hand side
            symtable[p->children[0]->leaf_value].value = val; // assign value to variable 
            //printf("Assigned %d to %s\n", val, symtable[p->children[0]->leaf_value].lexeme);           
            return val;
        }

        case '+': 
            return execute(p->children[0]) + execute(p->children[2]);
        case '-': 
            return execute(p->children[0]) - execute(p->children[2]);
        case '*': 
            return execute(p->children[0]) * execute(p->children[2]);
        case '/': 
            return execute(p->children[0]) / execute(p->children[2]);
        case DIV:
            return execute(p->children[0]) / execute(p->children[2]);
        case MOD:
            return execute(p->children[0]) % execute(p->children[2]);
        case '%': 
            return execute(p->children[0]) % execute(p->children[2]);
        case '^': 
            return (int) pow(execute(p->children[0]), execute(p->children[2]));
        case '<': 
            return execute(p->children[0]) < execute(p->children[2]);
        case '>': 
            return execute(p->children[0]) > execute(p->children[2]);
        case '&': 
            return execute(p->children[0]) && execute(p->children[2]);
        case '|': 
            return execute(p->children[0]) || execute(p->children[2]);

        case '?': {
            if (execute(p->children[0]))
                return execute(p->children[1]);
            else
                return execute(p->children[2]);
        }

        case PRINT: {
            int val = execute(p->children[0]);
            printf("%d\n", val);
            return val;
        }

        case READ: {
            int x;
            printf("Input a number for the variable %s: ", symtable[p->children[0]->leaf_value].lexeme);
            scanf("%d", &x);
            symtable[p->children[0]->leaf_value].value = x; // assign value to variable
            //printf("Read value %d into %s\n", x, symtable[p->children[0]->leaf_value].lexeme);
            return x;
        }

        case IF: {
            if (execute(p->children[0]))
                return execute(p->children[1]);
            else
                return execute(p->children[2]);
        }

        case WHILE: {
            int result = 0;
            //printf("Entering while loop\n");
            while (execute(p->children[0])) {
                result = execute(p->children[2]);
                //printf("While loop iteration result: %d\n", result);
            }
            //printf("While loop ended with result: %d\n", result);
            return result;
        }

        case ';':
            execute(p->children[0]);
            return execute(p->children[2]);

        default:
            printf("Unknown node type: %d\n", p->type);
            return 0;
    }
}






