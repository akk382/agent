cmake_minimum_required(VERSION 3.30)
project(agent C)

set(CMAKE_C_STANDARD 11)

add_library(agent
        library.c
        execute_job.h
        execute_job.c
        consumer.c
        producer.c
        consumer.h
        producer.h)
