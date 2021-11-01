cmake_minimum_required(VERSION 3.9)
project(CSC173_Project_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(CSC173_Project_2 expr.c LinkedList.c LinkedList.h RecursiveDescentParser.c RecursiveDescentParser.h LMCRS.c LMCRS.h stack.c stack.h TableDrivenParser.c TableDrivenParser.h)