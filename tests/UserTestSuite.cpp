#include <gtest/gtest.h>
#include "User.h"
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class UserTestSuite : public ::testing::Test {
    protected:
    std::vector<std::string> files = {"data/Users.txt"};
    std::vector<std::string> backupFiles;
            
    void SetUp() override {
        //creating backup files
        for (const auto& file : files) {
            std::string backupFile = file + ".bak";
            backupFiles.push_back(backupFile);
            if (fs::exists(file)) {
                fs::copy(file, backupFile, fs::copy_options::overwrite_existing);

            }
        }

        std::ofstream usersFileTemp("data/Users.txt", std::ios::trunc);
        //filling up a txt with books
        std::ofstream usersFile("data/Users.txt", std::ios::trunc);
        if (usersFile.is_open()) {
            usersFile << "lewy 1234 Robert Lewandowski\n";
            usersFile << "wojtus 1234 Wojciech Szczesny\n";
            usersFile << "admin admin admin admin\n";
            usersFile.close();
        }
    }

    void TearDown() override {
        //bringing back the original files
        for (size_t i = 0; i < files.size(); ++i){
            if (fs::exists(backupFiles[i])) {
                fs::copy(backupFiles[i], files[i], fs::copy_options::overwrite_existing);
                fs::remove(backupFiles[i]);
            }
        }
    }
};

TEST_F(UserTestSuite, ShouldLoadUsers) {
    std::string usersPath = "data/Users.txt";
    User user;
    std::ifstream usersFile(usersPath);
    ASSERT_TRUE(usersFile.is_open()) << "Failed to open users file.";
    std::string usersContent((std::istreambuf_iterator<char>(usersFile)), std::istreambuf_iterator<char>());
    std::cout << "Users content: \n" << usersContent << "\n" << std::endl;
    usersFile.close();

    user.LoadUsers(usersPath);
    
    std::string expectedContent =
        "lewy 1234 Robert Lewandowski\n"
        "wojtus 1234 Wojciech Szczesny\n"
        "admin admin admin admin\n";

    ASSERT_EQ(usersContent, expectedContent) << "File content after LoadUsers is not as expected.";

};

TEST_F(UserTestSuite, ShouldSaveUsers) {
    std::string usersPath = "data/Users.txt";
    User user;
    std::ifstream usersFileBeforeAdding(usersPath);
    ASSERT_TRUE(usersFileBeforeAdding.is_open()) << "Failed to open users file.";
    std::string usersContentBeforeAdding((std::istreambuf_iterator<char>(usersFileBeforeAdding)), std::istreambuf_iterator<char>());
    std::cout << "Users content before adding: \n" << usersContentBeforeAdding << "\n" << std::endl;
    usersFileBeforeAdding.close();

    user.AddUser("user1", "pass1", "First1", "Last1", usersPath);
    user.AddUser("user2", "pass2", "First2", "Last2", usersPath);

    std::ifstream usersFileAfterAdding(usersPath);
    std::string usersContentAfterAdding((std::istreambuf_iterator<char>(usersFileAfterAdding)), std::istreambuf_iterator<char>());
    std::cout << "Users content after adding: \n" << usersContentAfterAdding << "\n" << std::endl;
    usersFileAfterAdding.close();

    user.SaveUsers(usersPath);

    std::string expectedContent =
        "lewy 1234 Robert Lewandowski\n"
        "wojtus 1234 Wojciech Szczesny\n"
        "admin admin admin admin\n"
        "user1 pass1 First1 Last1\n"
        "user2 pass2 First2 Last2\n";

    ASSERT_EQ(usersContentAfterAdding, expectedContent) << "File content after SaveUsers is not as expected.";
}

TEST_F(UserTestSuite, ShouldDetectTakenUsername){
    User user;
    std::string usersPath = "data/Users.txt";
    std::string username = "lewy";

    bool isTaken = user.IsUsernameTaken(username, usersPath);

    ASSERT_TRUE(isTaken) << "Expected username 'lewy' to be taken, but its not";
}

TEST_F(UserTestSuite, ShouldAddUser){

    std::string usersPath = "data/Users.txt";
    User user;

    std::string username = "username";
    std::string password = "password";
    std::string firstname = "firstname";
    std::string lastname = "lastname";

    std::ifstream usersFile(usersPath);
    std::string usersContentBefore((std::istreambuf_iterator<char>(usersFile)), std::istreambuf_iterator<char>());
    usersFile.close();
    std::cout << "Users content before: \n" << usersContentBefore << "\n" << std::endl;
    
    user.AddUser(username, password, firstname, lastname, usersPath);

    std::ifstream usersFileAfter(usersPath);
    std::string usersContentAfter((std::istreambuf_iterator<char>(usersFileAfter)), std::istreambuf_iterator<char>());
    usersFile.close();
    std::cout << "Users content after: \n" << usersContentAfter << "\n" << std::endl;

    std::string expectedContent =
    "lewy 1234 Robert Lewandowski\n"
    "wojtus 1234 Wojciech Szczesny\n"
    "admin admin admin admin\n"
    "username password firstname lastname\n";
    ASSERT_EQ(usersContentAfter, expectedContent);
}



TEST_F(UserTestSuite, ShouldNotAddUser){

    std::string usersPath = "data/Users.txt";
    User user;

    std::string username = "lewy";
    std::string password = "password";
    std::string firstname = "firstname";
    std::string lastname = "lastname";

    std::ifstream usersFile(usersPath);
    std::string usersContentBefore((std::istreambuf_iterator<char>(usersFile)), std::istreambuf_iterator<char>());
    usersFile.close();
    std::cout << "Users content before: \n" << usersContentBefore << "\n" << std::endl;
    
    EXPECT_THROW(user.AddUser(username, password, firstname, lastname, usersPath), std::runtime_error);

    std::ifstream usersFileAfter(usersPath);
    std::string usersContentAfter((std::istreambuf_iterator<char>(usersFileAfter)), std::istreambuf_iterator<char>());
    usersFile.close();

    ASSERT_EQ(usersContentBefore, usersContentAfter);
}


TEST_F(UserTestSuite, ShouldDeleteUser){

    std::string usersPath = "data/Users.txt";
    User user;

    std::string username = "lewy";

    std::ifstream usersFile(usersPath);
    ASSERT_TRUE(usersFile.is_open()) << "Failed to open users file.";
    std::string usersContentBefore((std::istreambuf_iterator<char>(usersFile)), std::istreambuf_iterator<char>());
    usersFile.close();
    std::cout << "Users content before: \n" << usersContentBefore << "\n" << std::endl;
    
    user.DeleteUser(username, usersPath);

    std::ifstream usersFileAfter(usersPath);
    std::string usersContentAfter((std::istreambuf_iterator<char>(usersFileAfter)), std::istreambuf_iterator<char>());
    usersFile.close();
    std::cout << "Users content after: \n" << usersContentAfter << "\n" << std::endl;

    std::string expectedContent =
    "wojtus 1234 Wojciech Szczesny\n"
    "admin admin admin admin\n";
    ASSERT_EQ(usersContentAfter, expectedContent);
}




TEST_F(UserTestSuite, ShouldNotDeleteUser){

    std::string usersPath = "data/Users.txt";
    User user;

    std::string username = "krychowiak";

    std::ifstream usersFile(usersPath);
    ASSERT_TRUE(usersFile.is_open()) << "Failed to open users file.";
    std::string usersContentBefore((std::istreambuf_iterator<char>(usersFile)), std::istreambuf_iterator<char>());
    usersFile.close();
    std::cout << "Users content before: \n" << usersContentBefore << "\n" << std::endl;
    
    EXPECT_THROW(user.DeleteUser(username, usersPath), std::runtime_error);

    std::ifstream usersFileAfter(usersPath);
    std::string usersContentAfter((std::istreambuf_iterator<char>(usersFileAfter)), std::istreambuf_iterator<char>());
    usersFile.close();
    std::cout << "Users content after: \n" << usersContentAfter << "\n" << std::endl;

    std::string expectedContent =
    "lewy 1234 Robert Lewandowski\n"
    "wojtus 1234 Wojciech Szczesny\n"
    "admin admin admin admin\n";
    ASSERT_EQ(usersContentAfter, expectedContent);
}

TEST_F(UserTestSuite, ShouldDisplayUsers){
    std::string userPath = "data/Users.txt";
    User user;
    std::stringstream buffer;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf()); 

    user.DisplayUsers(userPath);

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput =
    "Number of users: 3\n"
    "List of users: \n"
    "- username: lewy, name: Robert, surname: Lewandowski\n"
    "- username: wojtus, name: Wojciech, surname: Szczesny\n"
    "- username: admin, name: admin, surname: admin\n";

    ASSERT_EQ(buffer.str(), expectedOutput);
}
