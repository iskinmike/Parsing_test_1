#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include "token_generator.h"
#include "generation_control.h"


int global_counter = 50;
std::vector<std::string> list_of_operators;
std::vector<std::string> list_of_closure_operators;


#define ADD_OPERATOR_INTO_THE_LIST(operator_name) \
	list_of_operators.push_back(operator_name);

#define ADD_OPERATOR_INTO_THE_CLOSURE_LIST(operator_name) \
	list_of_closure_operators.push_back(operator_name);

void generateOperatorsList(){
	ADD_OPERATOR_INTO_THE_LIST("PROGRAM");
	ADD_OPERATOR_INTO_THE_LIST("FUNCTIONS");
	ADD_OPERATOR_INTO_THE_LIST("FUNCTION");
	ADD_OPERATOR_INTO_THE_LIST("EXPORT_FLAG");
	ADD_OPERATOR_INTO_THE_LIST("ROBOTS");
	ADD_OPERATOR_INTO_THE_LIST("DECLARE_ARGS");
	ADD_OPERATOR_INTO_THE_LIST("BLOCK_CODE");
	ADD_OPERATOR_INTO_THE_LIST("OPERATORS");
	ADD_OPERATOR_INTO_THE_LIST("OPERATOR");
	ADD_OPERATOR_INTO_THE_LIST("OPER");
	ADD_OPERATOR_INTO_THE_LIST("EXPR");
	ADD_OPERATOR_INTO_THE_LIST("EXPR1");
	ADD_OPERATOR_INTO_THE_LIST("EXPR2");
	ADD_OPERATOR_INTO_THE_LIST("TERM");
	ADD_OPERATOR_INTO_THE_LIST("VAL");
	ADD_OPERATOR_INTO_THE_LIST("ROBOT_LINK");
	ADD_OPERATOR_INTO_THE_LIST("FLAG_WAIT");
	ADD_OPERATOR_INTO_THE_LIST("ARGS_BLOCK");
	ADD_OPERATOR_INTO_THE_LIST("ARGS");
	ADD_OPERATOR_INTO_THE_LIST("ARG");

	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("FUNCTIONS");
	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("OPERATORS");
	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("OPERATOR");
	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("EXPR");
	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("EXPR1");
	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("EXPR2");
	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("TERM");
	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("VAL");
	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("ARGS_BLOCK");
	ADD_OPERATOR_INTO_THE_CLOSURE_LIST("ARGS");
};


bool returnOperatorClosureFlag(std::string _name){
	for (int i = 0; i < list_of_closure_operators.size(); ++i)
	{
		if (list_of_closure_operators[i].compare(_name) == 0){
			return true;
		}
	}
	return false;
};

bool isItOperator(std::string _name){
	// 
	for (int i = 0; i < list_of_operators.size(); ++i)
	{
		if (list_of_operators[i].compare(_name) == 0){
			return true;
		}
	}
	return false;
};

bool isItToken(std::string _name, std::string *returned_string){
	// 
	returned_string->assign(getToken(_name));
	if (returned_string->compare("") == 0){ // Если пустую строку вернуло
		return false;
	}
	else {
		return true;
	}
};

/*
	bool isItSymbol(std::string _name){
		// 
		return false;
	};
*/

// Функция handleRequest(), надо как-то обработать структуру
AnswerNodeInformation* handleRequest(RequestNodeInformation* _request){

	/// Если первое вхождение то нужно сгенерировать список операторов
	generateOperatorsList();

	AnswerNodeInformation* _answer = new AnswerNodeInformation();
	std::string *temp_str = new std::string("");
	_answer->_name.assign(temp_str->c_str());
	// сначала проверим имя элемента. И решим это токен, символ или оператор с правилом
	if ( isItToken(_request->_name, temp_str)){
		_answer->_name.assign(temp_str->c_str()); // Подразумеваем что токен вернет символ или какой-то флаг поставит
		_answer->is_stop = false;
	}
	delete temp_str;
	// Теперь смотрим если это правило
	// А это должно быть стопудово правило
	// Тогда мы должны в структуру ОТВЕТ записать соответствующие флаги и изменить наши внутренние счетчики
	// И посмотреть на основе этих счетчиков можем мы применять оператор или нет.
	// Короче смотрим счетчик. можно или нет использовать. Меняем счетчик если можно.
	// И задаем орпеделенное имя так что ЯДРО программы поймет как с этим работать
	
	// Так теперь раз к нам пришел оператор мы смотрим занулился ли счетчик.
	// если нулевой то отправляем - низззяяа!
	// если нет, то можно и уменьшаем на единицу
	if (isItOperator(_request->_name)){
		_answer->is_closure_operator = returnOperatorClosureFlag(_request->_name);
		if (global_counter > 0){
			_answer->is_stop = false;
			global_counter--;
		}
		else {
			_answer->is_stop = true;
		}
	}
	return _answer;
};

PREFIX_FUNC_DLL AnswerNodeInformation* sendRequestToDll(RequestNodeInformation* _request){
	// Вызываем функцию обработки нашей структуры:
	return handleRequest(_request);
};