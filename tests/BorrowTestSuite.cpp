#include <gtest/gtest.h>
#include "Logger.h"
#include "Reader.h"
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class BorrowTestSuite : public ::testing::Test {
    protected:
    std::vector<std::string> files = {"data/OneBookTestData.txt", "data/BorrowedBook.txt"};
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

TEST_F(BorrowTestSuite, ShouldBorrowBookIfAvailable) {
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/OneBookTestData.txt";
    std::string borrowedPath = "data/BorrowedBook.txt";

    Logger logger;
    Reader reader;







    std::ifstream libraryFileBefore(libraryPath);
    std::string libraryContentBefore((std::istreambuf_iterator<char>(libraryFileBefore)), std::istreambuf_iterator<char>());
    libraryFileBefore.close();
    
    std::cout << "Library Content BEFORE borrowing:\n" << libraryContentBefore << std::endl;
    
    std::ifstream borrowedFileBefore(borrowedPath);
    std::string borrowedContentBefore((std::istreambuf_iterator<char>(borrowedFileBefore)), std::istreambuf_iterator<char>());
    borrowedFileBefore.close();
    
    std::cout << "Borrowed Content BEFORE borrowing:\n" << borrowedContentBefore << std::endl;
    








    reader.BorrowBook(BookName, logger, libraryPath, borrowedPath);

    //opening files
    std::ifstream libraryFile(libraryPath);
    std::ifstream borrowedFile(borrowedPath);

    //reading files into a string
    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    std::string borrowedContent((std::istreambuf_iterator<char>(borrowedFile)), std::istreambuf_iterator<char>());

    libraryFile.close();
    borrowedFile.close();

    std::string expectedLibraryContent = "Przedwiosnie, Stefan Zeromski, 1924, not available\n";
    std::string expectedBorrowedContent = logger.getUsername() + ", Przedwiosnie, 2025-03-25\n";

    std::cout << "xxLibrary Content:\n" << libraryContent << std::endl;
    std::cout << "Borrowed Content:\n" << borrowedContent << std::endl;

    ASSERT_EQ(libraryContent, expectedLibraryContent);
    ASSERT_EQ(borrowedContent,expectedBorrowedContent);
}


