# Parsing_test_1
flex &amp; bison parsing test, currently work on three struct

###Ядро документация.

Ядро программы для создания описания графов(на языке dot) и генерации программ по заданной синтаксической карте(карта задается по правилам, аналогичным фалам программы bison).

Генератор Синтетических тестов. Ядро.

Генератор тестов предназначен для автоматической генерации тестов языков программирования.
Для работы программы необходимо:
 - Синтаксическая карта языка. Это текстовый файл в котором описаны правила языка в формате аналогичном формату программы bison.
 - динамическая библиотека с именем libtoken_generator.so(.dll), экспортирующая функцию sendRequest();

###Доступные команды
  Использование: parser [аргумент [путь к файлу]]     Создает контент соответствующий заданному аргументу и выводит результат в файл или в консоль.

- --help:     Выводит список команд и завершает работу.
- --version:  Выводит версию программы и завершает работу.
- --graph:    Создает описание графа на языке dot. Если [путь к файлу] указан, то записывает описание в этот файл(создает его если нужно).
- --program:  Создает код тестовой программы. Если [путь к файлу] указан, то записывает код в этот файл(создает его если нужно).
- --input:    [путь к файлу] задает путь к синтаксической карте которую будет разбирать  программа, если аргумент не задан то ввод осуществляется в консоль.

  Динамическая библиотека libtoken_generator должна отвечать за создание токенов(зарезервированных слов), переменных, строк и чисел. А так же управлять количеством вызываемых операторов языка при создании тестов.


######Взаимодействие с библиотекой libtoken_generator:
Ядро генератора при создании тестов экспортирует из libtoken_generator функцию:
AnswerNodeInformation* _request sendRequest(RequestNodeInformation* _request).
  Функция принимет структуку RequestNodeInformation содержащую имя оператора или токена.
```
struct RequestNodeInformation{
	std::string _name;
};
```
  а возвращает структуру AnswerNodeInformation содержащую информацию о том можно ли вызывать данный оператор, сгенерированный токен, число, строку и дополнительную информацию.
```
struct AnswerNodeInformation{
	bool is_stop;
	bool is_closure_operator;
	int count;
	std::string _name;
}; 
```

Примеры использования
 - команда построения графа из файла test.txt.
```test.txt
%%
a: b
 | c;
c: var_1;
b: var_2
 | var_3;
```

```bash
 $ parser --input test.txt --graph 
``` 
Выведет на экран описание графа на языке dot:
```
digraph G {
	size ="40,40";
	node [shape = record,height=.1];
	splines=line;
	splines=true;
	rankdir = "LR";
	OP_1 -> DEFINITION_BLOCK_WITH_END_2;
	DEFINITION_BLOCK_WITH_END_2[label="Rule__1|{<var_0>var_1} " style=filled gradientangle=90 fillcolor="cornsilk;0.5:aquamarine"];
	OP_0 -> DEFINITION_BLOCK_WITH_END_0;
	DEFINITION_BLOCK_WITH_END_0[label="Rule__1|{<var_0>b} " style=filled gradientangle=90 fillcolor="cornsilk;0.5:aquamarine"];
	OP_0 -> DEFINITION_BLOCK_WITH_END_1;
	DEFINITION_BLOCK_WITH_END_1[label="Rule__2|{<var_0>c} " style=filled gradientangle=90 fillcolor="cornsilk;0.5:aquamarine"];
	OP_2 -> DEFINITION_BLOCK_WITH_END_3;
	DEFINITION_BLOCK_WITH_END_3[label="Rule__1|{<var_0>var2} " style=filled gradientangle=90 fillcolor="cornsilk;0.5:aquamarine"];
	OP_2 -> DEFINITION_BLOCK_WITH_END_4;
	DEFINITION_BLOCK_WITH_END_4[label="Rule__2|{<var_0>var_3} " style=filled gradientangle=90 fillcolor="cornsilk;0.5:aquamarine"];
	"DEFINITION_BLOCK_WITH_END_0":var_0 -> OP_2;
	"DEFINITION_BLOCK_WITH_END_1":var_0 -> OP_1;
	OP_1[label="c" shape=box,color=deeppink,style=filled ];
	OP_0[label="a" shape=box,color=deeppink,style=filled ];
	OP_2[label="b" shape=box,color=deeppink,style=filled ];
}
```
