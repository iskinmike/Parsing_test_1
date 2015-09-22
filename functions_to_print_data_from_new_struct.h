
void printAllDataFromNewStruct(std::string file_path, std::vector<std::string> massive_of_tokens);

void printNodeData(NodeStruct* _node, std::vector<std::string> *massive_of_tokens);
void printRuleData(RuleStruct* _rule, std::vector<std::string> *massive_of_tokens);
void printVariableData(VariableStruct* _variable, RuleStruct* _rule, int _pos, std::vector<std::string> *massive_of_tokens);

void printNodeLable(NodeStruct* _node);
void printRuleLable(RuleStruct* _rule);
void printVariableLable(VariableStruct* _variable, RuleStruct* _rule, int _pos);