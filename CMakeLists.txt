cmake_minimum_required(VERSION 3.10)
project(calc)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(calc main.cpp src/Parser.cpp src/Parser.h src/Expression.h src/Tokens.h)

enable_testing()
add_executable(calc_test tests/Tests.cpp)
target_link_libraries(calc_test ${CONAN_LIBS})
add_test(NAME calc_test COMMAND calc_test)