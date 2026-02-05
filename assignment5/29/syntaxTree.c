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





