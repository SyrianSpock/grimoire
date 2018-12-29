cmake_minimum_required(VERSION 3.8)
project(cpp-grimoire)

set(CMAKE_CXX_STANDARD 17)

add_executable(fp_either fp_either.cpp)
add_executable(fp_optional_bind fp_optional_bind.cpp)
add_executable(polymorphism_runtime polymorphism_runtime.cpp)
add_executable(polymorphism_static_crtp polymorphism_static_crtp.cpp)
