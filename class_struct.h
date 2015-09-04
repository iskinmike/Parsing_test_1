

std::string returnNewName(std::string str, int number);

enum class color_t
        {
        	WHITE, 
        	GREY,
        	BLACK
        };

class OperatorTypeClass { // abstract
        protected: OperatorTypeClass() {}
        public: virtual ~OperatorTypeClass(){};
    	public: int i;	
    	public: std::string _node_name; 	
    };

class TokenTypeClass{ // abstract
    	protected: TokenTypeClass() {}
        public: virtual ~TokenTypeClass() {}
    };


class Variable : public TokenTypeClass
    {
    	std::string _token_name;
    public:
    	OperatorTypeClass* def_operator;
    	std::string returnName();
    	Variable(std::string assigned_name);
    	//~Variable();
    };
class Symbol : public TokenTypeClass
    {
    	std::string _token_name;
    	
    public:
    	std::string returnName();
    	Symbol(std::string assigned_name);
    	//~Symbol();	
    };
class BraceCode : public TokenTypeClass
    {
    	std::string _token_name;
    	//assignName(std::string assigned_name){ this->_name ;};
    	
    public:
    	std::string returnName();
    	BraceCode(std::string assigned_name);
    	//~BraceCode();	
    };

class Operators : public OperatorTypeClass{
        //void append(OperatorTypeClass* op);
        public:
        	int _node_number;
        	color_t _color;

        	//std::string _node_name;
        	std::list<OperatorTypeClass*> ops;
        	OperatorTypeClass* pointer_to_operator;
        	OperatorTypeClass* pointer_to_operators;
            Operators(std::string node_name);
            Operators(OperatorTypeClass* op, std::string node_name);
            Operators(OperatorTypeClass* op1, OperatorTypeClass* op2, std::string node_name);
    };

class OperatorClass : public OperatorTypeClass
    {	
    public:
    	 int _node_number;
    	color_t _color;
    	//std::string _node_name;
    	OperatorTypeClass* definition_block_pointer;
    	TokenTypeClass* variable_pointer;
    	OperatorClass(TokenTypeClass* Variable, OperatorTypeClass* definition_block, std::string node_name);
    	//~OperatorClass();
    };

class DefinitionBlocksClass : public OperatorTypeClass
    {
    	//void append(OperatorTypeClass* args);
    public:
    	 int _node_number;
    	std::list<OperatorTypeClass*> _definition_blocks;
    	color_t _color;
    	OperatorTypeClass* pointer_to_def_blocks;
        OperatorTypeClass* pointer_to_def_block_with_brace_code;
    	//std::string _node_name;
    	DefinitionBlocksClass(std::string node_name);
        DefinitionBlocksClass(OperatorTypeClass* op, std::string node_name);
        DefinitionBlocksClass(OperatorTypeClass* op1, OperatorTypeClass* op2, std::string node_name);
    };

class DefinitionBlockWithBraceCode : public OperatorTypeClass
	{
	public:
		 int _node_number;

		OperatorTypeClass* block_pointer; // Ссылается на все перечисленные, кроме наверное Brace_code_token
		TokenTypeClass* brace_code_pointer; // песть отдельно ссылается на код
		color_t _color;
		//std::string _node_name;
		DefinitionBlockWithBraceCode(OperatorTypeClass* block, TokenTypeClass* Brace_code, std::string node_name);
	};

class DefinitionBlockClass : public OperatorTypeClass
	{
		
		//void append(OperatorTypeClass* args);
	public:
		 int _node_number;
		std::list<OperatorTypeClass*> _definition_block;
		color_t _color;
		//std::string _node_name;
		OperatorTypeClass* pointer_to_def_block;
        OperatorTypeClass* pointer_to_token;
		DefinitionBlockClass(std::string node_name);
        DefinitionBlockClass(OperatorTypeClass* op, std::string node_name);
        DefinitionBlockClass(OperatorTypeClass* op1, OperatorTypeClass* op2, std::string node_name);
	};

class TokenClass : public OperatorTypeClass 
	{
		color_t _color;
	public:
		 int _node_number;
		//std::string _node_name;
		TokenTypeClass* _token;
		TokenClass(TokenTypeClass* arg, std::string node_name);
	};