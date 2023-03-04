cmake_minimum_required(VERSION 3.16)
project(simple_shell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(simple_shell
        _cmd_input_tokenizer.c
        _cmd_path_search_tokenizer.c
        _get_env.c
        _trim.c
        main.c
        main.h
        queue_functions.c
        system_files_functions.c)
