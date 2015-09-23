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

GlobalDataStorage& generate_functions_data = GlobalDataStorage::Instance(); // Возможно не понадобится

//// Нужна функция проверки пустого правила. Первое правило проверяем пустое оно или нет.
bool isRuleEmpty(RuleStruct* _rule){
  if (_rule->_variable.size() != 0) return true;
  else return false;
}

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
}

void generateProgramCode(std::string file_path){
	srand(time(NULL));
	// Будет программа 
	// которая генерирует нам карту или вектор из объектов SettingsStruct
	//generateSettingsStruct();

	connectWithDll();

	printProgramCodeFromNode(generate_functions_data.node_struct_vector[0]);
	
	closeConnectionWithDll();
	clearAllDynamicData();

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