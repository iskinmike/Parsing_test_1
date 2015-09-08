#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>


#include "class_struct.h"
#include "new_struct_for_program.h"
#include "search_functions.h"
#include "singleton_data_struct.h"

//std::vector<Variable*> var_vector_for_additional_connections;
//std::map<Variable*,OperatorTypeClass*> var_map;
//std::vector<VariableStruct *> var_struct_vector;
//std::vector<NodeStruct*> node_struct_vector;

DataStorage& search_functions_data = DataStorage::Instance();

/////////////////////////////// !!!!!!!!!!!!!!!!!!!!!!
/*
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
        search_functions_data.var_struct_vector.push_back(temp_variable);
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
          search_functions_data.var_struct_vector.push_back(temp_variable);
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
  for (auto j=search_functions_data.var_map.begin(); j!=search_functions_data.var_map.end(); ++j){
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
    search_functions_data.node_struct_vector.push_back(temp_node);
  }
}

void generateAdditionalConnectionsInNewStructure(){
  for (auto i=search_functions_data.var_struct_vector.begin(); i != search_functions_data.var_struct_vector.end(); ++i){
    /// Пройдемся по всем векторам и проверим как  
    /// проверим какие имена переменных совпадают с именами переменных в карте и установим соответствующие связи
    for (auto j=search_functions_data.node_struct_vector.begin(); j!=search_functions_data.node_struct_vector.end(); ++j){
      // Дальше уже будем проверять и создавать сответствующие связи
      if ((*i)->_node_name == (*j)->_lable_data) {
        //std::cout << "connection created"<<  (*i)->_node_name << " "<< (*j)->_name << std::endl;
        (*i)->_node = (*j);
      }
    }
  }
}
*/
/*
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
      //else {printf("%s\n","don't work" );}
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

void printAllDataFromNewStruct(){
  for (auto i = search_functions_data.node_struct_vector.begin(); i!= search_functions_data.node_struct_vector.end(); ++i){
    printNodeData(*i);
  }
  // теперь надо вывести все связи

  ///for (auto i=search_functions_data.var_struct_vector.begin(); i != search_functions_data.var_struct_vector.end(); ++i){
  ///  if ((*i)->_node != NULL) {
  ///    printf("%s -> %s;\n",(*i)->_variable_uniq_name.c_str(), (*i)->_node->_node_uniq_name.c_str());
  ///  }
  ///}

  for (auto i = search_functions_data.node_struct_vector.begin(); i!= search_functions_data.node_struct_vector.end(); ++i){
    printNodeLable(*i);
  }
}
*/
/////////////////////////////// !!!!!!!!!!!!!!!!!!!!!!!


void createAdditionalConnections(){
  //printf("%s\n","edge [color=red];" );
  for (auto i=search_functions_data.var_vector_for_additional_connections.begin(); i!=search_functions_data.var_vector_for_additional_connections.end(); ++i){
    for (auto j=search_functions_data.var_map.begin(); j!=search_functions_data.var_map.end(); ++j){
      
      std::string map_string;
      map_string.assign(j->first->returnName());
      map_string=map_string.substr(map_string.find('\"')+1);
      map_string=map_string.substr(0,map_string.find('\"'));

      std::string temp_str;
      temp_str.assign((*i)->returnName());
      temp_str=temp_str.substr(temp_str.find("\"")+1);
      temp_str=temp_str.substr(0,temp_str.find("\""));

      ////printf("%s -> %s ;\n",temp_str.c_str(),map_string.c_str());

      if (temp_str.compare(map_string) ==0 ){
        ////printf("%s\n","edge [color=red];" );
        (*i)->def_operator = j->second;
        temp_str.assign((*i)->returnName());
        temp_str=temp_str.substr(0,temp_str.find(";"));
        //printf("%s -> %s;\n",temp_str.c_str(), j->second->_node_name.c_str() );
      }
    }
  }
  //for (auto j=search_functions_data.var_vector_for_additional_connections.begin(); j!=search_functions_data.var_vector_for_additional_connections.end(); ++j){
  //  std::cout << (*j)->def_operator << std::endl;
  //}
};

void searchOperators(OperatorTypeClass* _operators) {
  Operators* _b = dynamic_cast<Operators*>(_operators);
  if (_b) {
    if (_b->pointer_to_operators != NULL) {
      ////printf("%s -> ", _b->_node_name.c_str());
      searchOperators(_b->pointer_to_operators);
    }
    if (_b->pointer_to_operator != NULL) {
      ////printf("%s -> ", _b->_node_name.c_str());
      searchOperator(_b->pointer_to_operator);
    }
  } else {
    //printf("%s\n", "operator type");
    searchOperator(_operators);
  }
}

void searchOperator(OperatorTypeClass* _operator) {
  OperatorClass* _b = dynamic_cast<OperatorClass*>(_operator);

  if (_b->variable_pointer != NULL){
    
    ///// additional block. Fill map of variables and Operators
    Variable* _var_p = dynamic_cast<Variable*>(_b->variable_pointer);
    search_functions_data.var_map[_var_p] = _operator;
    /////
    //printf("%s -> ", _b->_node_name.c_str());
    searchVariable(_b->variable_pointer);
  }
  if (_b->definition_block_pointer != NULL){
    //printf("%s -> ", _b->_node_name.c_str());
    searchDefinitionBlocks(_b->definition_block_pointer);
  }
};

void searchVariable(TokenTypeClass* _variable) {
  Variable* _var_p = dynamic_cast<Variable*>(_variable);
  ///// additional block. Fill vector of variables
  //d.push_back(_var_p);
  /////
  //printf("%s ;\n", _var_p->returnName().c_str());
}

void searchDefinitionBlocks(OperatorTypeClass* _def_blocks) {
  DefinitionBlocksClass* _b = dynamic_cast<DefinitionBlocksClass*>(_def_blocks);
  if (_b) {
    if (_b->pointer_to_def_block_with_brace_code){
      //printf("%s -> ", _b->_node_name.c_str());
      searchDefinitionBlockWithEnd(_b->pointer_to_def_block_with_brace_code);
    }
    if (_b->pointer_to_def_blocks) {
      //printf("%s -> ", _b->_node_name.c_str());
      searchDefinitionBlocks(_b->pointer_to_def_blocks);
    }
  }
  else {
    //printf("%s\n", "smething wrong entered in DefinitionBlocks !!!!!!!!!!!!!!!!!!!!!!!");
  }

};

void searchDefinitionBlockWithEnd(OperatorTypeClass* _def_block_w_end) {
  DefinitionBlockWithBraceCode* _b = dynamic_cast<DefinitionBlockWithBraceCode*>(_def_block_w_end);
  if (_b) {
    if (_b->brace_code_pointer != NULL) {
      //printf("%s -> ", _b->_node_name.c_str());
      searchBraceCode(_b->brace_code_pointer);
    }
    if (_b->block_pointer !=NULL) {
      //printf("%s -> ", _b->_node_name.c_str());
      searchDefinitionBlock(_b->block_pointer);
    }
    if ((_b->block_pointer == NULL) && (_b->brace_code_pointer == NULL) ) {
      //printf("%s%s\n",_b->_node_name.c_str(),"_empty;");
    }
  }
};

void searchBraceCode(TokenTypeClass* _brace_code) {
  BraceCode* _brace_code_p = dynamic_cast<BraceCode*>(_brace_code);
  if (_brace_code_p) {
    //printf("%s ;\n", _brace_code_p->returnName().c_str());
  } else {
    /// Не уверн пока надо ли сюда что-то запихивать
  }
};

void searchDefinitionBlock(OperatorTypeClass* _def_block){
  DefinitionBlockClass* _b = dynamic_cast<DefinitionBlockClass*>(_def_block);
  if (_b){
    if (_b->pointer_to_token != NULL) {
      //printf("%s -> ", _b->_node_name.c_str());
      searchToken(_b->pointer_to_token);
    }
    if (_b->pointer_to_def_block != NULL) {
      //printf("%s -> ", _b->_node_name.c_str());
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
    //printf("%s ;\n", _token_pointer->returnName().c_str());
  } 
  else {
    ///// additional block. Fill vector of variables
    Variable* _var_p = dynamic_cast<Variable*>(_token);
    search_functions_data.var_vector_for_additional_connections.push_back(_var_p);
    /////
    searchVariable(_token);
  }
};
