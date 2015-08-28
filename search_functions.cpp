#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>

#include <class_struct.h>
#include <search_functions.h>

void searchOPS(oper_type* _OPS) {
  operators* _b = dynamic_cast<operators*>(_OPS);
  if (_b) {
    for (auto i = _b->ops.begin(); i != _b->ops.end(); ++i) {
      searchOPS(*i);
    }
  } else {
    searchOP(_OPS);
  }
};

void searchOP(oper_type* _OP) {
  operator_class* _b = dynamic_cast<operator_class*>(_OP);
  searchVariable(_b->variable_pointer);  
  searchDefinitionBlocks(_b->definition_block_pointer);
};

void searchVariable(token_type* _variable) {
  variable* _var_p = dynamic_cast<variable*>(_variable);
}







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
      searchDefinitionBlockWithEnd(_def_blocks);
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