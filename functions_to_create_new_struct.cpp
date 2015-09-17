#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>


#include "class_struct.h"
#include "new_struct_for_program.h"
#include "singleton_data_struct.h"


GlobalDataStorage& create_functions_data = GlobalDataStorage::Instance();

/////////////////////////////// !!!!!!!!!!!!!!!!!!!!!!

std::string returnLableOfOperator(OperatorTypeClass* _operator){
  //printf("%s\n","try to go work with Lable of Operator" );
  OperatorClass* operator_pointer = dynamic_cast<OperatorClass*>(_operator);
  //printf("%s\n","try to go work with Lable of Operator" );
  if (operator_pointer == NULL) { printf("%s\n","mistake" ); return "";}
  if (operator_pointer->variable_pointer) {
    //printf("%s\n","fail" );
    Variable* _variable_pointer = dynamic_cast<Variable*>(operator_pointer->variable_pointer);
    if (_variable_pointer) {
      std::string temp_str = _variable_pointer->returnName();
      //printf("%s\n", temp_str.c_str() );
      return temp_str; // Нужно вернуть Лэйбл оператора либо его уникальное имя не важно
    }
  }
  //printf("%s\n","fail" );
  return "";
};


void goIntoDefBlockWBCAndFindVariables(OperatorTypeClass* block_pointer, RuleStruct* temp_rule ) {
  ///приведем к удобному типу
  DefinitionBlockClass* def_block = dynamic_cast<DefinitionBlockClass*>(block_pointer);
  //printf("%s\n","work inside goIntoDefBlockWBCAndFindVariables" );
  VariableStruct* temp_variable;
  if (def_block->pointer_to_def_block !=  NULL) {
    //printf("%s\n","try to go inside goIntoDefBlockWBCAndFindVariables" );
    goIntoDefBlockWBCAndFindVariables(def_block->pointer_to_def_block, temp_rule);
  }
  if (def_block->pointer_to_token) {

    TokenClass* token_block = dynamic_cast<TokenClass*>(def_block->pointer_to_token);
    /// Теперь ту разделяется на Var и Sym  но для нас это будет одно и то же
    if (token_block->_token) {
      //printf("%s\n","try to go work with Variables" );
      Symbol* symbol_pointer = dynamic_cast<Symbol*>(token_block->_token);
      if (symbol_pointer) {
        //printf("%s\n","try to go work with Symbols" );
        /// Записываем имя Нужно будет еще обработку имени сделать
        temp_variable = new VariableStruct(symbol_pointer->returnName());
        temp_rule->_variable.push_back(temp_variable);
        create_functions_data.var_struct_vector.push_back(temp_variable);
      }
      else {
        Variable* variable_pointer = dynamic_cast<Variable*>(token_block->_token);
        if (variable_pointer != NULL) {

          temp_variable = new VariableStruct(variable_pointer->returnName());
          // А вот реальное имя надо будет вырезать из уникального
          if (variable_pointer->def_operator != NULL) {
            //std::cout<< variable_pointer->def_operator << std::endl;
            OperatorClass* operator_pointer = dynamic_cast<OperatorClass*>(variable_pointer->def_operator);
            temp_variable->_node_name = returnLableOfOperator(variable_pointer->def_operator);
          }
          temp_rule->_variable.push_back(temp_variable);
          create_functions_data.var_struct_vector.push_back(temp_variable);
        }
      }
    }
  }
}

void goIntoDefinitionBlocksAndFindDefBlocksWithBraceCode(OperatorTypeClass *def_blocks_pointer, NodeStruct *temp_node ){
  DefinitionBlocksClass* def_blocks = dynamic_cast<DefinitionBlocksClass*>(def_blocks_pointer);
  if (def_blocks->pointer_to_def_blocks != NULL){
    goIntoDefinitionBlocksAndFindDefBlocksWithBraceCode(def_blocks->pointer_to_def_blocks,temp_node);
  }
  if (def_blocks->pointer_to_def_block_with_brace_code != NULL){
    // Нашли и теперь записываем к нам в вектор
    DefinitionBlockWithBraceCode* _def_block_w_end = dynamic_cast<DefinitionBlockWithBraceCode*>(def_blocks->pointer_to_def_block_with_brace_code);
    RuleStruct* temp_rule = new RuleStruct();
    // Создали правило 
    
    temp_node->_rule.push_back(temp_rule);

    // Правилу добавим уникальное имя и лэйбл
    temp_rule->_name = returnNewName("Rule_",temp_node->_rule.size());
    temp_rule->_rule_uniq_name = _def_block_w_end->_node_name;
    // Запомнили наше правило в структуру узла

    // теперь аналогично надо найти все переменные на которые ссылается DefBlockWBC
    if (_def_block_w_end->block_pointer != NULL){
        goIntoDefBlockWBCAndFindVariables(_def_block_w_end->block_pointer,temp_rule);
      }
  }
};

void createNodesFromMap(){
  for (auto j=create_functions_data.var_map.begin(); j!=create_functions_data.var_map.end(); ++j){
    NodeStruct* temp_node = 
      new NodeStruct(
              j->second->_node_name,
              j->first->returnName()
            );
    //std::cout << "******"  << j->second->_node_name << std::endl;
    //std::cout << "---***"  << j->first->returnName() << std::endl;
    //std::cout << "---***"  << temp_node->_name << std::endl;
    //std::cout << "---***"  << temp_node->_node_uniq_name << std::endl;
    // Теерь из каждой структуры надо вытащить те данные что мы хотим
    // Сначала создадим структуру Rule
    /// Ищем все ссылки на DefBlocksWithBraceCode
    OperatorClass* searched_operator = dynamic_cast<OperatorClass*>(j->second);
    goIntoDefinitionBlocksAndFindDefBlocksWithBraceCode(
                  searched_operator->definition_block_pointer,
                  temp_node 
                  );
    create_functions_data.node_struct_vector.push_back(temp_node);
  }
}

void generateAdditionalConnectionsInNewStructure(){
  for (auto i=create_functions_data.var_struct_vector.begin(); i != create_functions_data.var_struct_vector.end(); ++i){
    /// Пройдемся по всем векторам и проверим как  
    /// проверим какие имена переменных совпадают с именами переменных в карте и установим соответствующие связи
    for (auto j=create_functions_data.node_struct_vector.begin(); j!=create_functions_data.node_struct_vector.end(); ++j){
      // Дальше уже будем проверять и создавать сответствующие связи
      if ((*i)->_node_name == (*j)->_lable_data) {
        //std::cout << "connection created"<<  (*i)->_node_name << " "<< (*j)->_name << std::endl;
        (*i)->_node = (*j);
      }
    }
  }
}