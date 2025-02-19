#include <gtest/gtest.h>
#include "../users/include/User.h"
#include "../include/Logger.h"

class UserTest : public ::testing::Test{
    protected:
    void SetUp() override{
        std::ofstream libraryFile("libraryTest.txt");
        libraryFile << "Przedwiosnie, Stefan Zeromski, 1924, not available" << std::endl;
        libraryFile << "Lalka, Prus, 1890, available" << std::endl;
        libraryFile.close();

        std::ofstream borrowedFile("borrowedBooksTest.txt");
        borrowedFile << "userTest, Przedwiosnie, 2025-01-05" << std::endl;
        borrowedFile.close();
    }

    void TearDown() override{

        std::remove("libraryTest.txt");
        std::remove("borrowedBooksTest.txt");
    }
}; //

TEST_F(UserTest, debug1) {
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
}
