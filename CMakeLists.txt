cmake_minimum_required(VERSION 3.22)

project(BookLibrary)
add_executable(out
  main.cpp
  source/Book.cpp
  source/Logger.cpp
  source/User.cpp
  source/Admin.cpp
  )

set_property(TARGET out PROPERTY COMPILE_WARNING_AS_ERROR ON)
