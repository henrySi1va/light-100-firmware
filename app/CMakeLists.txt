cmake_minimum_required(VERSION 3.25.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(light-100)

target_sources(app PRIVATE 
    src/main.c
    src/tasks/task_logger.c
    src/tasks/task_sound.c)

target_include_directories(app PRIVATE
    src/tasks)
