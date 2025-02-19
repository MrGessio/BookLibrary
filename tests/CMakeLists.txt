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
        ${PROJECT_SOURCE_DIR}/users/source/User.cpp
        ${PROJECT_SOURCE_DIR}/include/Logger.h
        ${PROJECT_SOURCE_DIR}/source/Logger.cpp)
    target_include_directories(
        Userlib
            PRIVATE
                "${PROJECT_SOURCE_DIR}/users/include")

add_executable(testUser testUser.cpp)
target_include_directories(
    testUser
            PRIVATE
                "${PROJECT_SOURCE_DIR}/users/include")

target_link_libraries(testUser
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        Userlib)

enable_testing()
add_test(
    NAME testUser
    COMMAND $<TARGET_FILE:testUser>)