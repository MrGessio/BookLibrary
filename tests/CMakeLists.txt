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
        ${PROJECT_SOURCE_DIR}/users/source/User.cpp
        ${PROJECT_SOURCE_DIR}/users/source/Reader.cpp
        ${PROJECT_SOURCE_DIR}/include/Logger.h
        ${PROJECT_SOURCE_DIR}/source/Logger.cpp)
    target_include_directories(
        Userlib
            PRIVATE
                "${PROJECT_SOURCE_DIR}/users/include"
                "${PROJECT_SOURCE_DIR}/include")

add_executable(BorrowingTest BorrowingTestSuite.cpp)
target_include_directories(
    BorrowingTest
            PRIVATE
            "${PROJECT_SOURCE_DIR}/users/include"
            "${PROJECT_SOURCE_DIR}/include")
            

target_link_libraries(BorrowingTest
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

enable_testing()
add_test(
    NAME BorrowingTest
    COMMAND $<TARGET_FILE:BorrowingTest>)


add_test(
    NAME ReaderTest
    COMMAND $<TARGET_FILE:ReaderTest>)

    file(
    COPY
        ${PROJECT_SOURCE_DIR}/tests/data
    DESTINATION
        ${PROJECT_BINARY_DIR}/tests)
