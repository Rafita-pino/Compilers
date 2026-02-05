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
    '<' expr { emit('<', token_value); } 
    | '>' expr { emit('>', token_value); } 
    | '&' expr { emit('&', token_value); } 
    | '|' expr { emit('|', token_value); } 
    | /*empty*/
    ;


moreterms:
    '+' term { emit('+', token_value); } moreterms
    | '-' term { emit('-', token_value); } moreterms
    | /* empty */
    ;

term:
    power morefactors
    ;

morefactors:
    '*' power { emit('*', token_value);} morefactors
    | '/' power { emit('/', token_value);} morefactors
    | DIV power { emit(DIV, token_value);} morefactors
    | MOD power { emit(MOD, token_value);} morefactors
    | '%' power { emit('%', token_value);} morefactors
    | /* empty */
    ;

power:
    factor morepowers
    ;

morepowers:
    '^' factor { emit('^', token_value); } morepowers
    | /* empty */
    ;

factor:
    '(' expr ')'
    | ID { emit(ID, token_value); }
    | NUM { emit(NUM, token_value); }
    ;
%%


/*---------------Subroutines----------------*/


int yylex(){
    return lexan();
} 

void yyerror(char *s) {
  error(s);
}

void parse() {
    yyparse();
}
