/* parser.c */

#include "global.h"
int lookahead;

void match(int);
void start(), list(), expr(), moreterms(), term(), morefactors(), factor(), assigment(), power(), morepower();


void parse()  /*  parses and translates expression list  */
{
    lookahead = lexan();
    start();
    
}

void start ()
{
    /* Just one production for start, so we don't need to check lookahead */
    list(); match(DONE);
}


/*  list -> assignment ; list
        | empty
    assignment -> id { print(id.lexeme) } = expr { print('=') }
*/
void list()
{
    if (lookahead == ID || lookahead == NUM) {
        assignment(); match(';'); list();
    }
    else {
        /* Empty */
    }
}

/* Added the necessary function assignment() to understand the new grammar */
void assignment() {
    if (lookahead == ID) {
        int id_number = token_value;
        lookahead = LEFT_ID; 
        match(LEFT_ID);
        emit(LEFT_ID, id_number);
        match('=');
        expr();
        emit('=', id_number);
    } else {
        error("syntax error in assignment");
    }
}


void expr ()
{
    /* Just one production for expr, so we don't need to check lookahead */
    term(); moreterms();
}

void moreterms()
{
    if (lookahead == '+') {
        match('+'); term(); emit('+', token_value); moreterms();
    }
    else if (lookahead == '-') {
        match('-'); term(); emit('-', token_value); moreterms();
    }
    else {
        /* Empty */
    }
}


void term (){
    power(); morefactors();
}

void morefactors ()
{
    if (lookahead == '*') {
        match('*'); power(); emit('*', token_value); morefactors();
    }
    else if (lookahead == '/') {
        match('/'); power(); emit('/', token_value); morefactors();
    }
    else if (lookahead == DIV) {
        match(DIV); power(); emit(DIV, token_value); morefactors();
    }
    else if (lookahead == MOD) {
        match(MOD); power(); emit(MOD, token_value); morefactors();
    }
    else {
        /* Empty */
    }
}

/*
            power -> factor morepowers

            morepowers -> ^ factor {print('^')} morepowers
                    | empty
*/

void power()
{
    factor(); morepower();
}

void morepower()
{
    if (lookahead == '^') {
        match('^'); factor(); emit('^', token_value); morepower();
    }
    else {
        /* Empty */
    }
}


void factor ()
{
    if (lookahead == '(') {
        match('('); expr(); match(')'); 
    }
    else if (lookahead == ID) {
        int id_number = token_value;
        match(ID);
        emit(ID, id_number);
        
    }
    else if (lookahead == NUM) {
        int num_value = token_value;
        match(NUM);
        emit(NUM, num_value);
        
    }
    else
        error("syntax error in factor");
}

void match(int t)
{
    if (lookahead == t)
        lookahead = lexan();
    else
        error ("syntax error in match");
}
