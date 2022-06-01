cmake_minimum_required(VERSION 3.0)
project(testwrite C)

add_executable(testwrite testwrite.c)
if(WIN32)
    target_compile_definitions(testwrite PRIVATE
        -D_CRT_SECURE_NO_WARNINGS)
elseif(APPLE)
    set_target_properties(testwrite PROPERTIES
        MACOSX_BUNDLE TRUE)
endif()
