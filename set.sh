lex code_parser.l
bison --verbose --report-file "result" -d -t code_parser.y
g++ -g -o parser -std=c++11 lex.yy.c code_parser.tab.c *.cpp -I"/home/mike/workspace/flex_bison/test6_code2" -I"/home/mike/workspace/flex_bison/test6_code2/rcml_token_generator/" -L"/home/mike/workspace/flex_bison/test6_code2/rcml_token_generator/" -ltoken_generator_debug