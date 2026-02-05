/*calculator.y*/

%{

#include "global.h"
extern void yyerror(char*);
extern int yylex(void);
extern void printtree(TreeNode* p);
TreeNode* root = NONE;
%}


%union {
    struct TreeNode *p;
    int val;
}

%token <val> NUM ID
%token DIV MOD DONE WHILE IF PRINT READ ELSE
%left '<' '>' '&' '|'
%left '+' '-'
%left '*' '/' DIV MOD '%'
%right '^'      /*right associativity*/
%right '?' ':'

%type <p> start expr conditional arithmetics term power factor relational block block_list

%%
/* grammar */
start: 
    block_list DONE {root = $$; printtree(root);}
    ;

block_list:
    block block_list { $$ = mknode(';', $1, NONE, $2);  }
    | block { $$ = $1; }
    | /* empty */   { $$ = NONE; }
    ;

block:
    '{' block_list '}'                              {$$ = $2; }
    | WHILE '(' expr ')' block_list                 { $$ = mknode(WHILE, $3, NONE, $5);    }
    | IF '(' expr ')' block_list                    { $$ = mknode(IF, $3, $5, NONE);       }
    | IF '(' expr ')' block_list ELSE block_list    { $$ = mknode(IF, $3, $5, $7);    }
    | PRINT '(' ID ')' ';'                          { $$ = mknode(PRINT, mkleaf(ID, $3), NONE, NONE);  }
    | PRINT '(' NUM ')' ';'                         { $$ = mknode(PRINT, mkleaf(NUM, $3), NONE, NONE);  }
    | READ '(' ID ')' ';'                           { $$ = mknode(READ, mkleaf(ID, $3), NONE, NONE);   }
    | expr ';'                                      { $$ = $1; }
    ;


expr:
    ID '=' expr { $$ = mknode('=', mkleaf(ID, $1 ), NONE, $3); }
    | relational conditional { $$ = ($2) ? mknode('?', $1, $2->children[0], $2->children[2]) : $1; }
    ;

conditional:
    '?' expr ':' expr { $$ = mknode('?', $2, NONE, $4); }
    | /* empty */ { $$ = NONE; }
    ;

relational:
      relational '<' arithmetics { $$ = mknode('<', $1, NONE, $3); }
    | relational '>' arithmetics { $$ = mknode('>', $1, NONE, $3); }
    | relational '&' arithmetics { $$ = mknode('&', $1, NONE, $3); }
    | relational '|' arithmetics { $$ = mknode('|', $1, NONE, $3); }
    | arithmetics { $$ = $1; }
    ;

arithmetics:
      arithmetics '+' term   { $$ = mknode('+', $1, NONE, $3); }
    | arithmetics '-' term   { $$ = mknode('-', $1, NONE, $3); }
    | term                   { $$ = $1; }
    ;

term:
      term '*' power        { $$ = mknode('*', $1, NONE, $3); }
    | term '/' power        { $$ = mknode('/', $1, NONE, $3); }
    | term DIV power        { $$ = mknode(DIV, $1, NONE, $3); }
    | term MOD power        { $$ = mknode(MOD, $1, NONE, $3); }
    | term '%' power        { $$ = mknode('%', $1, NONE, $3); }
    | power                 { $$ = $1; }
    ;


power:
      factor '^' power      { $$ = mknode('^', $1, NONE, $3); }
    | factor                { $$ = $1; }
    ;


factor:
    '(' expr ')' { $$ = $2; }
    | ID { $$ = mkleaf(ID, yylval.val); }
    | NUM { $$ = mkleaf(NUM, yylval.val); }
    ;
%%


/*---------------Subroutines----------------*/


void yyerror(char *s) {
  error(s);
}

void parse() {
    yyparse();
}
