%{
    #include <stdio.h>
    #include <iostream>
    #include <list>
    #include <vector>
    #include "class_struct.h"
    #include "search_functions.h"
    #include "create_program_functions.h"
    extern int yylineno;
    extern int yylex();
    void yyerror(char const *s) {
      std::cerr << s << ", line " << yylineno << std::endl;
      return;
    }
    //#define YYSTYPE std::string

    std::vector<std::string> massive_of_tokens;

	typedef struct {
        std::string str;
        oper_type* node_t;
        token_type* token_t; /// Пока не используется но может понадобится
    } YYSTYPE;
    #define YYSTYPE YYSTYPE

    //#define YYPRINT(file, type, value) printf("%d", value);
%}

%token VARIABLE
%token SYMBOL
%token BRACE_CODE_TOKEN

%token RETURNED_TOKEN

%token DOUBLE_PERCENT 
%token PERCENT_OPEN_BRACE
%token PERCENT_CLOSE_BRACE
%token TOKEN_LINE_START
 
%error-verbose

%type<str>     VARIABLE SYMBOL BRACE_CODE_TOKEN RETURNED_TOKEN
%type<node_t>  OPS OP DEFINITION_BLOCKS DEFINITION_BLOCK DEFINITION_BLOCK_WITH_END TOKEN

%%

PROGRAM: TOKEN_SECTION_EMPTY_OR_NOT DOUBLE_PERCENT OPS  {
															printf("%s\n","digraph G {\nsize =\"40,40\";");
															searchOPS($3);
															createAdditionalConnections();
															printf("%s","}");
														}
	; 

TOKEN_SECTION_EMPTY_OR_NOT:  
							| TOKEN_LINES
;

TOKEN_LINES:  TOKEN_LINE
			| TOKEN_LINES TOKEN_LINE
;

TOKEN_LINE: TOKEN_LINE_START RETURNED_TOKENS			
;

RETURNED_TOKENS:  RETURNED_TOKEN                  { massive_of_tokens.push_back($1); }
				| RETURNED_TOKENS RETURNED_TOKEN  { massive_of_tokens.push_back($2); }
;

OPS:  OP 	 { $$ = new operators($1,"OPS");    } // Наследуется от ОР $$ = new operators($1);
	| OPS OP { $$ = new operators($1,$2,"OPS"); }
;

OP:  VARIABLE ':' DEFINITION_BLOCKS ';' { 
											$$ = new operator_class(new variable($1), $3,"OP");
										}
;

DEFINITION_BLOCKS:    DEFINITION_BLOCK_WITH_END                       { $$ = new definition_blocks_class($1,"DEFINITION_BLOCKS");    } 
					| DEFINITION_BLOCKS '|' DEFINITION_BLOCK_WITH_END { $$ = new definition_blocks_class($1,$3,"DEFINITION_BLOCKS"); }
;

DEFINITION_BLOCK_WITH_END:                                      { $$ = new definition_block_with_end_class( NULL,
																											NULL,
																											"DEFINITION_BLOCK_WITH_END"
																											);
																} 
							| DEFINITION_BLOCK                  { $$ = new definition_block_with_end_class( $1,
																											NULL,
																											"DEFINITION_BLOCK_WITH_END"
																											);
																}
							| DEFINITION_BLOCK BRACE_CODE_TOKEN { $$ = new definition_block_with_end_class( $1,
																											new brace_code($2),
																											"DEFINITION_BLOCK_WITH_END"
																											); 
																}
							| BRACE_CODE_TOKEN                  { 
																	$$ = new definition_block_with_end_class( NULL,
																											  new brace_code($1),
																											  "DEFINITION_BLOCK_WITH_END"
																											  );
																}
;

DEFINITION_BLOCK:	  TOKEN                   { 
												$$ = new definition_block_class($1,"DEFINITION_BLOCK"); 
												} // Наследуется от { $$ = new definition_block_class($1); }
					| DEFINITION_BLOCK TOKEN  { $$ = new definition_block_class($1,$2,"DEFINITION_BLOCK");  }
;

TOKEN:    VARIABLE  { 
						//printf("Var %s\n", $1.c_str()); 
						$$ = new token_class(new variable($1), "TOKEN");
					}
		| SYMBOL    { 
						//printf("Sym %s\n", $1.c_str());
						$$ = new token_class(new symbol($1), "TOKEN");
					} 
;
%%

int main(int argc, char **argv){
  //yydebug=1;
  return yyparse();
}