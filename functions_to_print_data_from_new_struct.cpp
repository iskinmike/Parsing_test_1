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
        global_string_with_graph.append(_node->printLable());
        printRuleLable((*i));
      }
    }
  }
};
void printRuleLable(RuleStruct* _rule){
  if(_rule->_variable.size() == 0){
    global_string_with_graph.append(_rule->printLable());
  }
  for (auto i = _rule->_variable.begin(); i!= _rule->_variable.end(); ++i){
    if ((*i)!=NULL) {
      global_string_with_graph.append(_rule->printLable());
      printVariableLable((*i));
    }
  }
};
void printVariableLable(VariableStruct* _variable){
  if (_variable->_node == NULL){
    global_string_with_graph.append(_variable->printLable());
  }
};

//////////////////////////////////////////////// PRINT DATA
void printNodeData(NodeStruct* _node){
  if (_node->_rule.size() != 0) {
    for (auto i = _node->_rule.begin(); i!= _node->_rule.end(); ++i){
      if ((*i)!=NULL) {
        //printf("%s -> ",_node->_node_uniq_name.c_str() );
        global_string_with_graph.append(_node->_node_uniq_name.c_str());
        global_string_with_graph.append(" -> ");
        printRuleData((*i));
      }
    }
  }
};
void printRuleData(RuleStruct* _rule){
  if(_rule->_variable.size() == 0){
    //printf("%s;\n ", _rule->_rule_uniq_name.c_str());
    global_string_with_graph.append(_rule->_rule_uniq_name.c_str());
    global_string_with_graph.append(";\n");
  }
  bool should_print_lable = false;
  if (_rule->_variable.size() >1){
  	should_print_lable = true;
  }
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
  for (int i=0; i< _rule->_variable.size(); i++){
  	if (_rule->_variable[i] != NULL){
  		global_string_with_graph.append(_rule->_rule_uniq_name.c_str());
    	global_string_with_graph.append(" -> ");
      printVariableData(_rule->_variable[i],i,should_print_lable);
  	}
  }
};
void printVariableData(VariableStruct* _variable, int _pos, bool do_we_print_label){
  if (_variable->_node != NULL) {
    //printf("%s;\n",_variable->_node->_node_uniq_name.c_str() );
    //global_string_with_graph.append(_variable->_node->_node_uniq_name.c_str());
    if (do_we_print_label) {
    	//global_string_with_graph.append(_variable->_node->_node_uniq_name.c_str());

		global_string_with_graph.append("inremediate_node_");
    	global_string_with_graph.append(returnIntToString(counter_of_intermediate_nodes));
    	global_string_with_graph.append("->");
    	global_string_with_graph.append(_variable->_node->_node_uniq_name.c_str());
	    global_string_with_graph.append(";\n");

	    global_string_with_graph.append("inremediate_node_");
    	global_string_with_graph.append(returnIntToString(counter_of_intermediate_nodes));
        global_string_with_graph.append("[label=\"");
        global_string_with_graph.append(returnIntToString(_pos+1));
        global_string_with_graph.append("\"];\n");

        counter_of_intermediate_nodes++;
    }
    else {
    	global_string_with_graph.append(_variable->_node->_node_uniq_name.c_str());
    	global_string_with_graph.append(";\n");
    }
    //global_string_with_graph.append(";\n");
  }
  else {
    //printf("%s;\n", _variable->_variable_uniq_name.c_str() );
    if (do_we_print_label) {
    	global_string_with_graph.append("inremediate_node_");
    	global_string_with_graph.append(returnIntToString(counter_of_intermediate_nodes));
    	global_string_with_graph.append("->");
    	global_string_with_graph.append(_variable->_variable_uniq_name.c_str());
	    global_string_with_graph.append(";\n");

	    global_string_with_graph.append("inremediate_node_");
    	global_string_with_graph.append(returnIntToString(counter_of_intermediate_nodes));
    	global_string_with_graph.append("[label=\"");
        global_string_with_graph.append(returnIntToString(_pos+1));
        global_string_with_graph.append("\"];\n");

        counter_of_intermediate_nodes++;
    }
    else {
    	global_string_with_graph.append(_variable->_variable_uniq_name.c_str());
    	global_string_with_graph.append(";\n");
    }
  }
};


///////////////////////////////////////////////////////// PRINT ALL
void printAllDataFromNewStruct(std::string file_path){
  global_string_with_graph.append("digraph G {\nsize =\"40,40\";\n");
  for (auto i = print_functions_data.node_struct_vector.begin(); i!= print_functions_data.node_struct_vector.end(); ++i){
    printNodeData(*i);
  }

  for (auto i = print_functions_data.node_struct_vector.begin(); i!= print_functions_data.node_struct_vector.end(); ++i){
    printNodeLable(*i);
  }
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