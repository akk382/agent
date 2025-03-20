cmake_minimum_required(VERSION 3.30)
project(agent C)

set(CMAKE_C_STANDARD 11)

#find_package(cJSON REQUIRED)

set(RDKAFKA_INCLUDE_DIR "usr/include/librdkafka")
#set(RDKAFKA_LIBRARY "usr/lib/librdkafka.so") # for arch linux
set(RDKAFKA_LIBRARY "/usr/lib/x86_64-linux-gnu/librdkafka.so")

add_library(agent
        consumer.h
        producer.h
        execute_job.h
        library.c
        execute_job.c
        consumer.c
        producer.c
        cJSON.c
        cJSON.h)

add_executable(agent_exec test_producer.c)

target_link_libraries(agent_exec PRIVATE agent ${RDKAFKA_LIBRARY})

target_include_directories(agent_exec PRIVATE ${RDKAFKA_INCLUDE_DIR})