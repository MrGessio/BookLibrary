find_package(Git REQUIRED)

set(GTEST_ROOT ${PROJECT_BINARY_DIR}/googletest)

include(FetchContent)


set(GTEST_VERSION "v1.15.2")
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        ${GTEST_VERSION}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${GTEST_ROOT}
    )

    option (INSTALL_GTEST OFF)
    FetchContent_MakeAvailable(googletest)

    include_directories(${GTEST_ROOT}/users/include)
    link_directories(${GTEST_ROOT}/lib)

    set(GTest_DIR "${GTEST_ROOT}/lib/cmake/GTest")

    add_library(Userlib
        ${PROJECT_SOURCE_DIR}/users/include/User.h
        ${PROJECT_SOURCE_DIR}/users/include/Reader.h
        ${PROJECT_SOURCE_DIR}/users/include/Admin.h
        ${PROJECT_SOURCE_DIR}/users/include/Librarian.h
        ${PROJECT_SOURCE_DIR}/users/include/UsersData.h
        ${PROJECT_SOURCE_DIR}/users/source/UsersData.cpp
        ${PROJECT_SOURCE_DIR}/users/source/User.cpp
        ${PROJECT_SOURCE_DIR}/users/source/Admin.cpp
        ${PROJECT_SOURCE_DIR}/users/source/Reader.cpp
        ${PROJECT_SOURCE_DIR}/users/source/Librarian.cpp
        ${PROJECT_SOURCE_DIR}/include/Logger.h
        ${PROJECT_SOURCE_DIR}/include/Book.h
        ${PROJECT_SOURCE_DIR}/include/IBookManager.h
        ${PROJECT_SOURCE_DIR}/source/Logger.cpp
        ${PROJECT_SOURCE_DIR}/source/Book.cpp)
    target_include_directories(
        Userlib
            PRIVATE
                "${PROJECT_SOURCE_DIR}/users/include"
                "${PROJECT_SOURCE_DIR}/include")

add_executable(AdminTest AdminTestSuite.cpp)
target_include_directories(
    AdminTest
            PRIVATE
            "${PROJECT_SOURCE_DIR}/users/include"
            "${PROJECT_SOURCE_DIR}/include")
            

target_link_libraries(AdminTest
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        Userlib)
        

add_executable(BookTest BookTestSuite.cpp)
target_include_directories(
    BookTest
            PRIVATE
            "${PROJECT_SOURCE_DIR}/users/include"
            "${PROJECT_SOURCE_DIR}/include")
            

target_link_libraries(BookTest
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        Userlib)
        

add_executable(LibrarianTest LibrarianTestSuite.cpp)
target_include_directories(
    LibrarianTest
            PRIVATE
            "${PROJECT_SOURCE_DIR}/users/include"
            "${PROJECT_SOURCE_DIR}/include")
            

target_link_libraries(LibrarianTest
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        Userlib)
        


add_executable(LoggerTest LoggerTestSuite.cpp)
target_include_directories(
    LoggerTest
            PRIVATE
            "${PROJECT_SOURCE_DIR}/users/include"
            "${PROJECT_SOURCE_DIR}/include")
            

target_link_libraries(LoggerTest
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        Userlib)
        

        
add_executable(ReaderTest ReaderTestSuite.cpp)
target_include_directories(
    ReaderTest
            PRIVATE
            "${PROJECT_SOURCE_DIR}/users/include"
            "${PROJECT_SOURCE_DIR}/include")
            

target_link_libraries(ReaderTest
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        Userlib)


add_executable(UsersDataTest UsersDataTestSuite.cpp)
target_include_directories(
    UsersDataTest
            PRIVATE
            "${PROJECT_SOURCE_DIR}/users/include"
            "${PROJECT_SOURCE_DIR}/include")
            

target_link_libraries(UsersDataTest
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        Userlib)


add_executable(UserTest UserTestSuite.cpp)
target_include_directories(
    UserTest
            PRIVATE
            "${PROJECT_SOURCE_DIR}/users/include"
            "${PROJECT_SOURCE_DIR}/include")
            

target_link_libraries(UserTest
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        Userlib)

enable_testing()
add_test(
    NAME AdminTest
    COMMAND $<TARGET_FILE:AdminTest>)

add_test(
    NAME BookTest
    COMMAND $<TARGET_FILE:BookTest>)

 add_test(
    NAME LibrarianTest
    COMMAND $<TARGET_FILE:LibrarianTest>)
   
 add_test(
    NAME LoggerTest
    COMMAND $<TARGET_FILE:LoggerTest>)
   

add_test(
    NAME ReaderTest
    COMMAND $<TARGET_FILE:ReaderTest>)

add_test(
    NAME UserTest
    COMMAND $<TARGET_FILE:UserTest>)

add_test(
    NAME UsersDataTest
    COMMAND $<TARGET_FILE:UsersDataTest>)

    file(
    COPY
        ${PROJECT_SOURCE_DIR}/tests/data
    DESTINATION
        ${PROJECT_BINARY_DIR}/tests)
        