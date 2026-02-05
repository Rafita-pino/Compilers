/*calculator.y*/

%{

#include "global.h"
extern void yyerror(char*);
extern int yylex(void);

%}


%union {
    int val;
}

%token <val> NUM
%token <val> ID LEFT_ID
%token DIV MOD DONE
%left '<' '>' '&' '|'
%left '+' '-'
%left '*' '/' DIV MOD '%'
%right '^'      /*right associativity*/
%right '?' ':'


%%
/* grammar */
start: 
    list DONE
    ;

list:
    input ';' list
    | /* empty */
    ;

input:
    assignment
    | expr { emit('=', NONE); }
    ;

assignment:
    ID '=' expr 
    { 
        emit(LEFT_ID, $1); 
        emit('=', $1);
    }
    ;

expr:
    arithmetics nonarithmetics conditional
    ;

conditional:
    '?' expr ':' expr {emit('?', NONE); }
    | /*empty*/
    ;

arithmetics:
    term moreterms
    | /*empty*/
    ;

nonarithmetics:
    '<' expr { emit('<', yylval.val); } 
    | '>' expr { emit('>', yylval.val); } 
    | '&' expr { emit('&', yylval.val); } 
    | '|' expr { emit('|', yylval.val); } 
    | /*empty*/
    ;


moreterms:
    '+' term { emit('+', yylval.val); } moreterms
    | '-' term { emit('-', yylval.val); } moreterms
    | /* empty */
    ;

term:
    power morefactors
    ;

morefactors:
    '*' power { emit('*', yylval.val);} morefactors
    | '/' power { emit('/', yylval.val);} morefactors
    | DIV power { emit(DIV, yylval.val);} morefactors
    | MOD power { emit(MOD, yylval.val);} morefactors
    | '%' power { emit('%', yylval.val);} morefactors
    | /* empty */
    ;

power:
    factor morepowers
    ;

morepowers:
    '^' factor { emit('^', yylval.val); } morepowers
    | /* empty */
    ;

factor:
    '(' expr ')'
    | ID { emit(ID, yylval.val); }
    | NUM { emit(NUM, yylval.val); }
    ;
%%


/*---------------Subroutines----------------*/


/*int yylex(){
    return lexan();
} */

void yyerror(char *s) {
  error(s);
}

void parse() {
    yyparse();
}
