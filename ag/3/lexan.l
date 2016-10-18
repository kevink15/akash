%{
#include <stdio.h>
int line=0;
%}

%%

"/*"(.|\n)*"*/" {printf("%s is comment", yytext); 		
	fprintf(yyout,"%d \t %s \t Comment\n", line, yytext);}

"//"(.)* {printf("%s is comment", yytext);
	fprintf(yyout,"%d \t %s \t Comment\n", line, yytext);
}


"#include" {printf("%s is preprocessor directive", yytext);
	fprintf(yyout,"%d \t %s \t Preprocessor Directive\n", line, yytext);
}

"<"(.)*">" {printf("%s is header file", yytext);
	fprintf(yyout,"%d \t %s \t Header File\n", line, yytext);
}

(printf) | 
(scanf) {printf("%s is header file", yytext);
	fprintf(yyout,"%d \t %s \t Library Function\n", line, yytext);
}

int |
float |
char {printf("%s is datatype", yytext);
	fprintf(yyout,"%d \t %s \t Datatype\n", line, yytext);
}


for |
return |
main  {printf("%s is keyword", yytext);
	fprintf(yyout,"%d \t %s \t Keyword\n", line, yytext);
}


itn |
flaot |
mian  {printf("%s is error", yytext);
	fprintf(yyout,"%d \t %s \t Error\n", line, yytext);
}


[<>+_*&(){}<>/=]+ {printf("%s is symbol", yytext);
	fprintf(yyout,"%d \t %s \t Symbol\n", line, yytext);
}


[A-Za-z_][A-Za-z0-9]* {printf("%s is identifier", yytext);
	fprintf(yyout,"%d \t %s \t Identifer\n", line, yytext);
}


[0-9]+ {printf("%s is number", yytext);
	fprintf(yyout,"%d \t %s \t Number\n", line, yytext);
}


%d |
%s |
%c |
%f {printf("%s is format specifier", yytext);
	fprintf(yyout,"%d \t %s \t Format Specifier", line, yytext);
}

"\n" {++line;}
" " ;

%%

int main()
{
	yyin=fopen("myfile.c", "r");
	yyout=fopen("myfile1.txt","w");

	fprintf(yyout, "Line \t Lexeme \t Token\n");

	yylex();

	fclose(yyin);

	return 1;
}
int yyerror()
{
	printf("Error!");
}
int yywrap()
{
	return 1;
}
