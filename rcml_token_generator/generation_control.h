#ifdef _WIN32
	#define PREFIX_FUNC_DLL __declspec(dllexport)
#else
	#define PREFIX_FUNC_DLL
#endif

struct RequestNodeInformation{
	std::string _name;
	int i;
};

struct AnswerNodeInformation{
	bool is_stop;
	bool is_closure_operator;
	int count;
	std::string _name;
};

///  Блок функций которые будут обрабатывать эти структуры
/*
	class CounterOfOperatorInvokes{
		int operator_depth_counter; //Считает как глубоко зашли
		int operator_depth;  		// Устанавлливает максимальную глубину вложенности
		int amount_of_allowed_operators; // Определяет общее коичество таких операторов на программу
		bool is_allowed_to_invoke_operator; // Говорит разрешено ли вызывать оператор или нет
	public: 

		CounterOfOperatorInvokes(
			int _operator_depth_counter,
			int _operator_depth,  		
			int _amount_of_allowed_operators, 
			bool _is_allowed_to_invoke_operator
			):
			operator_depth_counter(_operator_depth_counter),
			operator_depth(_operator_depth),
			amount_of_allowed_operators(_amount_of_allowed_operators),
			is_allowed_to_invoke_operator(_is_allowed_to_invoke_operator)
		{};

		void invokeOperator();
		void closeOperator();
		bool isAllowedToInvokeOperator();
	};
*/

// Самая главная функция, которую экспортируем
PREFIX_FUNC_DLL AnswerNodeInformation* sendRequestToDll(RequestNodeInformation* _request);
void generateOperatorsList();
bool isItOperator(std::string _name);
bool isItToken(std::string _name, std::string *returned_string);
AnswerNodeInformation* handleRequest(RequestNodeInformation* _request);