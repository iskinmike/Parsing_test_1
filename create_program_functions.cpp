#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include "class_struct.h"
#include "create_program_functions.h"



void startFunctionTest(){
	printf("%s\n","test" );
}


bool findProgramInString(TokenTypeClass* _token){
	Variable* _var_p = dynamic_cast<Variable*>(_token);
	std::string temp_str;
	temp_str = _var_p->returnName();
	temp_str=temp_str.substr(temp_str.find("\"")+1);
    temp_str=temp_str.substr(0,temp_str.find("\""));
    if (temp_str.compare("PROGRAM") == 0) {
    	return true;
    }
    else {return false;}
};

std::string cutStringValueFromTokenName(TokenTypeClass* _token){
	Variable* _var_p = dynamic_cast<Variable*>(_token);
	std::string temp_str;
	temp_str = _var_p->returnName();
	temp_str=temp_str.substr(temp_str.find("\"")+1);
    temp_str=temp_str.substr(0,temp_str.find("\""));
    return temp_str;
};


OperatorTypeClass* returnVariablesRefToNextOperator(TokenTypeClass* searched_variable){
  Variable* _var_p = dynamic_cast<Variable*>(searched_variable);
  
};


void findDeapestToken(OperatorTypeClass* searched_operator){
  OperatorClass* _b = dynamic_cast<OperatorClass*>(searched_operator);
  if (_b->definition_block_pointer != NULL){
  	findDeapestToken(_b->definition_block_pointer);
  }
  else {
  	/// Теперь дошли до конца у нас в примере UID. Нужно по его ссылке пройти
  	if (_b->variable_pointer != NULL ) {
  		returnVariablesRefToNextOperator(_b->variable_pointer);

  	}
  }
}


void startCreatingProgram(OperatorTypeClass* starting_operator){
  //try
  // Сначала заходим в самый глубокий по связям в операторе Токен(это переменная)
  // нужно еще проверку сделать если это символ то выводить просто символ(его значение)
  findDeapestToken(starting_operator);

}


void findProgramEntryPoint(OperatorTypeClass* starting_operator){
  Operators* _b = dynamic_cast<Operators*>(starting_operator);
  if (_b) {
    if (_b->pointer_to_operators != NULL) {
      findProgramEntryPoint(_b->pointer_to_operators);
    }
    else {
    	if(_b->pointer_to_operator != NULL) { // Может быть лишняя проверка
    		/*
    		if (findProgramInString(_b->pointer_to_operator)) {
    			/// Теперь должно начинаться самое интересное мы точку входа в программу нашли
    			/// Работаем со pointer_to_operator Это у нас уже нужный оператор с него все и начнется
    			startCreatingProgram(_b->pointer_to_operator);
    		}
    		*/
    	}
    }
  }
}


