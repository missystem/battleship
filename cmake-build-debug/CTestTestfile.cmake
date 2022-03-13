# CMake generated Testfile for 
# Source directory: /Users/yuhan/Documents/Northwestern/CS211/Battleship
# Build directory: /Users/yuhan/Documents/Northwestern/CS211/Battleship/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test_model_test "model_test")
set_tests_properties(Test_model_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/yuhan/Documents/Northwestern/CS211/Battleship/.cs211/cmake/211commands.cmake;90;add_test;/Users/yuhan/Documents/Northwestern/CS211/Battleship/CMakeLists.txt;25;add_test_program;/Users/yuhan/Documents/Northwestern/CS211/Battleship/CMakeLists.txt;0;")
subdirs(".cs211/lib/catch")
subdirs(".cs211/lib/ge211")
