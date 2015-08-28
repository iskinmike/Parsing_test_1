lex code_parser.l
bison --verbose --report-file "result" -d -t code_parser.y
g++ -std=c++11 lex.yy.c code_parser.tab.c *.cpp -I"/home/mike/workspace/flex_bison/test6_code2"