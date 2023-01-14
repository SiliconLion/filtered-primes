cmake_minimum_required(VERSION 3.20)
project(filtered-primes C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O3")

add_executable(filtered-primes main.c)

find_library(cave libcave.a)
target_link_libraries(filtered-primes ${cave})
