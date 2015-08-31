#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>

#include <class_struct.h>
#include <search_functions.h>

oper_type* g_oper=NULL;

void setGlobalOperator(oper_type* _oper){
  g_oper= _oper;
};

operator_class* findInOPS(oper_type* _OPS){
  operators* _b = dynamic_cast<operators*>(_OPS);
  if (_b) {
    if (_b->pointer_to_OPS != NULL) {
      searchOPS(_b->pointer_to_OPS);
    }
    if (_b->pointer_to_OP != NULL) {
      //printf("%s -> ", _b->_node_name.c_str());
      operator_class* _d = dynamic_cast<operator_class*>(_b->pointer_to_OP);
      if (_d->variable_pointer != NULL){
        return _d;
      }
      //searchOP(_b->pointer_to_OP);
    }
  }
  return  NULL;
};

void findSameVariable(oper_type* start_OP, variable* searched_variable){
  std::string str_1, str_2;
  operator_class* finded_oper_p;
  finded_oper_p = findInOPS(start_OP);
  if (finded_oper_p != NULL){
    variable* finded_var_p = dynamic_cast<variable*>(finded_oper_p->variable_pointer);
    str_1 = searched_variable->returnName();
    str_2 = finded_var_p->returnName();
    if (str_1.compare(str_2) == 0) {
      _var_p->def_operator = finded_oper_p;
    }
  }
};


oper_type* findSameVarName(std::string searched_var_name){
  // Вызываем функцию для которая залезет в оп и будет искать пока не найдет или не упрется в нуль
  findVarNameInOP(g_oper, searched_var_name);


}

oper_type* findVarNameInOP(oper_type* _oper, std::string ser_name){
  operators* _b = dynamic_cast<operators*>(_oper);
  if (_b) {
    if (_b->pointer_to_OP != NULL) {
      operator_class* _d = dynamic_cast<operator_class*>(_b->pointer_to_OP);
      std::string str_1 = _d->variable_pointer->returnName();
      if (ser_name.compare(str_1) == 0){
        return _b->pointer_to_OP;
      }
    }
    if (_b->pointer_to_OPS != NULL) {
      findVarNameInOP(_b->pointer_to_OPS,ser_name);
    }
    else {return NULL;}

}


void searchOPS(oper_type* _OPS) {
  operators* _b = dynamic_cast<operators*>(_OPS);
  if (_b) {
    if (_b->pointer_to_OPS != NULL) {
      printf("%s -> ", _b->_node_name.c_str());
      searchOPS(_b->pointer_to_OPS);
    }
    if (_b->pointer_to_OP != NULL) {
      printf("%s -> ", _b->_node_name.c_str());
      searchOP(_b->pointer_to_OP);
    }
  } else {
    printf("%s\n", "operator type");
    searchOP(_OPS);
  }
};

void searchOP(oper_type* _OP) {
  operator_class* _b = dynamic_cast<operator_class*>(_OP);
  if (_b->variable_pointer != NULL){
    printf("%s -> ", _b->_node_name.c_str());
    searchVariable(_b->variable_pointer);
  }
  if (_b->definition_block_pointer != NULL){
    printf("%s -> ", _b->_node_name.c_str());
    searchDefinitionBlocks(_b->definition_block_pointer);
  }
};

void searchVariable(token_type* _variable) {
  variable* _var_p = dynamic_cast<variable*>(_variable);
  printf("%s ;\n", _var_p->returnName().c_str());
  findSameVariable(g_oper,_var_p);
}

void searchDefinitionBlocks(oper_type* _def_blocks) {
  definition_blocks_class* _b = dynamic_cast<definition_blocks_class*>(_def_blocks);
  if (_b) {
    if (_b->pointer_to_DEF_BLOCK_WITH_END){
      printf("%s -> ", _b->_node_name.c_str());
      searchDefinitionBlockWithEnd(_b->pointer_to_DEF_BLOCK_WITH_END);
    }
    if (_b->pointer_to_DEF_BLOCKS) {
      printf("%s -> ", _b->_node_name.c_str());
      searchDefinitionBlocks(_b->pointer_to_DEF_BLOCKS);
    }
  }
  else {printf("%s\n", "smething wrong entered in DefinitionBlocks !!!!!!!!!!!!!!!!!!!!!!!");}

};

void searchDefinitionBlockWithEnd(oper_type* _def_block_w_end) {
  definition_block_with_end_class* _b = dynamic_cast<definition_block_with_end_class*>(_def_block_w_end);
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

void searchBraceCode(token_type* _brace_code) {
  brace_code* _brace_code_p = dynamic_cast<brace_code*>(_brace_code);
  if (_brace_code_p) {
    printf("%s ;\n", _brace_code_p->returnName().c_str());
  } else {
    /// Не уверн пока надо ли сюда что-то запихивать
  }
};

void searchDefinitionBlock(oper_type* _def_block){
  definition_block_class* _b = dynamic_cast<definition_block_class*>(_def_block);
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

void searchToken(oper_type* _token_block){
  token_class* _b = dynamic_cast<token_class*>(_token_block);
  if (_b) {
    if (_b->_token != NULL){
      searchSymbol(_b->_token);
    }
  }
};

void searchSymbol(token_type* _token) {
  symbol* _token_pointer = dynamic_cast<symbol*>(_token);
  if (_token_pointer) {
    printf("%s ;\n", _token_pointer->returnName().c_str());
  } else {
    //
    searchVariable(_token);
  }
};

/*
  void searchDefinitionBlocks(oper_type* _def_blocks) {
  definition_blocks_class* _def_blocks_pointer = NULL;
  try
  	{
    _def_blocks_pointer =
    dynamic_cast<definition_blocks_class*>(_def_blocks);
  }
  catch (...) {	
  }  
  //
    if (_def_blocks_pointer) {
      for (auto i = _def_blocks_pointer->_definition_blocks.begin();
           i != _def_blocks_pointer->_definition_blocks.end(); ++i) {    	
        searchDefinitionBlocks(*i);
      }
    } else {  	
      //searchDefinitionBlockWithEnd(_def_blocks);
    }
  };


  void searchDefinitionBlockWithEnd(oper_type* _def_blocks) {
    definition_block_with_end_class* _def_block_with_end_pointer =
        dynamic_cast<definition_block_with_end_class*>(_def_blocks);
    if (_def_block_with_end_pointer) {
      // Нужно вызвать две функции для обработки Кода в скобках и  Определения
      // блока
      /// Они оба могут быть нулевыми
      if (_def_block_with_end_pointer->block_pointer) {
        searchDefinitionBlock(_def_block_with_end_pointer->block_pointer);
      }
      if (_def_block_with_end_pointer->brace_code_pointer) {
        searchBraceCode(_def_block_with_end_pointer->brace_code_pointer);
      }
    } else {
      //
    }
  };
  void searchDefinitionBlock(oper_type* _def_blocks) {
    definition_block_class* _def_block_pointer =
        dynamic_cast<definition_block_class*>(_def_blocks);
    if (_def_block_pointer) {
      // Просматриваем список и для каждого вызываем эту же функцию
      for (auto i = _def_block_pointer->_definition_block.begin();
           i != _def_block_pointer->_definition_block.end(); ++i) {
         _def_block_pointer->_definition_block.size() );
        searchDefinitionBlock(*i);
      }
    } else {
      //
      searchToken(_def_blocks);
    }
  };

  void searchBraceCode(token_type* _brace_code) {
    brace_code* _brace_code_p = dynamic_cast<brace_code*>(_brace_code);
    if (_brace_code_p) {
    } else {
    }
  };

  void searchToken(oper_type* _def_blocks) {
    token_class* _token_pointer = dynamic_cast<token_class*>(_def_blocks);
    if (_token_pointer) {
      searchSymbol(_token_pointer->_token);
    } else {
    }
  };

  void searchSymbol(token_type* _token) {
    symbol* _token_pointer = dynamic_cast<symbol*>(_token);
    if (_token_pointer) {
    } else {
      //
      searchVariable(_token);
    }
  };
*/