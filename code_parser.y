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

    extern void setNewBuffer(const char *buffer_pointer);

    void yyerror(char const *s) {
      std::cerr << s << ", line " << yylineno << std::endl;
      return;
    }
    //#define YYSTYPE std::string

    std::vector<std::string> massive_of_tokens;

	typedef struct {
        std::string str;
        OperatorTypeClass* node_t;
        TokenTypeClass* token_t; /// Пока не используется но может понадобится
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
															searchOperators($3);
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

OPS:  OP 	 { $$ = new Operators($1,"OPS");    } // Наследуется от ОР $$ = new Operators($1);
	| OPS OP { $$ = new Operators($1,$2,"OPS"); }
;

OP:  VARIABLE ':' DEFINITION_BLOCKS ';' { 
											$$ = new OperatorClass(new Variable($1), $3,"OP");
										}
;

DEFINITION_BLOCKS:    DEFINITION_BLOCK_WITH_END                       { $$ = new DefinitionBlocksClass($1,"DEFINITION_BLOCKS");    } 
					| DEFINITION_BLOCKS '|' DEFINITION_BLOCK_WITH_END { $$ = new DefinitionBlocksClass($1,$3,"DEFINITION_BLOCKS"); }
;

DEFINITION_BLOCK_WITH_END:                                      { $$ = new DefinitionBlockWithBraceCode( NULL,
																											NULL,
																											"DEFINITION_BLOCK_WITH_END"
																											);
																} 
							| DEFINITION_BLOCK                  { $$ = new DefinitionBlockWithBraceCode( $1,
																											NULL,
																											"DEFINITION_BLOCK_WITH_END"
																											);
																}
							| DEFINITION_BLOCK BRACE_CODE_TOKEN { $$ = new DefinitionBlockWithBraceCode( $1,
																											new BraceCode($2),
																											"DEFINITION_BLOCK_WITH_END"
																											); 
																}
							| BRACE_CODE_TOKEN                  { 
																	$$ = new DefinitionBlockWithBraceCode( NULL,
																											  new BraceCode($1),
																											  "DEFINITION_BLOCK_WITH_END"
																											  );
																}
;

DEFINITION_BLOCK:	  TOKEN                   { 
												$$ = new DefinitionBlockClass($1,"DEFINITION_BLOCK"); 
												} // Наследуется от { $$ = new DefinitionBlockClass($1); }
					| DEFINITION_BLOCK TOKEN  { $$ = new DefinitionBlockClass($1,$2,"DEFINITION_BLOCK");  }
;

TOKEN:    VARIABLE  { 
						//printf("Var %s\n", $1.c_str()); 
						$$ = new TokenClass(new Variable($1), "TOKEN");
					}
		| SYMBOL    { 
						//printf("Sym %s\n", $1.c_str());
						$$ = new TokenClass(new Symbol($1), "TOKEN");
					} 
;
%%

int main(int argc, char **argv){
  //yydebug=1;
  
  // Перед вызовом лекса надо считать из файла и в память.
  int const max_buffer_size = 2048;
  char buff[max_buffer_size];
  std::string _str("");
  FILE * pFile;

  pFile = fopen("temp_test_file.txt","r+");

  if (pFile != NULL)
  {
	while (fgets(buff, 2048, pFile)){
		_str.append(buff);
	}
	fclose(pFile);
	std::string temp_first_pars_string("");
	int pos_of_percen_brace;
	pos_of_percen_brace = _str.find("%{");
	if (pos_of_percen_brace != -1) {
		temp_first_pars_string = _str.substr(0,pos_of_percen_brace);
		temp_first_pars_string.append(_str.substr(_str.find("%}")+3));
		_str.assign(temp_first_pars_string);
		//std::cout << "test buffer:\n" << _str << std::endl;
	}
	else {	
		//std::cout << "test buffer:\n" << _str << std::endl;
	}
  }
  else {
    std::cout << "can't open file" << pFile << std::endl;
  }
  /// Set New Buffer For Flex Input
  setNewBuffer(_str.c_str());
  // Работает, этого должно быть достаточно чтобы собрать например массив строк,
  //  и из него сделать буфек из которого будем читать


  return yyparse();
}