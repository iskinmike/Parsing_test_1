/* search_functions.h */

/// У нас узлы не одинаковые, поэтому для каждого типа узла сделаем свою функцию.
void searchOperator(OperatorTypeClass* _operator);
void searchOperators(OperatorTypeClass* _operators);
/// Их можно как одну использовать разницы нет, а хотя нет, есть. пока оставим так чтобы каждая была отдельно
void searchVariable(TokenTypeClass* _variable);
void searchSymbol(TokenTypeClass* _symbol);
void searchBraceCode(TokenTypeClass* _brace_code);

void searchDefinitionBlocks(OperatorTypeClass* _def_blocks);
void searchDefinitionBlockWithEnd(OperatorTypeClass* _def_block_w_end);
void searchDefinitionBlock(OperatorTypeClass* _def_block);

void searchToken(OperatorTypeClass* _token_block);

void searchSameVariables(OperatorTypeClass* start_OP);

void setGlobalOperator(OperatorTypeClass* _oper);
void createAdditionalConnections();