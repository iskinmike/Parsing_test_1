%{
	#include <string>
	#include <vector>
	#include <stdio.h>
	#include <fstream>
	#include <iostream>
   #define YYSTYPE std::string
   #include "code_parser.tab.h"
   void yyerror(char const *s);
   //std::vector<std::string> massive_of_tokens;
   int percent_count = 0; // if we met second double percent - call yyterminate(); 
%}

%option yylineno
%option noyywrap

%x TOKEN_ARGUMENTS
%x BRACE_CODE
%x COMMENT

%%

[%][{][^%]*[%][}]    {; }

%token                         { BEGIN(TOKEN_ARGUMENTS); ; return TOKEN_LINE_START;}
<TOKEN_ARGUMENTS>[ \t\r]                 ;
<TOKEN_ARGUMENTS>[a-zA-Z_][a-zA-Z0-9_]*  { yylval = yytext; return RETURNED_TOKEN;} // Записываем в массив имя аргумента 
<TOKEN_ARGUMENTS>[\n]                    { BEGIN(INITIAL);  }

[%][%]              {
	
	percent_count++;
	if (percent_count>1) {
		yyterminate();
	}
	return DOUBLE_PERCENT;
}

[%][^t{%].*\n 		{;} // whitespace
[%][t][^o].*\n      {;} // whitespace

[/][*]              {  BEGIN(COMMENT); }
<COMMENT>[^*][^/]   {;} // whitespace <COMMENT>[ \t\r\n]  {;} 
<COMMENT>[*][/]     {  BEGIN(INITIAL); }

[{]                 {  yylval = ""; BEGIN(BRACE_CODE); }
<BRACE_CODE>[^}]+	{;} //<BRACE_CODE>[ \t\r\n]   {;}
<BRACE_CODE>[}]     {  BEGIN(INITIAL);  return BRACE_CODE_TOKEN; }

[/][/].*\n      ; // comment

[a-zA-Z_][a-zA-Z0-9_]* { 
							yylval = yytext;
							//printf("%s\n","variable" );
			                return VARIABLE;
		                }

['].[']        			{ 
							//printf("%s\n", "symbol" );

							yylval = yytext;
							return SYMBOL; 
						}

[ \t\r\n]      			; // whitespace
[;:|] 			{ return *yytext; }
.               yyerror("Invalid character");

%%

void setNewBuffer(const char *buffer_pointer){
	YY_BUFFER_STATE bp;

	bp = yy_scan_string(buffer_pointer);
	yy_switch_to_buffer(bp);
}