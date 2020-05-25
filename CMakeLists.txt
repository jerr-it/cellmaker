cmake_minimum_required(VERSION 3.15)
project(celautom)

add_subdirectory(CellularAutomata)
add_executable(celautom main.c)
target_link_libraries(celautom CellularAutomaton)
