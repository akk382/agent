cmake_minimum_required(VERSION 3.30)
project(agent C)

set(CMAKE_C_STANDARD 11)

find_package(cJSON REQUIRED)

add_library(agent
        consumer.h
        producer.h
        execute_job.h
        library.c
        execute_job.c
        consumer.c
        producer.c
        main.c
        test_producer.c)

target_link_libraries(agent cjson)