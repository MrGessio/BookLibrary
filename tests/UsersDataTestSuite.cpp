#include <gtest/gtest.h>
#include "../include/UsersData.h"

class UsersDataTestSuite : public ::testing::Test {

};

TEST_F(UsersDataTestSuite, ConstructorsTEST){
    UsersData user("Kamil", "Grosicki", "Grosik", "1234");

    EXPECT_EQ(user.getFirstName(), "Kamil");
    EXPECT_EQ(user.getLastName(), "Grosicki");
    EXPECT_EQ(user.getUserName(), "Grosik");
    EXPECT_EQ(user.getUserPassword(), "1234");
}
