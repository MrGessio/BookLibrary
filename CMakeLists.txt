cmake_minimum_required(VERSION 3.22)

project(BookLibrary)
add_executable(out
  main.cpp
  source/Book.cpp
  source/Logger.cpp
  users/source/User.cpp
  users/source/Admin.cpp
  users/source/Reader.cpp
  )
target_include_directories(out PUBLIC ${PROJECT_SOURCE_DIR}/users/include ${PROJECT_SOURCE_DIR}/include)
set_property(TARGET out PROPERTY COMPILE_WARNING_AS_ERROR ON)
