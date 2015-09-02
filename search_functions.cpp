#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <class_struct.h>
#include <search_functions.h>

OperatorTypeClass* g_oper=NULL;

std::vector<Variable*> var_vector;
std::map<Variable*,OperatorTypeClass*> var_map;


void setGlobalOperator(OperatorTypeClass* _oper){
  g_oper= _oper;
};


void createAdditionalConnections(){
  printf("%s\n","edge [color=red];" );
  for (auto i=var_vector.begin(); i!=var_vector.end(); ++i){
    for (auto j=var_map.begin(); j!=var_map.end(); ++j){

      std::string map_string;
      map_string.assign(j->first->returnName());
      map_string=map_string.substr(map_string.find('\"')+1);
      map_string=map_string.substr(0,map_string.find('\"'));

      std::string temp_str;
      temp_str.assign((*i)->returnName());
      temp_str=temp_str.substr(temp_str.find("\"")+1);
      temp_str=temp_str.substr(0,temp_str.find("\""));

      //printf("%s -> %s ;\n",temp_str.c_str(),map_string.c_str());

      if (temp_str.compare(map_string) ==0 ){
        (*i)->def_operator = j->second;
        temp_str.assign((*i)->returnName());
        temp_str=temp_str.substr(0,temp_str.find(";"));
        printf("%s -> %s;\n",temp_str.c_str(), j->second->_node_name.c_str() );
      }
    }
  }
};




void searchOperators(OperatorTypeClass* _operators) {
  Operators* _b = dynamic_cast<Operators*>(_operators);
  if (_b) {
    if (_b->pointer_to_operators != NULL) {
      //printf("%s -> ", _b->_node_name.c_str());
      searchOperators(_b->pointer_to_operators);
    }
    if (_b->pointer_to_operator != NULL) {
      //printf("%s -> ", _b->_node_name.c_str());
      searchOperator(_b->pointer_to_operator);
    }
  } else {
    printf("%s\n", "operator type");
    searchOperator(_operators);
  }
}

void searchOperator(OperatorTypeClass* _operator) {
  OperatorClass* _b = dynamic_cast<OperatorClass*>(_operator);
  if (_b->variable_pointer != NULL){
    
    ///// additional block. Fill map of variables and Operators
    Variable* _var_p = dynamic_cast<Variable*>(_b->variable_pointer);
    var_map[_var_p] = _operator;
    /////
    printf("%s -> ", _b->_node_name.c_str());
    searchVariable(_b->variable_pointer);
  }
  if (_b->definition_block_pointer != NULL){
    printf("%s -> ", _b->_node_name.c_str());
    searchDefinitionBlocks(_b->definition_block_pointer);
  }
};

void searchVariable(TokenTypeClass* _variable) {
  Variable* _var_p = dynamic_cast<Variable*>(_variable);
  ///// additional block. Fill vector of variables
  //var_vector.push_back(_var_p);
  /////
  printf("%s ;\n", _var_p->returnName().c_str());
}

void searchDefinitionBlocks(OperatorTypeClass* _def_blocks) {
  DefinitionBlocksClass* _b = dynamic_cast<DefinitionBlocksClass*>(_def_blocks);
  if (_b) {
    if (_b->pointer_to_def_block_with_brace_code){
      printf("%s -> ", _b->_node_name.c_str());
      searchDefinitionBlockWithEnd(_b->pointer_to_def_block_with_brace_code);
    }
    if (_b->pointer_to_def_blocks) {
      printf("%s -> ", _b->_node_name.c_str());
      searchDefinitionBlocks(_b->pointer_to_def_blocks);
    }
  }
  else {printf("%s\n", "smething wrong entered in DefinitionBlocks !!!!!!!!!!!!!!!!!!!!!!!");}

};

void searchDefinitionBlockWithEnd(OperatorTypeClass* _def_block_w_end) {
  DefinitionBlockWithBraceCode* _b = dynamic_cast<DefinitionBlockWithBraceCode*>(_def_block_w_end);
  if (_b) {
    if (_b->brace_code_pointer != NULL) {
      printf("%s -> ", _b->_node_name.c_str());
      searchBraceCode(_b->brace_code_pointer);
    }
    if (_b->block_pointer !=NULL) {
      printf("%s -> ", _b->_node_name.c_str());
      searchDefinitionBlock(_b->block_pointer);
    }
    if ((_b->block_pointer == NULL) && (_b->brace_code_pointer == NULL) ) {
      printf("%s%s\n",_b->_node_name.c_str(),"_empty;");
    }
  }
};

void searchBraceCode(TokenTypeClass* _brace_code) {
  BraceCode* _brace_code_p = dynamic_cast<BraceCode*>(_brace_code);
  if (_brace_code_p) {
    printf("%s ;\n", _brace_code_p->returnName().c_str());
  } else {
    /// Не уверн пока надо ли сюда что-то запихивать
  }
};

void searchDefinitionBlock(OperatorTypeClass* _def_block){
  DefinitionBlockClass* _b = dynamic_cast<DefinitionBlockClass*>(_def_block);
  if (_b){
    if (_b->pointer_to_token != NULL) {
      printf("%s -> ", _b->_node_name.c_str());
      searchToken(_b->pointer_to_token);
    }
    if (_b->pointer_to_def_block != NULL) {
      printf("%s -> ", _b->_node_name.c_str());
      searchDefinitionBlock(_b->pointer_to_def_block);
    }
  }
};

void searchToken(OperatorTypeClass* _token_block){
  TokenClass* _b = dynamic_cast<TokenClass*>(_token_block);
  if (_b) {
    if (_b->_token != NULL){
      searchSymbol(_b->_token);
    }
  }
};

void searchSymbol(TokenTypeClass* _token) {
  Symbol* _token_pointer = dynamic_cast<Symbol*>(_token);
  if (_token_pointer) {
    printf("%s ;\n", _token_pointer->returnName().c_str());
  } 
  else {
    ///// additional block. Fill vector of variables
    Variable* _var_p = dynamic_cast<Variable*>(_token);
    var_vector.push_back(_var_p);
    /////
    searchVariable(_token);
  }
};
