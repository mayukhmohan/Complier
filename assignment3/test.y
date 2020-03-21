%{ 
   /* Definition section */
  #include<stdio.h> 
  #include "lex.yy.c"
  void yyerror(char *);
%} 

%token MAIN_TOK
%token LPAREN_TOK
%token RPAREN_TOK
%token LCRLY_TOK
%token RCRLY_TOK
%token INT_TOK
%token ID_TOK
%token COMMA_TOK
%token SEMICOLON_TOK
%start S

/* Rule Section */
%% 

S : DATATYPE MAIN_TOK LPAREN_TOK RPAREN_TOK BLOCK {printf("\nOK MAIN");}
    ;

BLOCK : LCRLY_TOK STATEMENTS BLOCKS RCRLY_TOK     {printf("\nOK BLOCK");}
        ;

BLOCKS : BLOCK STATEMENTS BLOCKS		  {printf("\nOK BLOCKS");}
	 |                                        {}
	 ;

STATEMENTS : STATEMENTS STMT			  {printf("\nOK STATEMENTS");}
	     |
	     ;

STMT : DECLARATION SEMICOLON_TOK                  {printf("\nOK STMT");}
       ;

DECLARATION : DATATYPE ID_TOKEN                   {printf("\nOK DECLARATION");}
	      ;

DATATYPE : INT_TOK                                {printf("\nOK DATATYPE");}
	   |
           ;

ID_TOKEN : ID_TOKEN COMMA_TOK ID_TOK              {printf("\nOK ID_TOKEN");}
         | ID_TOK				  {}
         ;
  
%% 
  
//driver code 
int main() 
{ 
	if(yyparse() == 0) printf("parsing successful");
	else printf("\nParsing Error at Line No %d\n", yylineno);
	return 0; 
} 

void yyerror(char *s)
{
	printf("yyerror: %s\n",s);
}
