# cssParser
A parser that written in c for translating standard css to json

# develop
git clone https://github.com/kongxun/cssParser.git

cd cssParser&&make clean&&make&&./cssParser

# debug
gdb -tui ./cssParser

# todos
- support more css standard syntax, such as media query
- add testcase
- provide normal api for developer

# update
- v0.1.1 support simple standard css and output as json file
- v0.1 finish building AST
