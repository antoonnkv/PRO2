#PLEASE, DO NOT CHANGE THIS FILE
cmake_minimum_required(VERSION 3.5)
project(P2 C)
set(CMAKE_C_STANDARD 99)

include(config.cmake)

set(CMAKE_VERBOSE_MAKEFILE true)
set(warnings -Wall -Wextra)


set(dependencies_song song_list.h song_list.c)
add_executable(test_song_list types.h test_song_list.c ${dependencies_song})
target_compile_options(test_song_list PRIVATE ${warnings})


set(dependencies_user user_list.h user_list.c)
add_executable(test_user_list types.h test_user_list.c ${dependencies_user})
target_compile_options(test_user_list PRIVATE ${warnings})


add_definitions(-DINPUT_FILE="${input}")
add_executable(main main.c types.h ${dependencies_song} ${dependencies_user})
target_compile_options(main PRIVATE ${warnings})


set_target_properties(main test_user_list test_song_list PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)


