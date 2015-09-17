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


GlobalDataStorage& generate_functions_data = GlobalDataStorage::Instance(); // Возможно не понадобится


//// Нужна функция проверки пустого правила. Первое правило проверяем пустое оно или нет.
bool isRuleEmpty(RuleStruct* _rule){
  if (_rule->_variable.size() != 0) return true;
  else return false;
}

/// Создадим глобальный Стэк. Куда будем записывать какие правила и сколько раз вызывали в этом операторе
// Не стэк а Структуру пока
/*
	class CounterOfBlockCodeInvokes{
		int code_depth_counter;
		int amount_of_allowed_code_operators;
	public:
		bool is_allowed_to_invoke_block_code;

		CounterOfBlockCodeInvokes(): 
			code_depth_counter(0),
			amount_of_allowed_code_operators(10),
			is_allowed_to_invoke_block_code(true)
		{};

		void invokeBlockCode(){
			code_depth_counter++;
			amount_of_allowed_code_operators--;
			if (!is_allowed_to_invoke_block_code && code_depth_counter<3 && amount_of_allowed_code_operators>0){
				is_allowed_to_invoke_block_code = true;
			}
			if (code_depth_counter>=3 || amount_of_allowed_code_operators<=0){
				is_allowed_to_invoke_block_code = false;
			}
			//printf("\nBlockCode: depth(%d) capacity(%d) is_allowed(%d) \n",code_depth_counter, amount_of_allowed_code_operators,is_allowed_to_invoke_block_code);
		}
		void closeBlockCode(){
			amount_of_allowed_code_operators--;
			code_depth_counter--;
			if (!is_allowed_to_invoke_block_code && code_depth_counter<3 && amount_of_allowed_code_operators>0){
				is_allowed_to_invoke_block_code = true;
			}
			if (code_depth_counter>=3 || amount_of_allowed_code_operators<=0){
				is_allowed_to_invoke_block_code = false;
			}
			//printf("\nBlockCode: depth(%d) capacity(%d) is_allowed(%d) \n",code_depth_counter, amount_of_allowed_code_operators,is_allowed_to_invoke_block_code);
		}
	};
*/


/*
	int returnPseudoRandomInInterval(int _begin, int _end){
		int temp_int;
		temp_int = rand()%(_end - _begin + 1) + _begin;
		return temp_int;
	};

	int returnPseudoRandomInIntervalWithOneMoreOftenNumber(
	int _begin, int _end, int percent, int value_of_spec_number)
	{
		std::vector<int> temp_vector;
		int temp_val=_begin;
		for (int i=0;i<(_end-_begin+1);i++){
			if (temp_val==value_of_spec_number) {
				// Пока ничего не делаем
				//temp_val++;
			}
			else{
				temp_vector.push_back(temp_val);
			}
			temp_val++;
		}
		int temp_int;
		temp_int = rand()%101;
		if (temp_int >=0 && temp_int < percent){
			temp_int=value_of_spec_number;
		}
		else {
			temp_int = rand()%(_end - _begin);
			temp_int = temp_vector[temp_int];
		}
		return temp_int;
	};

	bool isRefrenceToNodeInRules(NodeStruct* _node){
		if (_node->_rule.size() != 0) {
			for (int i=0; i<_node->_rule.size(); i++ ){
				if (_node->_rule[i]->_variable.size() >0){
					if (_node->_rule[i]->_variable[0]->_node == _node) { // Пока сделаем так чтобы не учитывать сразу все ошибки а они точно будут
						return true;
					}
				}
			}
		}
		return false;
	}

	bool isRefrenceToNodeInRule(RuleStruct* _rule, NodeStruct* _node){
		// заходим в правило
		/// смотрим элементы
		// Возвращаем тру если есть ссылка на узел
		// если ничего не нашли то вернем фолс
		int elements_count = _rule->_variable.size();
		for (int i=0; i<elements_count; i++) {
			if (_rule->_variable[i]->_node == _node){
				return true;
			}
		}
		return false;
	}

	bool isRefrenceToBlockCodeInRule(RuleStruct* _rule){
		int elements_count = _rule->_variable.size();
		for (int i=0; i<elements_count; i++) {
			if (_rule->_variable[i]->_name.compare("BLOCK_CODE") == 0){
				return true;
			}
		}
		return false;
	}
*/

//std::vector<RuleStruct*> constructVectorOfRulesWithoutBlockCode()

/*
	void generateProgramCodeFromNode(NodeStruct* _node){
		// Смотрим правила. Если есть.
		static int special_condition_flag = DONT_DO_ANYTHING_SPECIAL;
		int rules_count = _node->_rule.size();
		//printf("node: %s\n", _node->_name.c_str());
		if (rules_count >0){
			/// Составим список правил с ссылками
			std::vector<RuleStruct*> rules_with_refrence_to_this_node;
			std::vector<RuleStruct*> rules_without_refrence;
			for (int i=0; i<rules_count; i++){
				// Заполняем список
				if ( isRefrenceToNodeInRule(_node->_rule[i], _node) ){
					// Записываем правило
					rules_with_refrence_to_this_node.push_back(_node->_rule[i]);
				}
				else {
					rules_without_refrence.push_back(_node->_rule[i]);
				}	
			}
			/// У нас пока только 1 особый случай это OPERATOR
			if (_node->_name.compare("OPERATOR") == 0){
				//  printf("\nnode: %s\n", _node->_name.c_str());
				/// Раз попали в оператор то 2 варианта либо мы делаем выбор из всех случайно
				/// либо нам приходится выбирать без вложенности
				
				std::vector<RuleStruct*> rules_without_block_code;
				for (int i=0; i<rules_count; i++){
					if (!isRefrenceToBlockCodeInRule(_node->_rule[i])){
						rules_without_block_code.push_back(_node->_rule[i]);
					}
				}

				if (counter_of_block_code_invokes->is_allowed_to_invoke_block_code){
					// Тогда выбираем из всех
					//printf("\n*** All node: %s\n", _node->_name.c_str());
					int random_rule = rand()% rules_count;
					generateProgramCodeFromRule(_node->_rule[random_rule]);
				}
				else {
					// Тогда выбираем только из тех где нет вложенного кода
					int random_rule = rand()% rules_without_block_code.size();
					//printf("\nOnly without BLOCK_CODE node: %s   %d\n", _node->_name.c_str(), random_rule);
					generateProgramCodeFromRule(rules_without_block_code[random_rule]);
				}
			}
			else{
				// Теперь смотрим установлен ли флаг Нужно сделать другую глобальную карту флагов
				if (special_condition_flag) {
					// То выбираем из тех правил которые не попали в список с обратными сылками 
					// Считаем что хотя бы 1 такое у нас всегда есть. пустое или нет не важно пока.
					int random_rule = rand()% rules_without_refrence.size();
					special_condition_flag = DONT_DO_ANYTHING_SPECIAL; /// Надо будет этот флаг переделать
					generateProgramCodeFromRule(rules_without_refrence[random_rule]);
				}
				else{
					if (rules_count == ONE_RULE){
						generateProgramCodeFromRule(_node->_rule[FIRST_RULE]);
					}
					
					int random_rule = rand()% rules_count;
					// Прогоним проверку входит наше случаеное правило в правила с ссылкой на этот узел
					// Если входит то устанавливаем флаг чтобы не вызывать  много раз 1 и тот же метод
					for (int i=0; i<rules_with_refrence_to_this_node.size();i++){
						if (_node->_rule[random_rule] == rules_with_refrence_to_this_node[i]) {
							special_condition_flag = THIS_FUNCTION_DO_SPECIAL_THINGS;
							break;
						}
					}
					/// Пока разделены не для удобства а потому что понадобятся позже
					if (rules_count == TWO_RULES){
						/// Выбираем случайное правило
						generateProgramCodeFromRule(_node->_rule[random_rule]);
					}
					if (rules_count >= THREE_RULES) {
						/// Выбираем случайное правило
						generateProgramCodeFromRule(_node->_rule[random_rule]);
					}
				}
			}
		}
	};
	void generateProgramCodeFromRule(RuleStruct* _rule){
		int elements_count = _rule->_variable.size();
		//printf("** %s", _rule->_name.c_str());
		//printAllRuleElements(_rule);
		if (elements_count > 0) {
			for (int i=0; i<elements_count; i++){
				generateProgramCodeFromVariable(_rule->_variable[i]);
			}
		}
		else {
			// Видимо пока ничего не делаем если пустое правило
			// 
		}
	};
	void generateProgramCodeFromVariable(VariableStruct* _variable){
		if (_variable->_name.compare("BLOCK_CODE") == 0){
			counter_of_block_code_invokes->invokeBlockCode();
		}
		if (_variable->_name.compare("\'}\'") == 0){
			counter_of_block_code_invokes->closeBlockCode();
		}
		if (_variable->_node != NULL) {
			generateProgramCodeFromNode(_variable->_node);
		}
		else{
			// Далее надо определить что перед нами Символ или Токен
			std::string temp_str = getToken(_variable->_name);
			if (temp_str.compare("") == 0) {
		  		temp_str.assign(_variable->_name);
		  		temp_str = temp_str.substr(temp_str.find("'")+1);
		  		temp_str = temp_str.substr(0,temp_str.find("'"));
		  		if (temp_str.compare(";") == 0 ||
			  		temp_str.compare("{") == 0 ||
			  		temp_str.compare("}") == 0  
			  	)
		  		{
		  			printf("%s \n", temp_str.c_str());
		  		}
		  		else {
		  			printf("%s ", temp_str.c_str());
		  		}
		  	}
		  	else {
		  		printf("%s ", temp_str.c_str());
		  	}
		}

	};
*/

// Получается у нас будет глобальная структура 
// Пусть это пока будет карта
// в которой будут Имя узла, либо его адрес 
// (адрес проще и быстрее, но не так хорошо читаем человеком, хотя хз)
// и будет указатель на соответствующую структуру
// 

/*	
#define SettingsStructMap std::map<NodeStruct*, SettingsStruct*>
SettingsStructMap map_of_settings_struct;
*/

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
/*
	// Зашли в узел хотим получить правило
	RuleStruct* temp_rule = map_of_settings_struct[_node]->generateRuleForNode();
	// Пока сделаем явно в программе вызов счетчика
	map_of_settings_struct[_node]->invokeOperatorCounter();
	printProgramCodeFromRule(temp_rule);
	map_of_settings_struct[_node]->closeOperatorAndChangeCounter();
*/
	RequestNodeInformation _request;
	_request._name.assign(_node->_name);

	AnswerNodeInformation* _answer;
	_answer = sendRequestToDll(&_request);
// Проверяем узел с замыканием или нет можно и внутри ДЛЛ проверять
	//if (isNodeWithClosure(_node))
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
		_answer = sendRequestToDll(&_request);


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
	  			printf("%s \n", temp_str.c_str());
	  		}
	  		else {
	  			printf("%s ", temp_str.c_str());
	  		}
	  	}
	  	else {
	  		printf("%s ", temp_str.c_str());
	  	}
	}
};

/*
void generateSettingsStruct(){
	generateArgsForConstructor();
	for (int i = 0; i < generate_functions_data.node_struct_vector.size(); ++i)
	{
		generate_functions_data.set_of_settings_structs.push_back(
			new SettingsStruct(
				&generate_functions_data.set_of_settings_structs,
				map_of_arguments_for_settings_constructor[generate_functions_data.node_struct_vector[i]])
		);
	}
	map_of_settings_struct;
	for (int i = 0; i < generate_functions_data.node_struct_vector.size(); ++i)
	{
		map_of_settings_struct[generate_functions_data.node_struct_vector[i]] 
			= generate_functions_data.set_of_settings_structs[i];
	}
};
*/

void clearAllDynamicData(){
	//delete counter_of_block_code_invokes;
}

void generateProgramCode(){
	srand(time(NULL));
	// Будет программа 
	// которая генерирует нам карту или вектор из объектов SettingsStruct
	//generateSettingsStruct();

	printProgramCodeFromNode(generate_functions_data.node_struct_vector[0]);

	clearAllDynamicData();
}