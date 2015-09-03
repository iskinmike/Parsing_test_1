struct NodeStruct;
struct RuleStruct;
struct VariableStruct;

struct NodeStruct
{
	int i;
	std::string _name; // По сути это lable
	std::string _node_uniq_name; // Уникальное имя
	std::vector<RuleStruct*> _ruleStructs;
	NodeStruct(){};
	NodeStruct(std::string name){ _name = name; };
	NodeStruct(std::string name,
				std::string node_uniq_name
				)
	{ 
		_name = name;
		_node_uniq_name=node_uniq_name
	};
};

struct  RuleStruct
{
	std::string _name;
	std::string _rule_uniq_name;
	std::vector<VariableStruct*> _variableStructs;
	RuleStruct(std::string name){ _name = name; };
};

struct VariableStruct
{
	std::string _name;
	std::string _variable_uniq_name;
	std:;string _node_name; // Имя Элемента NodeStruct на который будем ссылаться 
	NodeStruct* _node;

	VariableStruct(std::string name){ _name = name; };
};
