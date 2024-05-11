cmake_minimum_required(VERSION 3.28)
project(yapay_zeka_odev C)

set(CMAKE_C_STANDARD 11)

add_executable(yapay_zeka_odev main.c
        data_types.h
        graph_search.h
        HashTable.c
        hash_table.h
        Standart_Search.c
        SpesificToProblem.c)
