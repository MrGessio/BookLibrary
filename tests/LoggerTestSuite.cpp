#include <gtest/gtest.h>
#include "Logger.h"
#include <fstream>


class LoggerTestSuite : public ::testing:: Test {
    void SetUp() override {
        std::ofstream file("test_users.txt");
        file << "admin admin\n";
        file << "user1 1234\n";
        file.close();
    }

    void TearDown() override {
        std::remove("test_users.txt");
    }
};

TEST_F(LoggerTestSuite, TestGetUsernameAndPAssword) {
    Logger logger;
    logger.LogIn("admin", "admin");

    EXPECT_EQ(logger.getUsername(), "admin");
    EXPECT_EQ(logger.getPassword(), "admin");
}

TEST_F(LoggerTestSuite, TestValidUserLogin) {
    Logger logger;
    logger.LogIn("admin", "admin");

    EXPECT_TRUE(logger.IsValidUser("test_users.txt"));
}

TEST_F(LoggerTestSuite, TestInValidUserLogin) {
    Logger logger;
    logger.LogIn("admin1", "admin");
    EXPECT_FALSE(logger.IsValidUser("test_users.txt"));
}

TEST_F(LoggerTestSuite, TestInValidUserPassword) {
    Logger logger;
    logger.LogIn("admin", "admin1");
    EXPECT_FALSE(logger.IsValidUser("test_users.txt"));
}
