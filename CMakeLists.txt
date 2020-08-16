cmake_minimum_required(VERSION 3.12)
project(Ex2AdvancedCoding C)

set(CMAKE_C_STANDARD 99)

add_executable (Ex2AdvancedCoding Countries.c Countries.h main.c Defs.h HashTable.h LinkedList.c LinkedList.h keyValuePair.c keyValuePair.h HashTable.c)