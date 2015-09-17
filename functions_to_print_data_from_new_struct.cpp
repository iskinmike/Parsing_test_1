#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>


#include "class_struct.h"
#include "new_struct_for_program.h"
#include "singleton_data_struct.h"
#include "functions_to_print_data_from_new_struct.h"

GlobalDataStorage& print_functions_data = GlobalDataStorage::Instance();

//////////////////////////////////////////////// PRINT LABLE
void printNodeLable(NodeStruct* _node){
  if (_node->_rule.size() != 0) {
    for (auto i = _node->_rule.begin(); i!= _node->_rule.end(); ++i){
      if ((*i)!=NULL) {
        _node->printLable();
        printRuleLable((*i));
      }
    }
  }
};
void printRuleLable(RuleStruct* _rule){
  if(_rule->_variable.size() == 0){
    _rule->printLable();
  }
  for (auto i = _rule->_variable.begin(); i!= _rule->_variable.end(); ++i){
    if ((*i)!=NULL) {
      _rule->printLable();
      printVariableLable((*i));
    }
  }
};
void printVariableLable(VariableStruct* _variable){
  if (_variable->_node == NULL){
    _variable->printLable();
  }
  //if (_variable->_node != NULL) {
    //printNodeLable(_variable->_node);
  //}
};

//////////////////////////////////////////////// PRINT DATA
void printNodeData(NodeStruct* _node){
  //printf("%s ->\n", _node->_name.c_str());
  //_node->_node_uniq_name = _node->_name.substr(0,_node->_name.find('\n') - 2); // (-2) чтобы убрать ;
  if (_node->_rule.size() != 0) {
    for (auto i = _node->_rule.begin(); i!= _node->_rule.end(); ++i){
      if ((*i)!=NULL) {
        //printf("%s\n","works" );
        printf("%s -> ",_node->_node_uniq_name.c_str() );
        printRuleData((*i));
      }
    }
  }
};
void printRuleData(RuleStruct* _rule){
  //printf("%s -> ", _rule->_name.c_str());
  if(_rule->_variable.size() == 0){
    printf("%s;\n ", _rule->_rule_uniq_name.c_str());
  }
  for (auto i = _rule->_variable.begin(); i!= _rule->_variable.end(); ++i){
    if ((*i)!=NULL) {
      printf("%s -> ", _rule->_rule_uniq_name.c_str());
      printVariableData((*i));
    }
  }
};
void printVariableData(VariableStruct* _variable){
  //printf("%s\n", _variable->_name.c_str());
  //printf("%s;\n", _variable->_variable_uniq_name.c_str() );
  if (_variable->_node != NULL) {
    // Эти связи отдельно сделаем
    printf("%s;\n",_variable->_node->_node_uniq_name.c_str() );
    //printf("%s -> ", _variable->_variable_uniq_name.c_str() );
    //printNodeData(_variable->_node);
  }
  else {
    printf("%s;\n", _variable->_variable_uniq_name.c_str() );
  }
};


///////////////////////////////////////////////////////// PRINT ALL
void printAllDataFromNewStruct(){
  for (auto i = print_functions_data.node_struct_vector.begin(); i!= print_functions_data.node_struct_vector.end(); ++i){
    printNodeData(*i);
  }
  // теперь надо вывести все связи
/*
  for (auto i=print_functions_data.var_struct_vector.begin(); i != print_functions_data.var_struct_vector.end(); ++i){
    if ((*i)->_node != NULL) {
      printf("%s -> %s;\n",(*i)->_variable_uniq_name.c_str(), (*i)->_node->_node_uniq_name.c_str());
    }
  }
*/
  for (auto i = print_functions_data.node_struct_vector.begin(); i!= print_functions_data.node_struct_vector.end(); ++i){
    printNodeLable(*i);
  }
}