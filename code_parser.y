%{
    #include <stdio.h>
    #include <iostream>
    #include <list>
    #include <vector>
    #include <class_struct.h>
    #include <search_functions.h>
    extern int yylineno;
    extern int yylex();
    void yyerror(char const *s) {
      std::cerr << s << ", line " << yylineno << std::endl;
      return;
    }
    //#define YYSTYPE std::string

    std::vector<std::string> massive_of_tokens;

/*
    class oper_type { // abstract
        protected: oper_type() {}
        public: virtual ~oper_type() {}
    };

    class token_type{
    	protected: token_type() {}
        public: virtual ~token_type() {}
    };

	/// Объект класса operators будет иметь список ссылок на другие объекты operators,
	/// либо на 1 оператор или и на то и на другое, либо не иметь ссылок, но этого не должно быть.
    /// У нашей грамматики OPS и OP нужно чтобы имели тип oper_type
    /// Это для описания правила    OPS: OP | OPS OP;
    class operators : public oper_type{
    	std::list<oper_type*> ops;
        void append(oper_type* op) {
            operators* b = dynamic_cast<operators*>(op);
            if(b) {
                ops.splice(ops.end(), b->ops, b->ops.begin(), b->ops.end());
                delete b;
            }
            else ops.push_back(op);
        }
        public:
            operators() {}
            operators(oper_type* op) { append(op); }
            operators(oper_type* op1, oper_type* op2) { append(op1); append(op2); }
    };

    /// Затем нам нужен класс который опишет, если идем по-порядку, переменную VARIABLE
    /// Возможно надо бы для него абстрактный класс создать чтобы его типом объявить,
    /// но может и не надо - у него не будет ссылок на другие переменные
    class variable : public token_type
    {
    	/// Просто сделал свойство чтобы было, не факт что потребуется, 
    	/// пока нужен просто класс на который будут ссылаться
    	std::string _token_name;
    	//assignName(std::string assigned_name){ this->_name ;};
    	std::string returnName(){ return _token_name; };
    public:
    	variable(std::string assigned_name): _token_name(assigned_name) {};
    	//~variable();
    };
    class symbol : public token_type
    {
    	/// Просто сделал свойство чтобы было, не факт что потребуется, 
    	/// пока нужен просто класс на который будут ссылаться
    	std::string _token_name;
    	//assignName(std::string assigned_name){ this->_name ;};
    	std::string returnName(){ return _token_name; };
    public:
    	symbol(std::string assigned_name): _token_name(assigned_name){};
    	//~symbol();	
    };
    class brace_code : public token_type
    {
    	/// Просто сделал свойство чтобы было, не факт что потребуется, 
    	/// пока нужен просто класс на который будут ссылаться
    	std::string _token_name;
    	//assignName(std::string assigned_name){ this->_name ;};
    	std::string returnName(){ return _token_name; };
    public:
    	brace_code(std::string assigned_name): _token_name(assigned_name){};
    	//~brace_code();	
    };


    /// Теперь просто идем по порядку Карты. 
    /// На каждую строку после переменной у нас будет свой класс
    /// И каждый раз будет создаваться его экземпляр. Это и будет узел нашего дерева.

    /// OP:  VARIABLE ':' DEFINITION_BLOCKS ';';
    class operator_class : public oper_type
    {
    	/// Должны быть ссылки на variable и definition_block
    	oper_type* definition_block_pointer;
    	token_type* variable_pointer;
    	/// И как-то надо отразить правило создания - ':' и ';' пока не знаю как
    public:
    	operator_class(token_type* variable, oper_type* definition_block): definition_block_pointer(definition_block), variable_pointer(variable) {};
    	//~operator_class();
    };


    /// Вообще все по-другому надо сделать
    /// У нас есть узел такой:
    /// DEFINITION_BLOCKS:    DEFINITION_BLOCK_WITH_END
	/// 					| DEFINITION_BLOCKS '|' DEFINITION_BLOCK_WITH_END   ;
	/// Сделаем по аналогии с OPS: OP | OPS OP;
    class definition_blocks_class : public oper_type
    {
    	/// У него должы быть ссылки на (в виде списка на себя и на другой элемент definition_block_with_end)
    	std::list<oper_type*> _definition_blocks;
    	/// Надо описать метод который при содании будет заполнять этот список ссылками:
    	void append(oper_type* args) {
            definition_blocks_class* b = dynamic_cast<definition_blocks_class*>(args);
            if(b) {
                _definition_blocks.splice(_definition_blocks.end(), b->_definition_blocks, b->_definition_blocks.begin(), b->_definition_blocks.end());
                delete b;
            }
            else _definition_blocks.push_back(args);
        }
    public:
    	definition_blocks_class() {}
        definition_blocks_class(oper_type* op) { append(op); }
        definition_blocks_class(oper_type* op1, oper_type* op2) { append(op1); append(op2); }	
    };

    /// Теперь рассматриваем следующий узел:
    /// DEFINITION_BLOCK_WITH_END:    %empty
	///								| DEFINITION_BLOCK
	///								| DEFINITION_BLOCK BRACE_CODE_TOKEN
	///								| BRACE_CODE_TOKEN
	///	;
    /// Видимо в нашем в случае oper_type это все же тип узла а не тип оператора, но мы можем конкретизировать.
	class definition_block_with_end_class : public oper_type
	{
		/// Здесь должны быть ссылки на
		///| %empty 
		///| DEFINITION_BLOCK
		///| DEFINITION_BLOCK BRACE_CODE_TOKEN
		///| BRACE_CODE_TOKEN
		/// Это все 1-й ссылкой
		oper_type* block_pointer; // Ссылается на все перечисленные, кроме наверное brace_code_token
		token_type* brace_code_pointer; // песть отдельно ссылается на код
	public:
		definition_block_with_end_class(oper_type* block, token_type* brace_code): brace_code_pointer(brace_code), block_pointer(block) {};
	};

	/// DEFINITION_BLOCK:	  TOKEN
	///						| DEFINITION_BLOCK TOKEN
	/// ;
	/// Пропишем класс опять таки по аналогии с OPS: OP | OPS OP;  
	/// Он ссылается на TOKEN и на себя.
	/// 
	/// 
	class definition_block_class : public oper_type
	{
		std::list<oper_type*> _definition_block;
		void append(oper_type* args) {
            definition_block_class* b = dynamic_cast<definition_block_class*>(args);
            if(b) {
                _definition_block.splice(_definition_block.end(), b->_definition_block, b->_definition_block.begin(), b->_definition_block.end());
                delete b;
            }
            else _definition_block.push_back(args);
        }
	public:
		definition_block_class() {}
        definition_block_class(oper_type* op) { append(op); }
        definition_block_class(oper_type* op1, oper_type* op2) { append(op1); append(op2); }	
	};


	/// Теперь рассмотрим узел TOKEN
	/// TOKEN:    VARIABLE 
	///			| SYMBOL 
	/// Он ссылается только на токены либо на 1 либо на другой
	class token_class : public oper_type 
	{
		token_type* _token;
		/// В конструкторе надо сделать присваивание
	public:
		token_class(token_type* arg):  _token(arg) {};
	};

	/// Получается ему будем присваивать 
*/
	///   	oper_type* definition_block_pointer;
    ///	    token_type* variable_pointer;
/*
	/// У нас узлы не одинаковые, поэтому для каждого типа узла сделаем свою функцию.
	void searchOP(oper_type* _OP);
	void searchOPS(oper_type* _OPS);
	/// Их можно как одну использовать разницы нет, а хотя нет, есть. пока оставим так чтобы каждая была отдельно
	void searchVariable(token_type* _variable);
	void searchSymbol(token_type* _symbol);
	void searchBraceCode(token_type* _brace_code);

	void searchDefinitionBlocks(oper_type* _def_blocks);
	void searchDefinitionBlockWithEnd(oper_type* _def_blocks);
	void searchDefinitionBlock(oper_type* _def_blocks);

	void searchToken(oper_type* _def_blocks);



	void searchOPS(oper_type* _OPS){
		operators* _b = dynamic_cast<operators*>(_OPS);
		if (_b) {
			for (auto i=_b->ops.begin(); i!=_b->ops.end(); ++i ){	
				printf("%s -> ", _b->_node_name.c_str());
				searchOP(*i);
			}
		}
		else {
			searchOP(_OPS);
		}
	};

	void searchOP(oper_type* _OP){
		operator_class* _b = dynamic_cast<operator_class*>(_OP);
		printf("%s -> ", _b->_node_name.c_str());
		searchVariable(_b->variable_pointer);
		printf("%s -> ", _b->_node_name.c_str());
		searchDefinitionBlocks(_b->definition_block_pointer);
	};

	void searchVariable(token_type* _variable){	
		variable* _var_p = dynamic_cast<variable*>(_variable);	
		printf("%s;\n", (_var_p->returnName()).c_str());			
	}

	void searchDefinitionBlocks(oper_type* _def_blocks){
		definition_blocks_class* _def_blocks_pointer = dynamic_cast<definition_blocks_class*>(_def_blocks);
		if (_def_blocks_pointer){
			for (auto i=_def_blocks_pointer->_definition_blocks.begin(); i!=_def_blocks_pointer->_definition_blocks.end(); ++i ){
				//printf("%s -> ", _def_blocks_pointer->_node_name.c_str());
				searchDefinitionBlocks(*i);
			} 
		}
		else 
		{
			searchDefinitionBlockWithEnd(_def_blocks);
		}
	};
	void searchDefinitionBlockWithEnd(oper_type* _def_blocks){		
		definition_block_with_end_class* _def_block_with_end_pointer = dynamic_cast<definition_block_with_end_class*>(_def_blocks);
		if (_def_block_with_end_pointer) {
			// Нужно вызвать две функции для обработки Кода в скобках и  Определения блока
			/// Они оба могут быть нулевыми
			if (_def_block_with_end_pointer->block_pointer) {
				//printf("%s -> ", _def_block_with_end_pointer->_node_name.c_str());
				searchDefinitionBlock(_def_block_with_end_pointer->block_pointer);
			}		
			if (_def_block_with_end_pointer->brace_code_pointer) {
				//printf("%s -> ", _def_block_with_end_pointer->_node_name.c_str());
				searchBraceCode(_def_block_with_end_pointer->brace_code_pointer);				
			}
		}
		else {
			//
			//printf("%s\n", "SOMETHING WRONG ***************");
		}
	};
	void searchDefinitionBlock(oper_type* _def_blocks){
		//printf("%s -> ", _def_blocks->_node_name.c_str());
		definition_block_class* _def_block_pointer = dynamic_cast<definition_block_class*>(_def_blocks);
		if (_def_block_pointer) {
			//printf("%s -> ", _def_block_pointer->_node_name.c_str());
			// Просматриваем список и для каждого вызываем эту же функцию
			for (auto i=_def_block_pointer->_definition_block.begin(); i!=_def_block_pointer->_definition_block.end(); ++i ){
				//printf("%s %d---> ", (*i)->_node_name.c_str(), _def_block_pointer->_definition_block.size() );
				searchDefinitionBlock(*i);
			} 
		}
		else {
			//	
			////printf("%s -> ", _def_blocks->_node_name.c_str());
			searchToken(_def_blocks);			
		}
	};

	void searchBraceCode(token_type* _brace_code){		
		brace_code* _brace_code_p = dynamic_cast<brace_code*>(_brace_code);
		if (_brace_code_p) {
			//printf("brace_code%s;\n", (_brace_code_p->returnName()).c_str() );
		}
		else {	
		}
	};

	void searchToken(oper_type* _def_blocks){
		token_class* _token_pointer = dynamic_cast<token_class*>(_def_blocks);
		if (_token_pointer){
			//printf("%s -> ", _token_pointer->_node_name.c_str());
			searchSymbol(_token_pointer->_token);
		}
		else {
			//printf("%s\n", "SOMETHING GOES WRONG !!!!!!!!!!!!!!!!!!!!!!!!!!!");
		}
		
	};

	void searchSymbol(token_type* _token){
		symbol* _token_pointer = dynamic_cast<symbol*>(_token);
		if (_token_pointer) {
			//printf("%s;\n", (_token_pointer->returnName()).c_str() );
		}
		else {
			//
			searchVariable(_token);			
		}

	};

*/
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
															for (
																	auto i = massive_of_tokens.begin(); 
																	i != massive_of_tokens.end();
																	++i
																)
															{
																printf("%s\n", i->c_str() );
															}
															;
															// Попробуем здесь написать алгоритм обхода нашего дерева $3 - первая вершина.
															printf("%s\n","let's try to search little tree structure");
															searchOPS($3);
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

OPS:  OP 	 { $$ = new operators($1,"OPS");    }; // Наследуется от ОР $$ = new operators($1);
	| OPS OP { $$ = new operators($1,$2,"OPS"); }
;

OP:  VARIABLE ':' DEFINITION_BLOCKS ';' { 
											$$ = new operator_class(new variable($1), $3,"OP");
										}
;

DEFINITION_BLOCKS:    DEFINITION_BLOCK_WITH_END                       { $$ = new definition_blocks_class($1,"DEFINITION_BLOCKS");    }; 
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

DEFINITION_BLOCK:	  TOKEN                   { $$ = new definition_block_class($1,"DEFINITION_BLOCK"); }; // Наследуется от { $$ = new definition_block_class($1); }
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
  printf("start\n");
  //yydebug=1;
  return yyparse();
}