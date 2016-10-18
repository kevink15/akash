%{

#include <stdio.h>
#include "y.tab.h"

%}

digit [0-9]+
identifier [a-zA-Z][a-zA-Z0-9]*
%%
[\t\n]+ ;
main {return MAIN;}
printf {return PRINTF;}
int |
float |
char |
double { return DATATYPE;}
if {return IF;}
else {return ELSE;}
for {return FOR;}
return {return RETURN;}
"=" {return EQUALS;}
"!=" |
"==" |
"<=" |
">=" |
"<" |
">" {return LOGOP;}

"++" |
"--" {return INC;}

"&&" |
"||" {return CONJ;}

"+" |
"-" |
"*" |
"/" {return OP;}

{digit} {return NUM;}
{identifier} {return IDENTIFIER;}
\"(.)*\" {return LITERAL;}

"(" | 
")" |
"{" |
"}" |
"[" |
"]" |
";" |
"," {return yytext[0];}

%%

int yywrap()
{
return 1;
}
