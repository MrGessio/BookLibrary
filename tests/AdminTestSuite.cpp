#include <gtest/gtest.h>
#include "Admin.h"
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class AdminTestSuite : public ::testing::Test {
    protected:
    std::vector<std::string> files = {"data/Library.txt", "data/LibraryTemp.txt", "data/Users.txt", "data/BorrowedBooks.txt", "data/BorrowedBooksTemp.txt"};
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

        std::ofstream libraryFileTemp("data/LibraryTemp.txt", std::ios::trunc);
        //filling up a txt with books
        std::ofstream libraryFile("data/Library.txt", std::ios::trunc);
        if (libraryFile.is_open()) {
            libraryFile << "Przedwiosnie, Stefan Zeromski, 1924, available\n";
            libraryFile << "Lalka, Boleslaw Prus, 1890, available\n";
            libraryFile << "Ferdydurke, Witold Gombrowicz, 1937, available\n";
            libraryFile << "Pan Tadeusz, Adam Mickiewicz, 1834, available\n";
            libraryFile << "Kamienie na szaniec, Aleksander Kaminski, 1943, available\n";
            libraryFile.close();
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

TEST_F(AdminTestSuite, ShouldAddABook) {

    std::string libraryPath = "data/Library.txt";
    std::string bookName = "Krzyzacy";
    std::string author = "Sienkiewicz";
    int year = 1900;
    std::string status = ", available";
        
    Admin admin;

    std::ifstream libraryFile(libraryPath);
    std::string libraryContentBefore((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    libraryFile.close();
    std::cout << "Library Content BEFORE adding:\n" << libraryContentBefore << "\n" << std::endl;

    admin.AddBook(bookName, author, year, status, libraryPath);

    std::ifstream libraryFileAfter(libraryPath);
    std::string libraryContentAfter((std::istreambuf_iterator<char>(libraryFileAfter)), std::istreambuf_iterator<char>());
    libraryFileAfter.close();
    std::cout << "Library Content AFTER adding:\n" << libraryContentAfter << "\n" << std::endl;

    std::string expectedContent = 
    "Przedwiosnie, Stefan Zeromski, 1924, available\n"
    "Lalka, Boleslaw Prus, 1890, available\n"
    "Ferdydurke, Witold Gombrowicz, 1937, available\n"
    "Pan Tadeusz, Adam Mickiewicz, 1834, available\n"
    "Kamienie na szaniec, Aleksander Kaminski, 1943, available\n"
    "Krzyzacy, Sienkiewicz, 1900, available\n";

    ASSERT_EQ(libraryContentAfter, expectedContent); 
}

TEST_F(AdminTestSuite, ShouldDeleteABook){
    std::string libraryPath = "data/Library.txt";
    std::string libraryPathTemp = "data/LibraryTemp.txt";
    std::string bookName = "Przedwiosnie";
    
    Admin admin;

    std::ifstream libraryFile(libraryPath);
    std::string libraryContentBefore((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    libraryFile.close();
    std::cout << "Library content BEFORE deleting:\n'" << libraryContentBefore << "\n" << std::endl;

    admin.DeleteBook(bookName, libraryPath, libraryPathTemp);

    std::ifstream libraryFileAfter(libraryPath);
    std::string libraryContentAfter((std::istreambuf_iterator<char>(libraryFileAfter)), std::istreambuf_iterator<char>());
    libraryFileAfter.close();
    std::cout << "Library content AFTER deleting:\n'" << libraryContentAfter << "\n" << std::endl;

    
    std::string expectedContent = 
    "Lalka, Boleslaw Prus, 1890, available\n"
    "Ferdydurke, Witold Gombrowicz, 1937, available\n"
    "Pan Tadeusz, Adam Mickiewicz, 1834, available\n"
    "Kamienie na szaniec, Aleksander Kaminski, 1943, available\n";

    ASSERT_EQ(libraryContentAfter, expectedContent); 
}

TEST_F(AdminTestSuite, ShouldUpdateABook){
    std::string libraryPath = "data/Library.txt";
    std::string libraryPathTemp = "data/LibraryTemp.txt";
    std::string bookName = "Przedwiosnie";

    Admin admin;

    std::ifstream libraryFile(libraryPath);
    std::string libraryContentBefore((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    libraryFile.close();
    std::cout << "Library content BEFORE updating:\n'" << libraryContentBefore << "\n" << std::endl;

    admin.UpdateBook(bookName, libraryPath, libraryPathTemp);
}

