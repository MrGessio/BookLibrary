cmake_minimum_required(VERSION 3.22)

project(BookLibrary)
add_executable(out
  main.cpp)

set_property(TARGET out
  PROPERTY COMPILE_WARNING_AS_ERROR ON)
