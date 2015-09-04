struct NodeStruct;
struct RuleStruct;
struct VariableStruct;

struct NodeStruct
{
	int i;
	std::string _name; // По сути это lable
	std::string _node_uniq_name; // Уникальное имя
	std::string _lable_data;
	std::vector<RuleStruct*> _rule;
	void printLable(){
		printf("%s [label=\"%s\"];\n", _node_uniq_name.c_str(), _name.c_str());
	};
	NodeStruct(){};
	NodeStruct(std::string name){ _name = name; };
	NodeStruct(std::string node_uniq_name,
				std::string lable_data
				)
	{ 
		_node_uniq_name = node_uniq_name;
		_lable_data=lable_data;
		// 
		_name = _lable_data.substr(_lable_data.find("\"")+1);
		_name = _name.substr(0,_name.find("\""));
	};
};

struct  RuleStruct
{
	std::string _name;
	std::string _rule_uniq_name;
	std::vector<VariableStruct*> _variable;
	RuleStruct(){};
	RuleStruct(std::string name){ _name = name; };
	void printLable(){
		printf("%s [label=\"%s\" shape=box,color=aquamarine,style=filled ];\n", _rule_uniq_name.c_str(), _name.c_str());
	};
};

struct VariableStruct
{
	std::string _name;
	std::string _variable_uniq_name;
	std::string _lable_data;
	std::string _node_name; // Имя Элемента NodeStruct на который будем ссылаться 
	NodeStruct* _node;

	VariableStruct(std::string lable_data){ 
		_lable_data = lable_data; 
		_node=NULL;
		_variable_uniq_name = 
			_lable_data.substr(0,_lable_data.find("\n")-2);
		_name = _lable_data.substr(
			_lable_data.find("\"") +1
			);
		_name = _name.substr(0,_name.find("\""));
	};
	void printLable(){
		printf("%s [label=\"%s\" shape=polygon,sides=5,color=lightblue,style=filled ];\n", _variable_uniq_name.c_str(), _name.c_str());
	};
};
