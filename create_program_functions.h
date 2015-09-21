/* create_program_functions.h */
void generateProgramCode(std::string file_path);
void generateProgramCodeFromNode(NodeStruct* _node);
void generateProgramCodeFromRule(RuleStruct* _rule);
void generateProgramCodeFromVariable(VariableStruct* _variable);
void printProgramCodeFromNode(NodeStruct* _node);
void printProgramCodeFromRule(RuleStruct* _rule);
void printProgramCodeFromVariable(VariableStruct* _variable);