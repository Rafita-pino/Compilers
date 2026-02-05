/*treePrinter.c*/
#include "global.h"


void printtree1(TreeNode* p, int level) {
    //make space indentation
    printf("%*s", 2 * level, "");
    if (p == NONE) {
        printf("\n");
    }
    else{
        switch (p->type) {
            case ID:
                printf("%s\n", symtable[p->leaf_value].lexeme);
                break;

            case NUM:
                printf("%d\n", p->leaf_value);
                break;

            case '+': case '-': case '*': case '/': case '%':
            case '<': case '>': case '&': case '|': case '^':
            case '=': case ';':
                printf("%c\n", p->type);
                if (p->children[0]) printtree1(p->children[0], level + 1);
                if (p->children[2]) printtree1(p->children[2], level + 1);
                break;

            case MOD:
                printf("MOD\n");
                if (p->children[0]) printtree1(p->children[0], level + 1);
                if (p->children[2]) printtree1(p->children[2], level + 1);
                break;

            case DIV:
                printf("DIV\n");
                if (p->children[0]) printtree1(p->children[0], level + 1);
                if (p->children[2]) printtree1(p->children[2], level + 1);
                break;

            case '?':
                printf("?\n");
                printtree1(p->children[0], level + 1); // condition
                printtree1(p->children[1], level + 1); // true
                printtree1(p->children[2], level + 1); // false
                break;

            case PRINT:
                printf("PRINT\n");
                printtree1(p->children[0], level + 1); // argument
                break; 

            case READ:
                printf("READ\n");
                printtree1(p->children[0], level + 1); // argument
                break;

            case WHILE:
                printf("WHILE\n");
                printtree1(p->children[0], level + 1); // condition
                printtree1(p->children[2], level + 1); // body
                break;
            
            case IF:
                printf("IF\n");
                printtree1(p->children[0], level + 1); // condition
                printtree1(p->children[1], level + 1); // then
                if (p->children[2] != NONE) {   // else
                    printtree1(p->children[2], level + 1);
                }
                break;


            default:
                printf("Unknown node type: %d\n", p->type);
                break;
        }
    }
}

void printtree(TreeNode* p) {
    printf("Syntax tree:\n");
    printtree1(p, 0);    
    printf(";\n");
    exit(0);
}
