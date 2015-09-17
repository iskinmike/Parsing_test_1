#include <vector>
#include <map>

#ifndef _SETTINGS_STRUCT_
#include "settings_struct.h"
#endif
// Наверное стоит сделать его синглтоном чтобы 
// всегда работали с одним и теми же данными в памяти
class GlobalDataStorage
{
public:
	std::vector<Variable*> var_vector_for_additional_connections;
	std::map<Variable*,OperatorTypeClass*> var_map;
	std::vector<VariableStruct *> var_struct_vector;
	std::vector<NodeStruct*> node_struct_vector;
	std::vector<SettingsStruct*> set_of_settings_structs;
	// Функция которая вернет структуру
	static GlobalDataStorage& Instance()
	{
		static GlobalDataStorage theSingleInstance;
		return theSingleInstance;
	}
private:
	GlobalDataStorage(){};
	GlobalDataStorage(const GlobalDataStorage&) = delete;
	GlobalDataStorage& operator=(const GlobalDataStorage&) = delete;
};