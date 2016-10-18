%{
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;
%}

%token MAIN PRINTF IF FOR ELSE CONJ OP NUM IDENTIFIER DATATYPE LOGOP LITERAL INC EQUALS RETURN 

%%

main :MAIN'('')' '{' body '}'{ printf("main ends here\n"); }
;

body: dec stmt1 
;
dec: DATATYPE variable ';' |
;
variable: IDENTIFIER ',' variable |IDENTIFIER {printf("valid declaration\n");}

;
stmt1: stmt stmt1 |
;
stmt: printf | if | inc |assignment | operation
;
operation: var EQUALS var OP var ';'	{printf("valid operation\n");}
;
assignment: var EQUALS NUM	';' {printf("valid assignment\n");}
;
printf: PRINTF '(' LITERAL ')' ';' { printf("valid printf\n");}
;
if: IF '(' condition ')' '{' body '}' {printf("if ends here\n");}
;
condition: IDENTIFIER LOGOP var CONJ condition | IDENTIFIER LOGOP var
;
var: NUM | IDENTIFIER
;
inc: IDENTIFIER INC ';' {printf("valid increment\n");}
;


%%

int main()
{
yyin=fopen("myfile-2.c","r");
yyparse();
fclose(yyin);
return 0;
}

int yyerror(char *s)
{
printf("%s",s);
}
