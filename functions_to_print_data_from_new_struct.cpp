#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string> 

#include "class_struct.h"
#include "new_struct_for_program.h"
#include "singleton_data_struct.h"
#include "functions_to_print_data_from_new_struct.h"

std::string global_string_with_graph("");

int counter_of_intermediate_nodes = 0;

GlobalDataStorage& print_functions_data = GlobalDataStorage::Instance();

/// MACROS

#define CREATE_TOKENS_TABLE \
  global_string_with_graph.append("TOKEN_TABLE[label=\""); \
  global_string_with_graph.append("{"); \
  global_string_with_graph.append("Key Words"); \
  global_string_with_graph.append("|"); \
  global_string_with_graph.append("{"); \
  int temp_count_i = massive_of_tokens.size(); \
  for (int i=0; i< temp_count_i; i++){ \
    global_string_with_graph.append("<"); \
    global_string_with_graph.append("token_"); \
  	global_string_with_graph.append(returnIntToString(i)); \
  	global_string_with_graph.append(">"); \
  	global_string_with_graph.append(massive_of_tokens[i]); \
  	if (i < temp_count_i-1){ \
  	  global_string_with_graph.append("|"); \
  	} \
  } \
  global_string_with_graph.append("} }\" style=filled gradientangle=90 fillcolor=\"lightsteelblue1;0.5:green\"];\n");




std::string returnIntToString(int number) {
	std::string str;
	char buf[10];
	sprintf(buf, "%d", number);
	str.assign(buf);
	return str;
};

//////////////////////////////////////////////// PRINT LABLE
void printNodeLable(NodeStruct* _node){
  if (_node->_rule.size() != 0) {
    for (auto i = _node->_rule.begin(); i!= _node->_rule.end(); ++i){
      if ((*i)!=NULL) {
        //global_string_with_graph.append(_node->printLable());
        printRuleLable((*i));
      }
    }
  }
};
void printRuleLable(RuleStruct* _rule){
  if(_rule->_variable.size() == 0){
    //global_string_with_graph.append(_rule->printLable());
  }
  for (int i=0;i < _rule->_variable.size(); i++) {
  //for (auto i = _rule->_variable.begin(); i!= _rule->_variable.end(); ++i){
      //"node0":f2 -> "node4":f1;
      //global_string_with_graph.append(_rule->printLable());
      //printVariableLable((*i),_rule,);
      printVariableLable(_rule->_variable[i],_rule,i);
  }
};
void printVariableLable(VariableStruct* _variable, RuleStruct* _rule, int _pos){
  if (_variable->_node != NULL){
  	  global_string_with_graph.append("\"");
      global_string_with_graph.append(_rule->_rule_uniq_name.c_str());
      global_string_with_graph.append("\":var_");
      global_string_with_graph.append(returnIntToString(_pos));
	  global_string_with_graph.append(" -> ");
	  global_string_with_graph.append(_variable->_node->_node_uniq_name.c_str());
	  global_string_with_graph.append(";\n");
  }
};

//////////////////////////////////////////////// PRINT DATA
void printNodeData(NodeStruct* _node, std::vector<std::string> *massive_of_tokens){
  if (_node->_rule.size() != 0) {
    for (auto i = _node->_rule.begin(); i!= _node->_rule.end(); ++i){
      if ((*i)!=NULL) {
        //printf("%s -> ",_node->_node_uniq_name.c_str() );
        global_string_with_graph.append(_node->_node_uniq_name.c_str());
        global_string_with_graph.append(" -> ");
        printRuleData((*i), massive_of_tokens);
      }
    }
  }
};
void printRuleData(RuleStruct* _rule, std::vector<std::string> *massive_of_tokens){
  if(_rule->_variable.size() == 0){
    //printf("%s;\n ", _rule->_rule_uniq_name.c_str());
    global_string_with_graph.append(_rule->_rule_uniq_name.c_str());
    global_string_with_graph.append(";\n");
  }
  //bool should_print_lable = false;
  //if (_rule->_variable.size() >1){
  //	should_print_lable = true;
  //}
/*
  for (auto i = _rule->_variable.begin(); i!= _rule->_variable.end(); ++i){
    if ((*i)!=NULL) {
      //printf("%s -> ", _rule->_rule_uniq_name.c_str());
    	global_string_with_graph.append(_rule->_rule_uniq_name.c_str());
    	global_string_with_graph.append(" -> ");
      printVariableData((*i));
    }
  }
*/

  global_string_with_graph.append(_rule->_rule_uniq_name.c_str());
  global_string_with_graph.append(";\n");

  global_string_with_graph.append(_rule->_rule_uniq_name.c_str());
  global_string_with_graph.append("[label=\"");
  //global_string_with_graph.append("{");
  global_string_with_graph.append(_rule->_name.c_str());
  global_string_with_graph.append("|");
  global_string_with_graph.append("{");
  int temp_count_i = _rule->_variable.size();
  for (int i=0; i< temp_count_i; i++){
    global_string_with_graph.append("<");
    global_string_with_graph.append("var_");
  	global_string_with_graph.append(returnIntToString(i));
  	global_string_with_graph.append(">");
  	std::string temp_str(_rule->_variable[i]->_name);
  	if (temp_str.find("'") != std::string::npos){
  	  	temp_str = temp_str.substr(temp_str.find("'")+1);
  		temp_str = temp_str.substr(0,temp_str.find("'"));
  		global_string_with_graph.append("\\");
  	}
  	global_string_with_graph.append(temp_str);
  	if (i < temp_count_i-1){
  	  global_string_with_graph.append("|");
  	}
  }
  global_string_with_graph.append("} \" style=filled gradientangle=90 fillcolor=\"cornsilk;0.5:aquamarine\"];\n");


/*
  for (int i=0; i< _rule->_variable.size(); i++){
  	if (_rule->_variable[i] != NULL){
  		//global_string_with_graph.append(_rule->_rule_uniq_name.c_str());
    	//global_string_with_graph.append(";\n");
    	//global_string_with_graph.append();

      printVariableData(_rule->_variable[i],_rule,i, massive_of_tokens);
  	}
  }
*/
};
void printVariableData(VariableStruct* _variable, RuleStruct* _rule, int _pos, std::vector<std::string> *massive_of_tokens){
/*	
  if (_variable->_node == NULL){
  	for (int i = 0; i < massive_of_tokens->size(); ++i)
  	{
  		if (_variable->_name.compare((*massive_of_tokens)[i]) == 0){
  		  global_string_with_graph.append("\"");
		  global_string_with_graph.append(_rule->_rule_uniq_name.c_str());
		  global_string_with_graph.append("\":var_");
		  global_string_with_graph.append(returnIntToString(_pos));
          global_string_with_graph.append(" -> \"TOKEN_TABLE\":token_");
          global_string_with_graph.append(returnIntToString(i));
          global_string_with_graph.append(";\n");
  		}
  	}
  	
  }
*/
};


///////////////////////////////////////////////////////// PRINT ALL
void printAllDataFromNewStruct(std::string file_path, std::vector<std::string> massive_of_tokens){
  global_string_with_graph.append("digraph G {\nsize =\"40,40\";\n node [shape = record,height=.1];\n splines=line;\nsplines=true;\nrankdir = \"LR\";\n");

  for (auto i = print_functions_data.node_struct_vector.begin(); i!= print_functions_data.node_struct_vector.end(); ++i){
    printNodeData(*i, &massive_of_tokens);
  }

  for (auto i = print_functions_data.node_struct_vector.begin(); i!= print_functions_data.node_struct_vector.end(); ++i){
    printNodeLable(*i);
  }
  for (auto i = print_functions_data.node_struct_vector.begin(); i!= print_functions_data.node_struct_vector.end(); ++i){
    global_string_with_graph.append((*i)->printLable());
  }

  // Вызываем функцию которая соберет нам бокс с токенами 
  // и потом функцию которая нарисует связи в правил и этого бокса
  //CREATE_TOKENS_TABLE;


  //printf("%s\n","}");
  global_string_with_graph.append("}\n");

	if (file_path.compare("")==0){
		printf("%s\n",global_string_with_graph.c_str() );
	}
	else {
		FILE * pointer_to_file;
		pointer_to_file = fopen(file_path.c_str(),"w+");
		if (pointer_to_file != NULL)
		{
			// Точно печать в файл
			fputs(global_string_with_graph.c_str(),pointer_to_file);
		}
		else {
			printf("%s\n",global_string_with_graph.c_str() );
		}
		fclose(pointer_to_file);
	}
}