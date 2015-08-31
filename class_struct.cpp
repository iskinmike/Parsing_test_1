#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <stdlib.h>
#include <class_struct.h>

/// GLOBAL VARIABLES
int _operators_number = 0;
int _operator_class_number = 0;
int _definition_blocks_class_number = 0;
int _definition_block_with_end_class_number = 0;
int _definition_block_class_number = 0;
int _token_class_number = 0;
int _symbol_number = 0;
int _variable_number = 0;
int _brace_code_number = 0;

std::string returnNewName(std::string str, int number) {
  char buf[10];
  sprintf(buf, "%d", number);
  str.append("_");
  str.append(buf);
  return str;
};

/// variable VARIBLE
std::string variable::returnName() { return _token_name; };
variable::variable(std::string assigned_name) {
	_token_name.assign(returnNewName("variable",_variable_number));
	std::string temp_str(_token_name);
	_token_name.append("; \n");
	_token_name.append(temp_str);
	_token_name.append(" [label=\"");
	_token_name.append(assigned_name);
	_token_name.append("\"]");
	_variable_number++;
};
///
std::string symbol::returnName() { return _token_name; };
symbol::symbol(std::string assigned_name){
	_token_name.assign(returnNewName("symbol",_symbol_number));
	std::string temp_str(_token_name);
	_token_name.append("; \n");
	_token_name.append(temp_str);
	_token_name.append(" [label=\"");
	_token_name.append(assigned_name);
	_token_name.append("\"]");
	_symbol_number++;
};
///
std::string brace_code::returnName() { return _token_name; };
brace_code::brace_code(std::string assigned_name){
	_token_name.assign(returnNewName("brace_code",_brace_code_number));
	_brace_code_number++;
};

/*
	/// MACROS
	#define APPEND_METHOD(class_name, list_parameter)                    \
	  void class_name::append(oper_type* op) {                           \
	    class_name* b = dynamic_cast<class_name*>(op);                   \
	    if (b) {                                                         \
	      list_parameter.push_back(op);         	                     \
	      delete b;                                                      \
	    } else                                                           \
	      list_parameter.push_back(op);                                  \
	};

	#define THREE_CONSTRUCTORS(class_name, node_number)                        \
	  class_name::class_name(std::string node_name) : _color(color_t::WHITE) { \
	    _node_name.assign(returnNewName(node_name, node_number));              \
	    node_number++;                                                         \
	  };                                                                       \
	  class_name::class_name(oper_type* op, std::string node_name)             \
	      : _color(color_t::WHITE) {                                           \
	    append(op);                                                            \
	    _node_name.assign(returnNewName(node_name, node_number));              \
	    node_number++;                                                         \
	  };                                                                       \
	  class_name::class_name(oper_type* op1, oper_type* op2,                   \
	                         std::string node_name)                            \
	      : _color(color_t::WHITE) {                                           \
	    append(op1);                                                           \
	    append(op2);                                                           \
	    _node_name.assign(returnNewName(node_name, node_number));              \
	    node_number++;                                                         \
	  };

	//// operators OPS
	APPEND_METHOD(operators, ops);
	THREE_CONSTRUCTORS(operators, _operators_number);

	//// definition_blocks_class DEFINITION_BLOCKS
	APPEND_METHOD(definition_blocks_class, _definition_blocks);
	THREE_CONSTRUCTORS(definition_blocks_class, _definition_blocks_class_number);

	//// definition_block_class DEFINITION_BLOCK
	APPEND_METHOD(definition_block_class, _definition_block);
	THREE_CONSTRUCTORS(definition_block_class, _definition_block_class_number);

	operator_class::operator_class(token_type* variable,
	                               oper_type* definition_block,
	                               std::string node_name)
	    : definition_block_pointer(definition_block),
	      variable_pointer(variable),
	      _color(color_t::WHITE) {
	  _node_name.assign(returnNewName(node_name, _operator_class_number));
	  _operator_class_number++;
	};
	definition_block_with_end_class::definition_block_with_end_class(
	    oper_type* block, token_type* brace_code, std::string node_name)
	    : brace_code_pointer(brace_code),
	      block_pointer(block),
	      _color(color_t::WHITE) {
	  _node_name.assign(
	      returnNewName(node_name, _definition_block_with_end_class_number));
	  _definition_block_with_end_class_number++;
	};
	token_class::token_class(token_type* arg, std::string node_name)
	    : _token(arg), _color(color_t::WHITE) {
	  _node_name.assign(returnNewName(node_name, _token_class_number));
	  _token_class_number++;
	};
*/


//oper_type* pointer_to_OP;
//oper_type* pointer_to_OPS;

// MACROS
#define CREATE_NEW_NAME(node_number)							\
	_node_name.assign(returnNewName(node_name, node_number));	\
	node_number++;

#define DEFINE_THREE_CONSTRUCTORS(class_name, pointer_to_another_type_object, pointer_to_same_type_object, node_number) \
	class_name::class_name(std::string node_name) { \
	CREATE_NEW_NAME(node_number); \
}; \
class_name::class_name(oper_type* op, std::string node_name){ \
	CREATE_NEW_NAME(node_number); \
	pointer_to_another_type_object = op; \
	pointer_to_same_type_object = NULL; \
}; \
class_name::class_name(oper_type* op1, oper_type* op2, std::string node_name){ \
	CREATE_NEW_NAME(node_number); \
	pointer_to_another_type_object = op2; \
	pointer_to_same_type_object = op1; \
};

/*
	operators::operators(std::string node_name) {
		CREATE_NEW_NAME(_operators_number);
	};
	operators::operators(oper_type* op, std::string node_name){
		CREATE_NEW_NAME(_operators_number);
		pointer_to_OP = op;
	};
	operators::operators(oper_type* op1, oper_type* op2, std::string node_name){
		CREATE_NEW_NAME(_operators_number);
		pointer_to_OP = op1;
		pointer_to_OPS = op2;
	};
*/

DEFINE_THREE_CONSTRUCTORS(operators,pointer_to_OP,pointer_to_OPS,_operators_number);

DEFINE_THREE_CONSTRUCTORS(definition_blocks_class,pointer_to_DEF_BLOCK_WITH_END,pointer_to_DEF_BLOCKS,_definition_blocks_class_number);

DEFINE_THREE_CONSTRUCTORS(definition_block_class,pointer_to_token,pointer_to_def_block,_definition_block_class_number);


operator_class::operator_class(token_type* variable,
                               oper_type* definition_block,
                               std::string node_name)
    : definition_block_pointer(definition_block),
      variable_pointer(variable),
      _color(color_t::WHITE) {
  CREATE_NEW_NAME(_operator_class_number);
};
definition_block_with_end_class::definition_block_with_end_class(
    oper_type* block, token_type* brace_code, std::string node_name)
    : brace_code_pointer(brace_code),
      block_pointer(block),
      _color(color_t::WHITE) {
  CREATE_NEW_NAME(_definition_block_with_end_class_number);
};
token_class::token_class(token_type* arg, std::string node_name)
    : _token(arg), _color(color_t::WHITE) {
  CREATE_NEW_NAME(_token_class_number);
};




