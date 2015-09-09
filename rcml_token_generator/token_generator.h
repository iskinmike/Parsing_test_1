#ifdef _WIN32
	#define PREFIX_FUNC_DLL __declspec(dllexport)
#else
	#define PREFIX_FUNC_DLL
#endif

PREFIX_FUNC_DLL std::string getToken(std::string recv_str);

std::string searchSimilarStringInData(std::string recv_str);

// Пока без class enum 

#define GENERATE_NUM 0
#define GENERATE_ROBOT_VAR 1
#define GENERATE_ROBOT_ID 2
#define GENERATE_ID 3
#define CHOOSE_PREGEN_STRING 4
#define GENERATE_NAME_AND_MACROS 5

#define AMOUNT_OF_CHARS 63
//int chekKeywordInSpechialTokensNames(std::string str);

std::string generateNumber();
std::string generateRobotVariable();
std::string generateRobotId();
std::string generateId();
std::string choosePregenString();
std::string generateNameAndMacros();

std::string returnIntToString(int number);
std::string generateString();

// Наверное стоит сделать его синглтоном чтобы 
// всегда работали с одним и теми же данными в памяти
class DataStorage
{
public:
	int i;
	// Карта имен. Имя токена - что вернуть.
	std::map<std::string, std::string> names_of_tokens;
	std::map<std::string, int> special_tokens_names;
	std::vector<std::string> pregen_strings;
	char mass_of_chars[AMOUNT_OF_CHARS];
	// Функция которая вернет структуру
	static DataStorage& Instance()
	{
		static DataStorage theSingleInstance;
		return theSingleInstance;
	}
private:
	DataStorage();
	DataStorage(const DataStorage&) = delete;
	DataStorage& operator=(const DataStorage&) = delete;
};