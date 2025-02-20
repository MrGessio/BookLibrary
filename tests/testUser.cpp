/*
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

TEST_F(UserTest, ReturnBorrowedBook){
    Logger testLogger("testUser");
    User user;

    std::istringstream input("Przedwiosnie\n");
    std::cin.rdbuf(input.rdbuf());

    user.ReturnBook(testLogger);

    //testiing if the book has been removed from the file
    std::ifstream borrowedFile("borrowedBooksTest.txt");
    std::string line;
    bool found = false;
    while(std::getline(borrowedFile, line)){
        if(line.find("Przedwiosnie") != std::string::npos){
            found = true;
        }
    }
    borrowedFile.close();

    EXPECT_FALSE(found) << "The book has not been removed from borrowedBooksTest.txt.";

    // testing if the status has changed to "available"
    std::ifstream libraryFile("libraryTest.txt");
    found = false;
    while (std::getline(libraryFile, line)){
        if(line.find("Przedwiosnie") != std::string::npos && line.find("available") != std::string::npos){
           found = true; 
        }
    }
    libraryFile.close();

    EXPECT_TRUE(found) << "The status of the book in library_test.txt has not changed to available.";
}

// Test for returning a book that the user has not borrowed
TEST_F(UserTest, ReturnNotBorrowedBook){
    Logger testLogger("testUser");
    User user;

    std::istringstream input("Lalka\n");
    std::cin.rdbuf(input.rdbuf());

    user.ReturnBook(testLogger);

    //Checking if borrowedBooksTest.txt has not been modified.
    std::ifstream borrowedFile("borrowedBooksTest.txt");
    std::string line;
    std::getline(borrowedFile, line);
    borrowedFile.close();

    EXPECT_EQ(line, "testUser, Przedwiosnie, 2025-01-05")
        << "The file borrowedBooksTest.txt has been modified, even though the book was not borrowed.";

        //Checking if libraryTest.txt has not been modified.
        std::ifstream libraryFile("libraryTest.txt");
        std::string libraryLine;
        bool statusChanged = false;

        while(std::getline(libraryFile, libraryLine)){
            if(libraryLine.find("Lalka") != std::string::npos && libraryLine.find("not available") != std::string::npos){
                statusChanged = true;
            }
        }
        libraryFile.close();
        EXPECT_FALSE(statusChanged) << "The status of the book in libraryTest.txt should not change.";
}