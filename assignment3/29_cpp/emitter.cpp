/* emitter.c */

#include "global.h"
#include "calculator.tab.h"
#define MAX_STACK_SIZE 1000

int stack[MAX_STACK_SIZE];
int sp = 0;  /*  stack pointer  */

void push(int token_type){
    if (sp<MAX_STACK_SIZE){
        stack[sp++] = token_type;
    } else {
        error("stack overflow");
    }
}

int pop(){
    if (sp > 0) {
        return stack[--sp];
    }else {
        error("stack underflow");
    }
    return 0; /* to avoid compiler warning */
}

void emit (int token_type, int token_value)  /*  generates output  */
{
    int x, y, result;
    switch(token_type) {
        case '+' :{
             x=pop(); y=pop();
            result = y + x;
            push(result);
            printf("%c\n", token_type); 
            break;
        } 
           
        case '-' :{
            x=pop(); y=pop();
            result = y - x;
            push(result);
            printf("%c\n", token_type); 
            break;
        }
            

        case '*' : {
            x=pop(); y=pop();
            result = y * x;
            push(result);
            printf("%c\n", token_type); 
            break;
        }
            

        case '/' : {
            x=pop(); y=pop();
            if (x == 0) {
                error("division by zero");
            }
            result = y/x;
            push(result);
            printf("%c\n", token_type); 
            break;
        }
            
        case '^' : {
            x=pop(); y=pop();
            result = 1;
            for (int i = 0; i < x; i++) {
                result *= y;
            }
            push(result);
            printf("%c\n", token_type); 
            break;
        }

        case DIV:{
             x=pop(); y=pop();
            if (x == 0) {
                error("division by zero");
            }
            result = y / x;
            push(result);
            printf("DIV\n"); 
            break; 
        }
           

        case MOD:{
            x=pop(); y=pop();
            if (x == 0) {
                error("modulus by zero");
            }
            result = y % x;
            push(result);
            printf("MOD\n"); 
            break;
        }
            

        case '%':{
            x=pop(); y=pop();
            if (x == 0) {
                error("modulus by zero");
            }
            result = y % x;
            push(result);
            printf("%c\n", token_type); 
            break;
            
        }


        case '&':{
            x=pop(); y=pop();
            result = y & x;
            push(result);
            printf("%c\n", token_type); 
            break;
        }
            

        case '|':{
            x=pop(); y=pop();
            result = y | x;
            push(result);
            printf("%c\n", token_type); 
            break;
        }
            

        case '<':{
            x=pop(); y=pop();
            result = (y < x) ? 1 : 0;
            push(result);
            printf("%c\n", token_type); 
            break;
        }
            

        case '>':{
            x=pop(); y=pop();
            result = (y > x) ? 1 : 0;
            push(result);
            printf("%c\n", token_type); 
            break; 
        }
             
        
        case '?':{
            int expr3 = pop();
            int expr2 = pop();
            int expr1 = pop();
            result = expr1 ? expr2 : expr3;
            push(result);
            printf("%c\n", token_type); 
            break;
        }
            

        case NUM:{
             printf("%d\n", token_value); 
            push(token_value);
            break;
        }
           
        case ID:{
            printf("%s\n", symtable[token_value].lexeme); 
            push(symtable[token_value].value); /*  push the value of the ID  */
            break; 
        }
            
        case LEFT_ID:{
            printf("%s\n", symtable[token_value].lexeme); 
            break;
        }
            

        case '=':{
            printf("=\n");
            result = pop();  /* value of expression */              
            symtable[token_value].value = result;
            printf("%s = %d\n", symtable[token_value].lexeme, result);
            break;
        }
            

        default: {
            printf("[Unknown token %d, with value %d]\n", token_type, token_value);
            break;
        }    
    }
}


