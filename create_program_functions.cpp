#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <time.h>
#include <math.h>
#include <stack>
#include <string> 
#include "class_struct.h"
#include "new_struct_for_program.h"
//#include "settings_struct.h"
#include "singleton_data_struct.h"
#include "create_program_functions.h"
#include "generation_control.h"



// Здесь начнем динамически подключать нашу библиотеку
// чтобы получить функцию sendRequestToDll();
// 

#include <dlfcn.h>

void *ext_library;	// хандлер внешней библиотеки
char *error;
AnswerNodeInformation* (*sendRequestToController)(RequestNodeInformation*); // переменная для хранения адреса функции


void connectWithDll(){
	//загрузка библиотеки
	ext_library = dlopen("./token_generator/libtoken_generator.so",RTLD_LAZY);
	if (!ext_library){
		//если ошибка, то вывести ее на экран
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		return;
	};
	//загружаем из библиотеки требуемую процедуру	
	sendRequestToController = (AnswerNodeInformation* (*)(RequestNodeInformation*)) dlsym(ext_library, "sendRequestToDll");
	if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        return;
    }
}
void closeConnectionWithDll(){
	dlclose(ext_library);
}

////////////////////////////////////////////////
void startFunctionTest(){
	printf("%s\n","test");
}

#define DONT_DO_ANYTHING_SPECIAL 0
#define THIS_FUNCTION_WAS_CALLED_RECENTLY 1
#define THIS_FUNCTION_DO_SPECIAL_THINGS 2

#define WITHOUT_RULES 0
#define ONE_RULE 1
#define TWO_RULES 2
#define THREE_RULES 3

#define FIRST_RULE 0
#define SECOND_RULE 1





std::string global_string_with_program;
std::string global_first_path_program("");
std::string global_first_path_repeat_program("");
std::string global_repeated_program_collection("");

std::map<std::string, std::vector<bool> > map_of_visited_rules;
// Нужна функция заполняющая эту карту
std::string returnIntToString(int number);

GlobalDataStorage& generate_functions_data = GlobalDataStorage::Instance(); // Возможно не понадобится

bool isNodeWithClosure(NodeStruct* _node);
bool isRuleEmpty(RuleStruct* _rule);
RuleStruct* generateRuleFromMapOfVisitedNodes(NodeStruct* _node);

void calculateVariants(){
	std::vector<int> count_of_variants;
	for (int i = 0; i < generate_functions_data.node_struct_vector.size(); ++i)
	{
		count_of_variants.push_back(generate_functions_data.node_struct_vector[i]->_rule.size());
	}
	int _sum =0;
	long long _mult = 1;
	for (int i = 0; i < count_of_variants.size(); ++i)
	{
		_sum = _sum + count_of_variants[i];
		_mult = _mult * count_of_variants[i];
		printf("%d * ",count_of_variants[i]);
	}
	printf("\n %lld\n", _mult );
	printf("%d\n", _sum );
};

void printMapOfVisitedRules(){
	for (auto i = map_of_visited_rules.begin(); i != map_of_visited_rules.end(); ++i)
	{
		printf("%s: ", i->first.c_str());
		for (int j = 0; j < i->second.size(); ++j)
		{
			printf("%d ",(int) i->second[j]);
		}
		printf("%s\n ","");
	}
};
void setupMapOfVisitedRules(){
	for (int i = 0; i < generate_functions_data.node_struct_vector.size(); ++i)
	{
		NodeStruct* temp_node = generate_functions_data.node_struct_vector[i];
		// define temp_node for easier typing
		std::vector<bool> temp_mass_of_visited_rules(temp_node->_rule.size(),false);
		map_of_visited_rules[temp_node->_name] = temp_mass_of_visited_rules;
	}

	//printMapOfVisitedRules();	
};



struct PathTrougthTheGraph
{
	NodeStruct* _node;
	RuleStruct* _rule;
};

std::vector<PathTrougthTheGraph> first_path;

void prinFirstPath(){
	printf("%s\n","First Path");
	for (int i = 0; i < first_path.size(); ++i)
	{
		printf("%s: %s\n",first_path[i]._node->_name.c_str(),first_path[i]._rule->_name.c_str());
	}
};
//PathTrougthTheGraph *first_path = new PathTrougthTheGraph[generate_functions_data.node_struct_vector.size()];

bool areWeSeenThisNode(NodeStruct* _node){
	for (int i = 0; i < first_path.size(); ++i)
	{
		if (first_path[i]._node == _node){
			return true;
		}
	}
	return false;
};

bool isThisRuleHasClosure(RuleStruct* _rule){
	for (int i = 0; i < _rule->_variable.size(); ++i)
	{
		if (_rule->_variable[i]->_node != NULL){
			if (areWeSeenThisNode(_rule->_variable[i]->_node)) {
				return true;
			}
		}
	}
	return false;
};

#define RETURN_SPECIAL_RULE(opertaor_name, number_of_rule) \
	if (_node->_name.compare(opertaor_name) ==0) \
	{ return _node->_rule[number_of_rule];}


RuleStruct* findRulesWithoutClosure(NodeStruct* _node){
	std::vector<RuleStruct*> appropriate_rules;
	for (int i=0; i< _node->_rule.size(); i++){
		if ( (!isThisRuleHasClosure(_node->_rule[i])) && ( _node->_rule[i]->_variable.size()>0 ) )		
		{
			// Нужно правильно выбрать правила
			// Разорвать замыкания
			appropriate_rules.push_back(_node->_rule[i]);
			/* code */
		}
	}

	RETURN_SPECIAL_RULE("ARG",0);
	RETURN_SPECIAL_RULE("EXPR",0);
	RETURN_SPECIAL_RULE("OPERATOR",0);
	RETURN_SPECIAL_RULE("OPER",10);
/*
	if (_node->_name.compare("ARG") ==0)
	{
		return _node->_rule[0];
	}

if (_node->_name.compare("FUNCTIONS") ==0)
	{
		printf("%s\n","**------ Rrules**");
		for (int i = 0; i <_node->_rule.size() ; ++i)
		{
			printf("%s\n",_node->_rule[i]->_name.c_str());
		}
		printf("%s : %d\n","**APPR Rrules**",appropriate_rules.size());
		for (int i = 0; i < appropriate_rules.size(); ++i)
		{
			printf("%s ",appropriate_rules[i]->_name.c_str());
			printf("%d\n",appropriate_rules[i]->_variable.size());
		}
	}
*/
	RuleStruct* temp_rule;
	if (appropriate_rules.size() >0){
		temp_rule = appropriate_rules[rand()%appropriate_rules.size()];
	}
	else {
		temp_rule = _node->_rule[0];
	}
	return temp_rule;
};

void passWithBreakConnectionNode(NodeStruct* _node);
void passWithBreakConnectionRule(RuleStruct* _rule);
void passWithBreakConnectionVariable(VariableStruct* _variable);

void passWithBreakConnectionNode(NodeStruct* _node){
//
//
	PathTrougthTheGraph temp_struct;
	temp_struct._node = _node;
	//temp_struct._rule = choosen_rule;
	first_path.push_back(temp_struct);
	// идем в первый раз вглубь.
	// Есть глобальный first_path в него запишем какие узлы уже прошли 

	// Сначчала выбаерем по какому правилу пойдем
	// Нам нужно правило без обратной связи
	// Точнее нам нужно проверить не указывает ли оно на узелв котором мы уже были.
	// Для этого у нас есть структура первы_путь
/*
	global_first_path_program.append(" :");
	global_first_path_program.append(_node->_name);
	global_first_path_program.append(":\n");
*/
	RuleStruct* choosen_rule;
	choosen_rule = findRulesWithoutClosure(_node);
	// Нашли теперь запоминаем и идем по нему
	//temp_struct._rule = choosen_rule;
	auto i = first_path.end() - 1;
	(*i)._rule = choosen_rule;

	// Запомнили и идем по этому правилу
	passWithBreakConnectionRule(choosen_rule);
/*
	if (isNodeWithClosure(_node))
	{
		passWithBreakConnectionRule(_node->_rule[rand()%_node->_rule.size()]);
	}
	else {
		passWithBreakConnectionRule(_node->_rule[rand()%_node->_rule.size()]);
	}
*/
};
void passWithBreakConnectionRule(RuleStruct* _rule){
	int elements_count = _rule->_variable.size();
	if (elements_count > 0) {
		for (int i=0; i<elements_count; i++){
			passWithBreakConnectionVariable(_rule->_variable[i]);
		}
	}
};
void passWithBreakConnectionVariable(VariableStruct* _variable){
	if (_variable->_node != NULL) {
		passWithBreakConnectionNode(_variable->_node);
	}
	else{
		RequestNodeInformation _request;
		_request._name.assign(_variable->_name);

		AnswerNodeInformation* _answer;
		_answer = (*sendRequestToController)(&_request); // sendRequestToDll(&_request);

		std::string temp_str = _answer->_name;
		if (temp_str.compare("") == 0) {
	  		temp_str.assign(_variable->_name);
	  		temp_str = temp_str.substr(temp_str.find("'")+1);
	  		temp_str = temp_str.substr(0,temp_str.find("'"));
	  		if (temp_str.compare(";") == 0 ||
		  		temp_str.compare("{") == 0 ||
		  		temp_str.compare("}") == 0
		  	)
	  		{
	  			//printf("%s \n", temp_str.c_str());
	  			global_first_path_program.append(temp_str);
	  			global_first_path_program.append("\n");
	  		}
	  		else {
	  			//printf("%s ", temp_str.c_str());
	  			global_first_path_program.append(temp_str);
	  			global_first_path_program.append(" ");
	  		}
	  	}
	  	else {
	  		//printf("%s ", temp_str.c_str());
	  		global_first_path_program.append(temp_str);
	  		global_first_path_program.append(" ");
	  	}
	}
};

void passThroughCreatedPathNode(NodeStruct* _node);
void passThroughCreatedPathRule(RuleStruct* _rule);
void passThroughCreatedPathVariable(VariableStruct* _variable);

void passThroughCreatedPathNode(NodeStruct* _node){
	for (int i = 0; i < first_path.size(); ++i)
	{
		if (_node == first_path[i]._node){
			for (int j = 0; j < _node->_rule.size(); ++j)
			{
				if (_node->_rule[j] == first_path[i]._rule)
				{
					map_of_visited_rules[_node->_name][j]=true;
				}
			}
			passThroughCreatedPathRule(first_path[i]._rule);
			break;
		}
	}
};
void passThroughCreatedPathRule(RuleStruct* _rule){
	for (int i = 0; i < _rule->_variable.size(); ++i)
	{
		passThroughCreatedPathVariable(_rule->_variable[i]);
	}
};
void passThroughCreatedPathVariable(VariableStruct* _variable){
	if (_variable->_node != NULL) {
		passThroughCreatedPathNode(_variable->_node);
	}
	else{
		// Далее надо определить что перед нами Символ или Токен
		// 
		RequestNodeInformation _request;
		_request._name.assign(_variable->_name);

		AnswerNodeInformation* _answer;
		_answer = (*sendRequestToController)(&_request); // sendRequestToDll(&_request);

		std::string temp_str = _answer->_name;
		if (temp_str.compare("") == 0) {
	  		temp_str.assign(_variable->_name);
	  		temp_str = temp_str.substr(temp_str.find("'")+1);
	  		temp_str = temp_str.substr(0,temp_str.find("'"));
	  		if (temp_str.compare(";") == 0 ||
		  		temp_str.compare("{") == 0 ||
		  		temp_str.compare("}") == 0
		  	)
	  		{
	  			//printf("%s \n", temp_str.c_str());
	  			global_first_path_repeat_program.append(temp_str);
	  			global_first_path_repeat_program.append("\n");
	  		}
	  		else {
	  			//printf("%s ", temp_str.c_str());
	  			global_first_path_repeat_program.append(temp_str);
	  			global_first_path_repeat_program.append(" ");
	  		}
	  	}
	  	else {
	  		//printf("%s ", temp_str.c_str());
	  		global_first_path_repeat_program.append(temp_str);
	  		global_first_path_repeat_program.append(" ");
	  	}
	}
};

void passProgramVersionOne(){
/*
	for (int i = 0; i < first_path.size(); ++i)
	{
		first_path
	}
*/
	passThroughCreatedPathNode(first_path[0]._node);
	printf("%s\n",global_first_path_repeat_program.c_str() );
};

//global_repeated_program_collection
/////////////////////   ФУНКЦИИ ОБЕСПЕЧИВАЮЩИЕ ГЕНЕРАЦИЮ БОЛЬШОГО КОЛИЧЕСТВА ПРОГРАММ
RuleStruct* generateRuleFromMapOfVisitedNodes(NodeStruct* _node){
	RuleStruct* temp_rule;
	std::vector<RuleStruct*> appropriate_rules;

	for (int i = 0; i < _node->_rule.size(); ++i)
	{
		if (!map_of_visited_rules[_node->_name][i])
		{
			appropriate_rules.push_back(_node->_rule[i]);
		}
	}
	if (appropriate_rules.size()>0){
		temp_rule = appropriate_rules[rand()%appropriate_rules.size()];
	}
	else{
		temp_rule = _node->_rule[0];
	}
	return temp_rule;
};
// Функция записывает пройденное правило а если узла еще не было в карте запишет его в карту и пометит правило
void writeChoosenRuleIntoMapOfVisitedNodes(NodeStruct* _node, RuleStruct* _rule){
	if (map_of_visited_rules.count(_node->_name)){
		for (int i = 0; i < _node->_rule.size(); ++i)
		{
			if (_node->_rule[i] == _rule){
				map_of_visited_rules[_node->_name][i] = true; // Visited
				break;
			}
		}
	}
	else {
		std::vector<bool> temp_mass_of_visited_rules(_node->_rule.size(),false);
		map_of_visited_rules[_node->_name] = temp_mass_of_visited_rules;
		for (int i = 0; i < _node->_rule.size(); ++i)
		{
			if (_node->_rule[i] == _rule){
				map_of_visited_rules[_node->_name][i] = true; // Visited
				break;
			}
		}
	}
};
bool isNodeWasInFirstPath(NodeStruct* _node){
	for (int i = 0; i < first_path.size(); ++i)
	{
		if (first_path[i]._node == _node)
		{
			return true;
		}
	}
	return false;
};
bool isAllRulesVisitedInThisNode(NodeStruct* _node){
	std::vector<bool> temp_mass_of_visited_rules;
	temp_mass_of_visited_rules = map_of_visited_rules[_node->_name];
	for (int i = 0; i < temp_mass_of_visited_rules.size(); ++i)
	{
		if (!temp_mass_of_visited_rules[i])
		{
			return false;
		}
	}
	return true;
};
RuleStruct* getRuleFromFirstPath(NodeStruct* _node){
	for (int i = 0; i < first_path.size(); ++i)
	{
		if (first_path[i]._node == _node)
		{
			return first_path[i]._rule;
		}
	}
	return _node->_rule[0]; // Заглушка не должно такого быть
};

//////////////////////////////////////////////////////////
void passByPathWithChangesInRulesNode(NodeStruct* _node);
void passByPathWithChangesInRulesRule(RuleStruct* _rule);
void passByPathWithChangesInRulesVariable(VariableStruct* _variable);
void passByRefrencesNode(NodeStruct* _node);
void passByRefrencesRule(RuleStruct* _rule);
void passByRefrencesVariable(VariableStruct* _variable);
void passByPathWithoutChangesNode(NodeStruct* _node);
void passByPathWithoutChangesRule(RuleStruct* _rule);
void passByPathWithoutChangesVariable(VariableStruct* _variable);

void passByPathWithChangesInRulesNode(NodeStruct* _node){
	for (int i = 0; i < first_path.size(); ++i)
	{
		if (_node == first_path[i]._node){
			for (int j = 0; j < _node->_rule.size(); ++j)
			{
				if (_node->_rule[j] == first_path[i]._rule)
				{
					map_of_visited_rules[_node->_name][j]=true;
				}
			}
			// Сделаем такую переменную, чтобы для всех вызовов функции она хранилась
			static int position_in_path = 1;
			if (i == first_path.size() - position_in_path)
			{
				// Раз дошли до последнего участка
				// Тепеь сначала определим, какое правило будем использовать
				RuleStruct* temp_rule = generateRuleFromMapOfVisitedNodes(_node);
				// Тпереь записали в карту выбранное правило
				writeChoosenRuleIntoMapOfVisitedNodes(_node, temp_rule);
				// теперь нужно перейти в особую прогррамму с этим правилом
				// которая вызовет функции чтобы мы дальше шли как придется по связям
				// А не по пути  
				if ( isAllRulesVisitedInThisNode(_node))/* если в карте пути по этому знаку все правила посещены */
				 {
				 	position_in_path++;
				 } 
				passByRefrencesRule(temp_rule);
				// При том раз дошли до конца то разываем путь.
				// В том смысле что не идем дальше по пути а идем по связям
				break;
			}
			else {
				passByPathWithChangesInRulesRule(first_path[i]._rule);
			}
			break;
		}
	}
};
void passByPathWithChangesInRulesRule(RuleStruct* _rule){
	for (int i = 0; i < _rule->_variable.size(); ++i)
	{
		passByPathWithChangesInRulesVariable(_rule->_variable[i]);
	}
};
void passByPathWithChangesInRulesVariable(VariableStruct* _variable){
	if (_variable->_node != NULL) {
		passByPathWithChangesInRulesNode(_variable->_node);
	}
	else{
		// Далее надо определить что перед нами Символ или Токен
		// 
		RequestNodeInformation _request;
		_request._name.assign(_variable->_name);

		AnswerNodeInformation* _answer;
		_answer = (*sendRequestToController)(&_request); // sendRequestToDll(&_request);

		std::string temp_str = _answer->_name;
		if (temp_str.compare("") == 0) {
	  		temp_str.assign(_variable->_name);
	  		temp_str = temp_str.substr(temp_str.find("'")+1);
	  		temp_str = temp_str.substr(0,temp_str.find("'"));
	  		if (temp_str.compare(";") == 0 ||
		  		temp_str.compare("{") == 0 ||
		  		temp_str.compare("}") == 0
		  	)
	  		{
	  			//printf("%s \n", temp_str.c_str());
	  			global_repeated_program_collection.append(temp_str);
	  			global_repeated_program_collection.append("\n");
	  		}
	  		else {
	  			//printf("%s ", temp_str.c_str());
	  			global_repeated_program_collection.append(temp_str);
	  			global_repeated_program_collection.append(" ");
	  		}
	  	}
	  	else {
	  		//printf("%s ", temp_str.c_str());
	  		global_repeated_program_collection.append(temp_str);
	  		global_repeated_program_collection.append(" ");
	  	}
	}
};

void passByRefrencesNode(NodeStruct* _node){
	// Попали сюда
	// Здесь просто идем по ссылкам но
	// будет развилка которая определит идем дальше по ссылкам или нет

	// Первое что мы должны сделать - проверить были ли мы уже здесь
	// т.е. сравнить _node с узлами в пути и если мы здесь были пререходим к проходу по уже пройденному пути
	if (isNodeWasInFirstPath(_node))
	 {
	 	// Если мы были здесь то прыгаем на путь
	 	RuleStruct* temp_rule = getRuleFromFirstPath(_node);
	 	// Выбрали правило и переходим на путь
	 	passByPathWithoutChangesRule(temp_rule);
	 }
	 else{
	 	// Иначе просто идем по ссылкам выбирая случайные правила и записывая их в карту посещенных
	 	// Тепеь сначала определим, какое правило будем использовать
		RuleStruct* temp_rule = generateRuleFromMapOfVisitedNodes(_node);
		// Тпереь записали в карту выбранное правило
		writeChoosenRuleIntoMapOfVisitedNodes(_node, temp_rule);
		/// ?????????????????????????/ Тут надо подумать как быть если еще ни разу не были в этом месте
		passByRefrencesRule(temp_rule);
	 }
};
void passByRefrencesRule(RuleStruct* _rule){
	for (int i = 0; i < _rule->_variable.size(); ++i)
	{
		passByRefrencesVariable(_rule->_variable[i]);
	}
};
void passByRefrencesVariable(VariableStruct* _variable){
	if (_variable->_node != NULL) {
		passByRefrencesNode(_variable->_node);
	}
	else{
		// Далее надо определить что перед нами Символ или Токен
		// 
		RequestNodeInformation _request;
		_request._name.assign(_variable->_name);

		AnswerNodeInformation* _answer;
		_answer = (*sendRequestToController)(&_request); // sendRequestToDll(&_request);

		std::string temp_str = _answer->_name;
		if (temp_str.compare("") == 0) {
	  		temp_str.assign(_variable->_name);
	  		temp_str = temp_str.substr(temp_str.find("'")+1);
	  		temp_str = temp_str.substr(0,temp_str.find("'"));
	  		if (temp_str.compare(";") == 0 ||
		  		temp_str.compare("{") == 0 ||
		  		temp_str.compare("}") == 0
		  	)
	  		{
	  			//printf("%s \n", temp_str.c_str());
	  			global_repeated_program_collection.append(temp_str);
	  			global_repeated_program_collection.append("\n");
	  		}
	  		else {
	  			//printf("%s ", temp_str.c_str());
	  			global_repeated_program_collection.append(temp_str);
	  			global_repeated_program_collection.append(" ");
	  		}
	  	}
	  	else {
	  		//printf("%s ", temp_str.c_str());
	  		global_repeated_program_collection.append(temp_str);
	  		global_repeated_program_collection.append(" ");
	  	}
	}
};

void passByPathWithoutChangesNode(NodeStruct* _node){
	for (int i = 0; i < first_path.size(); ++i)
	{
		if (_node == first_path[i]._node){
			for (int j = 0; j < _node->_rule.size(); ++j)
			{
				if (_node->_rule[j] == first_path[i]._rule)
				{
					map_of_visited_rules[_node->_name][j]=true;
				}
			}
			passByPathWithoutChangesRule(first_path[i]._rule);
			break;
		}
	}
};
void passByPathWithoutChangesRule(RuleStruct* _rule){
	for (int i = 0; i < _rule->_variable.size(); ++i)
	{
		passByPathWithoutChangesVariable(_rule->_variable[i]);
	}
};
void passByPathWithoutChangesVariable(VariableStruct* _variable){
	if (_variable->_node != NULL) {
		passByPathWithoutChangesNode(_variable->_node);
	}
	else{
		// Далее надо определить что перед нами Символ или Токен
		// 
		RequestNodeInformation _request;
		_request._name.assign(_variable->_name);

		AnswerNodeInformation* _answer;
		_answer = (*sendRequestToController)(&_request); // sendRequestToDll(&_request);

		std::string temp_str = _answer->_name;
		if (temp_str.compare("") == 0) {
	  		temp_str.assign(_variable->_name);
	  		temp_str = temp_str.substr(temp_str.find("'")+1);
	  		temp_str = temp_str.substr(0,temp_str.find("'"));
	  		if (temp_str.compare(";") == 0 ||
		  		temp_str.compare("{") == 0 ||
		  		temp_str.compare("}") == 0
		  	)
	  		{
	  			//printf("%s \n", temp_str.c_str());
	  			global_repeated_program_collection.append(temp_str);
	  			global_repeated_program_collection.append("\n");
	  		}
	  		else {
	  			//printf("%s ", temp_str.c_str());
	  			global_repeated_program_collection.append(temp_str);
	  			global_repeated_program_collection.append(" ");
	  		}
	  	}
	  	else {
	  		//printf("%s ", temp_str.c_str());
	  		global_repeated_program_collection.append(temp_str);
	  		global_repeated_program_collection.append(" ");
	  	}
	}
};

/////////////////////// ФУНКЦИИ ПОИСКА УЗЛА ССЫЛАЮЩЕГОСЯ НА ИСКОМЫЙ УЗЕЛ
void findRefrenceToSpecificNode_Node(NodeStruct* _node, PathTrougthTheGraph specific_point);
void findRefrenceToSpecificNode_Rule(RuleStruct* _rule, PathTrougthTheGraph specific_point);
void findRefrenceToSpecificNode_Variable(VariableStruct* _variable, PathTrougthTheGraph specific_point);

void findRefrenceToSpecificNode_Node(NodeStruct* _node, PathTrougthTheGraph specific_point){
	for (int i = 0; i < first_path.size(); ++i)
	{
		if (_node == first_path[i]._node){
			if (_node == specific_point._node)
			{
				// Нужно в карту записатьчто мы были тут
				writeChoosenRuleIntoMapOfVisitedNodes(specific_point._node, specific_point._rule);
				passByRefrencesRule(specific_point._rule); 
				break;
			}
			else{
				writeChoosenRuleIntoMapOfVisitedNodes(first_path[i]._node, first_path[i]._rule);
				findRefrenceToSpecificNode_Rule(first_path[i]._rule, specific_point);
				break;
			}
		}
	}
};
void findRefrenceToSpecificNode_Rule(RuleStruct* _rule, PathTrougthTheGraph specific_point){
	for (int i = 0; i < _rule->_variable.size(); ++i)
	{
		findRefrenceToSpecificNode_Variable(_rule->_variable[i], specific_point);
	}
};
void findRefrenceToSpecificNode_Variable(VariableStruct* _variable, PathTrougthTheGraph specific_point){
	if (_variable->_node != NULL) {
		findRefrenceToSpecificNode_Node(_variable->_node, specific_point);
	}
	else{
		// Далее надо определить что перед нами Символ или Токен
		// 
		RequestNodeInformation _request;
		_request._name.assign(_variable->_name);

		AnswerNodeInformation* _answer;
		_answer = (*sendRequestToController)(&_request); // sendRequestToDll(&_request);

		std::string temp_str = _answer->_name;
		if (temp_str.compare("") == 0) {
	  		temp_str.assign(_variable->_name);
	  		temp_str = temp_str.substr(temp_str.find("'")+1);
	  		temp_str = temp_str.substr(0,temp_str.find("'"));
	  		if (temp_str.compare(";") == 0 ||
		  		temp_str.compare("{") == 0 ||
		  		temp_str.compare("}") == 0
		  	)
	  		{
	  			//printf("%s \n", temp_str.c_str());
	  			global_repeated_program_collection.append(temp_str);
	  			global_repeated_program_collection.append("\n");
	  		}
	  		else {
	  			//printf("%s ", temp_str.c_str());
	  			global_repeated_program_collection.append(temp_str);
	  			global_repeated_program_collection.append(" ");
	  		}
	  	}
	  	else {
	  		//printf("%s ", temp_str.c_str());
	  		global_repeated_program_collection.append(temp_str);
	  		global_repeated_program_collection.append(" ");
	  	}
	}
};

// Нужна функция "Вернуть Мне Узел и правило которые ссылаеются на имя искомого узла
PathTrougthTheGraph returnNodeAndRuleRefrenToSearchedNode(std::string searched_node){
	// Запилим сначала структуру которую будем возвращать
	PathTrougthTheGraph temp_path_point;
	// Даллее надо бы этоу структуру заполнить
	// Все очень просто, нужно только 2 цикла
	// первый цикл перебирает узлы из первого пути
	for (int pos_of_node = 0; pos_of_node < first_path.size(); ++pos_of_node)
	{
		// Второй будет перебирать все правила этих узлов в пути
		for (int pos_of_rule = 0; pos_of_rule < first_path[pos_of_node]._node->_rule.size(); ++pos_of_rule)
		{
			// В этом цикле мы будем смотреть как у нас дела с ссылкой на искомый узел
			// Но вот блин у нас эти ссылки хранятся в векторе переменных для каждого правила
			// Поэтому третьим циклом надо каждую из них проглядеть на предмет ссылки на узлы
			// И если таковая имеется посмотреть на искомый узел ссыается или нет
			RuleStruct* temp_rule = first_path[pos_of_node]._node->_rule[pos_of_rule];
			for (int pos_of_variable = 0; pos_of_variable < temp_rule->_variable.size(); ++pos_of_variable)
			{
				// Так а теперь уже точно начинаем проверять 
				// сначала есть ли ссылка на узел
				if (temp_rule->_variable[pos_of_variable]->_node != NULL)
				{
					// Теперь если уж у нас есть ссылка на узел смотрим тот ли еэто узел
					if (searched_node.compare(temp_rule->_variable[pos_of_variable]->_node->_name) == 0 )
					{
						// А что мы собственно теперь должны сделать?
						if (isNodeWasInFirstPath(temp_rule->_variable[pos_of_variable]->_node))
						{
							// Немного по другому сделаем Мы вернем узел который хотим посетить, его имя.
							// и вернем правио сгенерированное из карты
							temp_path_point._node = temp_rule->_variable[pos_of_variable]->_node;
							temp_path_point._rule = generateRuleFromMapOfVisitedNodes(temp_rule->_variable[pos_of_variable]->_node);
						}
						else {
							// Наверное надо записать в нашу структуру узел first_path[pos_of_node]._node
							// И записать в нее правило                     temp_rule
							temp_path_point._node = first_path[pos_of_node]._node;
							temp_path_point._rule = temp_rule;
						}
						return temp_path_point;
					}
				}
			}
		}
	}
	temp_path_point._node = NULL;
	return temp_path_point;
};
bool isMapOfVisitedRulesCompleted(){
	// Сначала пробегаем все ключи
	for (auto i = map_of_visited_rules.begin(); i != map_of_visited_rules.end(); ++i)
	{
		// Каждому ключу соответствует вектор
		// теперь пробегаем каждый вектор
		for (int pos_in_vector = 0; pos_in_vector < i->second.size(); ++pos_in_vector)
		{
			if (!i->second[pos_in_vector])
			{
				return false;
			}
		}
	}
	return true;
};
std::string returnNameOfNotCompletedNode(){
	std::string temp_str("empty_string_it_is_result_of_wrong_data");
	// Сначала пробегаем все ключи
	for (auto i = map_of_visited_rules.begin(); i != map_of_visited_rules.end(); ++i)
	{
		// Каждому ключу соответствует вектор
		// теперь пробегаем каждый вектор
		for (int pos_in_vector = 0; pos_in_vector < i->second.size(); ++pos_in_vector)
		{
			if (!i->second[pos_in_vector])
			{
				return i->first;
			}
		}
	}
	return temp_str;
};



/////////////////////// 

void generateProgramsWithPassedPath(){

	// Пока в карте посещенных есть еще не посещенные - генерируем программы

	printf("%s\n","****************** Global Program Collection ******************" );
	for (int i = 0; i < 68; ++i)
	{
		global_repeated_program_collection.append("Program_");
		global_repeated_program_collection.append(returnIntToString(i));
		global_repeated_program_collection.append("\n"); 
		passByPathWithChangesInRulesNode(first_path[0]._node);
		printf("---------------------- %s %d -----------------\n", "Map of the path",i);
		//printMapOfVisitedRules();
	}
	// Забавная такая штука
	// короче нужно крутить пока в карте есть хотя бы 1 непосещенный
	printMapOfVisitedRules();
	while (!isMapOfVisitedRulesCompleted()){
		// Мы ищем специальную точку в которую точно надо попасть
		printf("%s\n","entered into while loop" );
		std::string searched_node = returnNameOfNotCompletedNode();
		printf("%s\n",searched_node.c_str() );
		PathTrougthTheGraph specific_point = returnNodeAndRuleRefrenToSearchedNode(searched_node);
		printf("%s: %s \n",specific_point._node->_name.c_str(),specific_point._rule->_name.c_str() );
		findRefrenceToSpecificNode_Node(first_path[0]._node, specific_point);
	};

	printf("%s\n","*************** Start Global Program Collection ***************" );
	printf("%s\n",global_repeated_program_collection.c_str() );
	printMapOfVisitedRules();
	printf("%s\n","************** End Of Global Program Collection ***************" );
};


//// Нужна функция проверки пустого правила. Первое правило проверяем пустое оно или нет.
bool isRuleEmpty(RuleStruct* _rule){
  if (_rule->_variable.size() != 0) return true;
  else return false;
};
bool isNodeWithClosure(NodeStruct* _node) { /// Впоследствии надо будет переделать под 
	for (int i = 0; i < _node->_rule.size(); ++i)
	{
		for (int j = 0; j < _node->_rule[i]->_variable.size(); ++j)
		{
			if (_node->_rule[i]->_variable[j]->_node != NULL){
				return true;
			}
		}
	}
	return false;
};
void printProgramCodeFromNode(NodeStruct* _node){
	RequestNodeInformation _request;
	_request._name.assign(_node->_name);

	AnswerNodeInformation* _answer;
	_answer = (*sendRequestToController)(&_request); //sendRequestToDll(&_request);
// Проверяем узел с замыканием или нет можно и внутри ДЛЛ проверять
	if (_answer->is_closure_operator)
	{// Зашли в узел, создали структуру с именем
		// Получили ответ, теперь с ним работаем
		// Смотри:
		if (_answer->is_stop){
			// Скорее всего придется выбрать пустое правило либо просто первое
			printProgramCodeFromRule(_node->_rule[0]);
		}
		else {
			// Здесь получается надо выбрать одно из правил
			// Нужно как-то отобразить что мы генерим 1/2/3/5/10 штук
			// Пока не знаю как
			// пусть снова рандомно
			// Ладно давайте более по-хитрому 
			printProgramCodeFromRule(_node->_rule[rand()%_node->_rule.size()]);
		}
	}
	else {
		// Просто выбираем рандомное правило
		printProgramCodeFromRule(_node->_rule[rand()%_node->_rule.size()]);
	}
};
void printProgramCodeFromRule(RuleStruct* _rule){
	int elements_count = _rule->_variable.size();
	if (elements_count > 0) {
		for (int i=0; i<elements_count; i++){
			printProgramCodeFromVariable(_rule->_variable[i]);
		}
	}
};
void printProgramCodeFromVariable(VariableStruct* _variable){
	if (_variable->_node != NULL) {
		printProgramCodeFromNode(_variable->_node);
	}
	else{
		// Далее надо определить что перед нами Символ или Токен
		// 
		RequestNodeInformation _request;
		_request._name.assign(_variable->_name);

		AnswerNodeInformation* _answer;
		_answer = (*sendRequestToController)(&_request); // sendRequestToDll(&_request);

		std::string temp_str = _answer->_name;
		if (temp_str.compare("") == 0) {
	  		temp_str.assign(_variable->_name);
	  		temp_str = temp_str.substr(temp_str.find("'")+1);
	  		temp_str = temp_str.substr(0,temp_str.find("'"));
	  		if (temp_str.compare(";") == 0 ||
		  		temp_str.compare("{") == 0 ||
		  		temp_str.compare("}") == 0
		  	)
	  		{
	  			//printf("%s \n", temp_str.c_str());
	  			global_string_with_program.append(temp_str);
	  			global_string_with_program.append("\n");
	  		}
	  		else {
	  			//printf("%s ", temp_str.c_str());
	  			global_string_with_program.append(temp_str);
	  			global_string_with_program.append(" ");
	  		}
	  	}
	  	else {
	  		//printf("%s ", temp_str.c_str());
	  		global_string_with_program.append(temp_str);
	  		global_string_with_program.append(" ");
	  	}
	}
};

void clearAllDynamicData(){
	//delete counter_of_block_code_invokes;
	//delete[] first_path;
}
void calculateVariantsOfFirstPath(){
	int sum_of_variants = 0;
	for (int i = 0; i < first_path.size(); ++i)
	{
		printf("%s: %d\n", first_path[i]._node->_name.c_str(), first_path[i]._node->_rule.size());
		sum_of_variants = sum_of_variants + first_path[i]._node->_rule.size();
	}
	printf("%d\n", sum_of_variants);

};

void generateProgramCode(std::string file_path){
	srand(time(NULL));
	// Будет программа 
	// которая генерирует нам карту или вектор из объектов SettingsStruct
	//generateSettingsStruct();

	//calculateVariants();
	setupMapOfVisitedRules();



	connectWithDll();

	passWithBreakConnectionNode(generate_functions_data.node_struct_vector[0]);
	printf("%s\n\n\n",global_first_path_program.c_str() );

	prinFirstPath();
	printf("%s\n\n","" );

	passProgramVersionOne();
	printMapOfVisitedRules();


	generateProgramsWithPassedPath();


	printProgramCodeFromNode(generate_functions_data.node_struct_vector[0]);
	
	closeConnectionWithDll();
	clearAllDynamicData();

	calculateVariantsOfFirstPath();

	if (file_path.compare("")==0){
		printf("%s\n",global_string_with_program.c_str() );
	}
	else {
		FILE * pointer_to_file;
		pointer_to_file = fopen(file_path.c_str(),"w+");
		if (pointer_to_file != NULL)
		{
			// Точно печать в файл
			fputs(global_string_with_program.c_str(),pointer_to_file);
		}
		else {
			printf("%s\n",global_string_with_program.c_str() );
		}
		fclose(pointer_to_file);
	}
}