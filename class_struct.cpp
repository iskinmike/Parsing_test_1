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
std::string Variable::returnName() { return _token_name; };
Variable::Variable(std::string assigned_name) {
	_token_name.assign(returnNewName("variable",_variable_number));
	std::string temp_str(_token_name);
	_token_name.append("; \n");
	_token_name.append(temp_str);
	_token_name.append(" [label=\"");
	_token_name.append(assigned_name);
	_token_name.append("\" shape=polygon,sides=5,color=lightblue,style=filled ]");
	_variable_number++;
	def_operator = NULL;
};
///
std::string Symbol::returnName() { return _token_name; };
Symbol::Symbol(std::string assigned_name){
	_token_name.assign(returnNewName("symbol",_symbol_number));
	std::string temp_str(_token_name);
	_token_name.append("; \n");
	_token_name.append(temp_str);
	_token_name.append(" [label=\"");
	_token_name.append(assigned_name);
	_token_name.append("\" shape=polygon,sides=5,color=aquamarine,style=filled]");
	_symbol_number++;
};
///
std::string BraceCode::returnName() { return _token_name; };
BraceCode::BraceCode(std::string assigned_name){
	_token_name.assign(returnNewName("brace_code",_brace_code_number));
	_brace_code_number++;
};

// MACROS
#define CREATE_NEW_NAME(node_number)							\
	_node_name.assign(returnNewName(node_name, node_number));	\
	node_number++;

#define DEFINE_THREE_CONSTRUCTORS(class_name, pointer_to_another_type_object, pointer_to_same_type_object, node_number) \
	class_name::class_name(std::string node_name) { \
	CREATE_NEW_NAME(node_number); \
}; \
class_name::class_name(OperatorTypeClass* op, std::string node_name){ \
	CREATE_NEW_NAME(node_number); \
	pointer_to_another_type_object = op; \
	pointer_to_same_type_object = NULL; \
}; \
class_name::class_name(OperatorTypeClass* op1, OperatorTypeClass* op2, std::string node_name){ \
	CREATE_NEW_NAME(node_number); \
	pointer_to_another_type_object = op2; \
	pointer_to_same_type_object = op1; \
};


DEFINE_THREE_CONSTRUCTORS(Operators,pointer_to_operator,pointer_to_operators,_operators_number);

DEFINE_THREE_CONSTRUCTORS(DefinitionBlocksClass,pointer_to_def_block_with_brace_code,pointer_to_def_blocks,_definition_blocks_class_number);

DEFINE_THREE_CONSTRUCTORS(DefinitionBlockClass,pointer_to_token,pointer_to_def_block,_definition_block_class_number);


OperatorClass::OperatorClass(TokenTypeClass* variable,
                               OperatorTypeClass* definition_block,
                               std::string node_name)
    : definition_block_pointer(definition_block),
      variable_pointer(variable) {
  CREATE_NEW_NAME(_operator_class_number);
};
DefinitionBlockWithBraceCode::DefinitionBlockWithBraceCode(
    OperatorTypeClass* block, TokenTypeClass* brace_code, std::string node_name)
    : brace_code_pointer(brace_code),
      block_pointer(block) {
  CREATE_NEW_NAME(_definition_block_with_end_class_number);
};
TokenClass::TokenClass(TokenTypeClass* arg, std::string node_name)
    : _token(arg) {
  CREATE_NEW_NAME(_token_class_number);
};




