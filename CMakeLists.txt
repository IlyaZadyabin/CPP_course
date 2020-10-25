cmake_minimum_required(VERSION 3.16)
project(CPP_course)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#add_executable(CPP_course Yellow_Belt/final_project/token.h Yellow_Belt/final_project/token.cpp  Yellow_Belt/final_project/condition_parser.cpp
#		Yellow_Belt/final_project/condition_parser.cpp Yellow_Belt/final_project/condition_parser_test.cpp Yellow_Belt/final_project/main.cpp
#		Yellow_Belt/final_project/node.cpp Yellow_Belt/final_project/database.cpp Yellow_Belt/final_project/date.cpp
#		Yellow_Belt/final_project/test_runner.cpp Yellow_Belt/final_project/test_runner.h)
#add_executable(CPP_course Red_Belt/SearchSystem/main.cpp Red_Belt/SearchSystem/parse.cpp
#		Red_Belt/SearchSystem/search_server.cpp)
add_executable(CPP_course BrownBelt/Week2/test_ini.cpp)
