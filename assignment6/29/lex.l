/*calculator.l*/
%{
  #include "global.h"
  #include "calculator.tab.h"  //bison tokens
%}
%option noyywrap

%%

[ \t\r]+  ;              // strip out white space

\n  {lineno = lineno +1;}

"while" {return WHILE;}
"if"    {return IF;   }
"else"  {return ELSE; }
"read"  {return READ; }
"print" {return PRINT;}

"done"  {return DONE; }

[0-9]+  {
  yylval.val = atoi(yytext); 
  return NUM;
  }
"{" {return '{';  }
"}" {return '}';  }
"+" {return '+';  }
"-" {return '-';  }
"*" {return '*';  }
"/" {return '/';  }
"mod" {return MOD;}
"div" {return DIV;}
"%" {return '%';  }
"^" {return '^';  }
"=" {return '=';  }
"<" {return '<';  }
">" {return '>';  }
"&" {return '&';  }
"|" {return '|';  }
"?" {return '?';  }
":" {return ':';  }


[A-Za-z][A-Za-z0-9]*  { 
    int id_number = lookup(yytext);
    if (id_number == -1)
        id_number = insert(yytext, ID);
    yylval.val = id_number; 
    return ID;
}

.   { return yytext[0]; }

%%
