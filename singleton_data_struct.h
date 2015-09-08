#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>


// Наверное стоит сделать его синглтоном чтобы 
// всегда работали с одним и теми же данными в памяти
class DataStorage
{
public:
	int i;
	// Карта имен. Имя токена - что вернуть.
	std::vector<Variable*> var_vector_for_additional_connections;
	std::map<Variable*,OperatorTypeClass*> var_map;
	std::vector<VariableStruct *> var_struct_vector;
	std::vector<NodeStruct*> node_struct_vector;
	// Функция которая вернет структуру
	static DataStorage& Instance()
	{
		static DataStorage theSingleInstance;
		return theSingleInstance;
	}
private:
	DataStorage(){};
	DataStorage(const DataStorage&) = delete;
	DataStorage& operator=(const DataStorage&) = delete;
};