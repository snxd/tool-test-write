cmake_minimum_required(VERSION 3.0)
project(testwrite C)

add_executable(testwrite testwrite.c)
target_compile_definitions(testwrite PRIVATE -D_CRT_SECURE_NO_WARNINGS)