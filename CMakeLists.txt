cmake_minimum_required(VERSION 3.10)
project(CounterProgram)

set(CMAKE_C_STANDARD 99)

include_directories(include)

# Create the executable for infinite_counter
add_executable(infinite_counter src/main.c src/counter.c)

# Create the executable for counter_handler
add_executable(counter_handler src/counter_handler.c)
