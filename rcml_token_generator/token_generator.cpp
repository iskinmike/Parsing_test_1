#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include "token_generator.h"

void printHelloFromSo(){
	printf("%s\n", "Hello from Shared library, all seems to work good!");
};

std::string choosePregenString(){
	DataStorage& data = DataStorage::Instance();
	return data.pregen_strings[rand() % data.pregen_strings.size()];
};
std::string returnIntToString(int number) {
	std::string str;
	char buf[10];
	sprintf(buf, "%d", number);
	str.assign(buf);
	return str;
};
std::string generateString(){
	std::string temp_str("");
	int count_of_characters = rand() % 10 + 3;
	DataStorage& data = DataStorage::Instance();
	for (int i = 0; i < count_of_characters; i++){
		temp_str.append((data.mass_of_chars + rand() % 63), 1);
	}
	return temp_str;
};
std::string generateNumber(){
	std::string temp_str("");
	int count_of_numbers = rand() % 10 + 1;
	for (int i = 0; i < count_of_numbers; i++){
		temp_str.append(returnIntToString(rand() % 10));
	}
	return temp_str;
};
std::string generateRobotVariable(){
	std::string temp_str("@");
	temp_str.append(generateString());
	return temp_str;
};
std::string generateRobotId(){
	std::string temp_str("robot_");
	temp_str.append(generateString());
	return temp_str;
};
std::string generateId(){
	std::string temp_str("");
	int count_of_characters = rand() % 10 + 2;
	DataStorage& data = DataStorage::Instance();
	/// 
	temp_str.append((data.mass_of_chars + rand() % 52), 1);
	for (int i = 1; i < count_of_characters; i++){
		temp_str.append((data.mass_of_chars + rand() % 63), 1);
	}
	return temp_str;
};
std::string generateNameAndMacros(){
	std::string temp_str("");
	temp_str.append(generateString());
	temp_str.append(" ");
	temp_str.append(generateString());
	return temp_str;
}

std::string searchSimilarStringInData(std::string recv_str){
	DataStorage& data = DataStorage::Instance();
	data.i = 5;
	if (data.names_of_tokens.count(recv_str)){
		return data.names_of_tokens[recv_str];
	}
	else {
		if (data.special_tokens_names.count(recv_str)){
			switch (data.special_tokens_names[recv_str]){
			case GENERATE_NUM:{
				recv_str = generateNumber();
				return recv_str;
			}
			case GENERATE_ROBOT_VAR:{
				recv_str = generateRobotVariable();
				return recv_str;
			}
			case GENERATE_ROBOT_ID:{
				recv_str = generateRobotId();
				return recv_str;
			}
			case GENERATE_ID:{
				recv_str = generateId();
				return recv_str;
			}
			case CHOOSE_PREGEN_STRING:{
				recv_str = choosePregenString();
				return recv_str;
			}
			case GENERATE_NAME_AND_MACROS:{
				recv_str = generateNameAndMacros();
				return recv_str;
			}
			default:{return "error_invalid_special_token"; }
			}
		}
		else {
			return "";
		}
	}
};

// Ёто будет внешн€€ функци€  ѕусть вызывает что-нить еще
std::string getToken(std::string recv_str){
	recv_str = searchSimilarStringInData(recv_str);
	return recv_str;
};

DataStorage::DataStorage()
{
	i = 1;
	srand(time(NULL));
	// «десь надо будет сделать заполнение карты имен
	names_of_tokens["UID_KEYWORD"] = "UID";
	names_of_tokens["INCLUDE_KEYWORD"] = "include";
	names_of_tokens["INCLUDE_LIB_KEYWORD"] = "include_lib";
	names_of_tokens["EXPORT_KEYWORD"] = "export";
	names_of_tokens["FUNCTION_KEYWORD"] = "function";
	names_of_tokens["ROBOT_KEYWORD"] = "robot";
	names_of_tokens["FLAG_WAIT_YES"] = "#";
	names_of_tokens["FLAG_WAIT_NO"] = "~";
	names_of_tokens["FUNCTION_DELIMETER"] = "::";
	names_of_tokens["ROBOT_POINTER"] = "->";
	names_of_tokens["IF_KEYWORD"] = "if";
	names_of_tokens["ELSE_KEYWORD"] = "else";
	names_of_tokens["LOOP_KEYWORD"] = "loop";
	names_of_tokens["BREAK_KEYWORD"] = "break";
	names_of_tokens["CONTINUE_KEYWORD"] = "continue";
	names_of_tokens["EXIT_KEYWORD"] = "exit";
	names_of_tokens["RETURN_KEYWORD"] = "return";
	names_of_tokens["DELETE_KEYWORD"] = "delete";
	names_of_tokens["TRY_KEYWORD"] = "try";
	names_of_tokens["CATCH_KEYWORD"] = "catch";
	names_of_tokens["THROW_KEYWORD"] = "throw";
	names_of_tokens["EQ"] = "==";
	names_of_tokens["LE"] = "<=";
	names_of_tokens["GE"] = ">=";
	names_of_tokens["NE"] = "!=";
	names_of_tokens["AND"] = "&&";
	names_of_tokens["OR"] = "||";

	special_tokens_names["NUM"] = GENERATE_NUM;
	special_tokens_names["ROBOT_VAR"] = GENERATE_ROBOT_VAR;
	special_tokens_names["ROBOT_ID"] = GENERATE_ROBOT_ID;
	special_tokens_names["ID"] = GENERATE_ID;
	special_tokens_names["STRING"] = CHOOSE_PREGEN_STRING;
	special_tokens_names["DEFINE"] = GENERATE_NAME_AND_MACROS;

	for (int i = 0; i < AMOUNT_OF_CHARS; i++){
		if (i < 26) {
			mass_of_chars[i] = i + 65;
		}
		if (i > 25 && i < 52) {
			mass_of_chars[i] = i + 97 - 26;
		}
		if (i > 51 && i < 62) {
			mass_of_chars[i] = i + 48 - 52;
		}
		if (i == 62) {
			mass_of_chars[i] = 95;
		}
	}

	pregen_strings.push_back("pregen_fail");
	pregen_strings.push_back("pregen_success");
	pregen_strings.push_back("pregen_please_wait");
	pregen_strings.push_back("pregen_change_color");
	pregen_strings.push_back("pregen_name_of_variable");
	pregen_strings.push_back("pregen_robot_id");
	pregen_strings.push_back("pregen_error");
};