/* init.c */

#include "global.h"

struct symentry keywords[] = {
    { "div", DIV },
    { "mod", MOD, }
};

void init()  /*  loads keywords into symtable  */
{
    int nr_keywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < nr_keywords; ++i)
        insert(keywords[i].lexeme, keywords[i].token_type);
    for (int i = 0; i < MAX_SYMBOLS; ++i)
        symtable[i].value = NONE; /*  initialize all symbol values to -1 (undefined)  */
}
