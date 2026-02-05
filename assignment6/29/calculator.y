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

%type <p> start expr conditional arithmetics term power factor relational statement block_list else r

%%
/* grammar */
start: 
    block_list DONE {root = $$; printtree(root);}
    ;

block_list:
    statement block_list    { $$ = ($2) ? mknode(';', $1, NONE, $2) : $1;  }
    | /* empty */   { $$ = NONE; }
    ;

statement:
    '{' block_list '}'                               { $$ = $2;  }
    | WHILE '(' expr ')' '{' block_list '}'                  { $$ = mknode(WHILE, $3, NONE, $6);    }
    | IF '(' expr ')' '{' block_list '}'  else                { $$ = mknode(IF, $3, $6, $8);    }
    | PRINT '(' r ')' ';'                           { $$ = mknode(PRINT, $3, NONE, NONE);  }
    | READ '(' ID ')' ';'                           { $$ = mknode(READ, mkleaf(ID, $3), NONE, NONE);   }
    | expr ';'                                      { $$ = $1; }
    ;

r:
    ID                                              { $$ = mkleaf(ID, $1);  }
    | NUM                                           { $$ = mkleaf(NUM, $1); }
    ;

else:
    ELSE '{' block_list '}'                           { $$ = $3;  }
    | /*empty*/                                     { $$ = NONE;    }
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
