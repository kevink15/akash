%{
  #include<stdio.h>
  #include<string.h>
  #include<stdlib.h>
void qudraple();//function to find the quadruple code
char AddToTable(char ,char, char);//function to create a table of the oper,operands & res

  int ind=0;
  char temp='A'; //a temporary variable that serves the purpose of  a register
  struct incod  //structure storing the contents of an expression
  {
     char opd1;
     char opd2;
     char opr;
  };
%}

%union
{
 char sym; //to define datatypes of tokens returned by yylex
}

%token <sym> LETTER NUMBER //LETTER NUMBER are tokens
%type <sym> expr 
%left '-''+'
%right '*''/'

%%

statement: LETTER '=' expr ';' 
           | expr ';'
	   ;

expr: expr '+' expr {$$ = AddToTable($1,$3,'+');}     //instead of manipulating
      | expr '-' expr {$$ = AddToTable($1,$3,'-');}   //stack,directly add to 
      | expr '*' expr {$$ = AddToTable($1,$3,'*');}   //table
      | expr '/' expr {$$ = AddToTable($1,$3,'/');}
      | '(' expr ')' {$$ = (char)$2;}
      | NUMBER {$$ = (char)$1;}
      | LETTER {$$ = (char)$1;}
      ;

%%

yyerror(char *s)
{
  printf("%s",s);
  exit(0);
}

struct incod code[20]; //to store expresions

int id=0;

char AddToTable(char opd1,char opd2,char opr)
{
code[ind].opd1=opd1;
//store the values in the structure
code[ind].opd2=opd2;
code[ind].opr=opr;
ind++;
temp++;
return temp;
}

void quadraple()
{
    int cnt=0;
temp++; //increment the temporary variable{Which serves as a register}
printf("\n\n\t QUADRAPLE CODE\n\n");
while(cnt<ind)
{         printf("%d",id);
          printf("\t");       
          printf("%c",code[cnt].opr);
          printf("\t");    
           if(isalnum(code[cnt].opd1)) //checks if token is an alphabetic or numeric
        printf("%c\t",code[cnt].opd1);
            else
        {printf("%c\t",temp);} //if not then print the temporary variable ie. register val
        if(isalnum(code[cnt].opd2))
            printf("%c\t",code[cnt].opd2);
        else
        {printf("%c\t",temp);}
       
        printf("%c",temp);

    printf("\n");
    cnt++;
    temp++;
    id++;
   
}
}




main()
{
 printf("\nEnter the Expression: ");
 yyparse(); //call for parsing,generate tokens.
printf("\n---------\n");
temp='A';
quadraple();
}

int yywrap()
{
 return 1;
}
