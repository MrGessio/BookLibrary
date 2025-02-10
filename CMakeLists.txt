cmake_minimum_required(VERSION 3.22)

if (COVERAGE)
    message("Building with code coverage enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

project(BookLibrary)
add_executable(out
  main.cpp
  source/Book.cpp
  source/Logger.cpp
  users/source/User.cpp
  users/source/Admin.cpp
  users/source/Reader.cpp
  users/source/Librarian.cpp
  users/source/UsersData.cpp
  )
target_include_directories(out PUBLIC ${PROJECT_SOURCE_DIR}/users/include ${PROJECT_SOURCE_DIR}/include)
add_subdirectory(
  tests
)