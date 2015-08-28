/* search_functions.h */

/// У нас узлы не одинаковые, поэтому для каждого типа узла сделаем свою функцию.
void searchOP(oper_type* _OP);
void searchOPS(oper_type* _OPS);
/// Их можно как одну использовать разницы нет, а хотя нет, есть. пока оставим так чтобы каждая была отдельно
void searchVariable(token_type* _variable);
void searchSymbol(token_type* _symbol);
void searchBraceCode(token_type* _brace_code);

void searchDefinitionBlocks(oper_type* _def_blocks);
void searchDefinitionBlockWithEnd(oper_type* _def_blocks);
void searchDefinitionBlock(oper_type* _def_blocks);

void searchToken(oper_type* _def_blocks);