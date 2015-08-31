
enum class color_t
        {
        	WHITE, 
        	GREY,
        	BLACK
        };

class oper_type { // abstract
        protected: oper_type() {}
        public: virtual ~oper_type(){};
    	public: int i;	
    	public: std::string _node_name; 	
    };

class token_type{ // abstract
    	protected: token_type() {}
        public: virtual ~token_type() {}
    };


class variable : public token_type
    {
    	std::string _token_name;
    public:
    	std::string returnName();
    	variable(std::string assigned_name);
    	//~variable();
    };
class symbol : public token_type
    {
    	std::string _token_name;
    	
    public:
    	std::string returnName();
    	symbol(std::string assigned_name);
    	//~symbol();	
    };
class brace_code : public token_type
    {
    	std::string _token_name;
    	//assignName(std::string assigned_name){ this->_name ;};
    	
    public:
    	std::string returnName();
    	brace_code(std::string assigned_name);
    	//~brace_code();	
    };

class operators : public oper_type{
        //void append(oper_type* op);
        public:
        	int _node_number;
        	color_t _color;
        	
        	//std::string _node_name;
        	std::list<oper_type*> ops;
        	oper_type* pointer_to_OP;
        	oper_type* pointer_to_OPS;
            operators(std::string node_name);
            operators(oper_type* op, std::string node_name);
            operators(oper_type* op1, oper_type* op2, std::string node_name);
    };

class operator_class : public oper_type
    {	
    public:
    	 int _node_number;
    	color_t _color;
    	//std::string _node_name;
    	oper_type* definition_block_pointer;
    	token_type* variable_pointer;
    	operator_class(token_type* variable, oper_type* definition_block, std::string node_name);
    	//~operator_class();
    };

class definition_blocks_class : public oper_type
    {
    	//void append(oper_type* args);
    public:
    	 int _node_number;
    	std::list<oper_type*> _definition_blocks;
    	color_t _color;
    	oper_type* pointer_to_DEF_BLOCKS;
        oper_type* pointer_to_DEF_BLOCK_WITH_END;
    	//std::string _node_name;
    	definition_blocks_class(std::string node_name);
        definition_blocks_class(oper_type* op, std::string node_name);
        definition_blocks_class(oper_type* op1, oper_type* op2, std::string node_name);
    };

class definition_block_with_end_class : public oper_type
	{
	public:
		 int _node_number;

		oper_type* block_pointer; // Ссылается на все перечисленные, кроме наверное brace_code_token
		token_type* brace_code_pointer; // песть отдельно ссылается на код
		color_t _color;
		//std::string _node_name;
		definition_block_with_end_class(oper_type* block, token_type* brace_code, std::string node_name);
	};

class definition_block_class : public oper_type
	{
		
		//void append(oper_type* args);
	public:
		 int _node_number;
		std::list<oper_type*> _definition_block;
		color_t _color;
		//std::string _node_name;
		oper_type* pointer_to_def_block;
        oper_type* pointer_to_token;
		definition_block_class(std::string node_name);
        definition_block_class(oper_type* op, std::string node_name);
        definition_block_class(oper_type* op1, oper_type* op2, std::string node_name);
	};

class token_class : public oper_type 
	{
		color_t _color;
	public:
		 int _node_number;
		//std::string _node_name;
		token_type* _token;
		token_class(token_type* arg, std::string node_name);
	};