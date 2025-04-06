#include <gtest/gtest.h>
#include "Logger.h"
#include "Reader.h"
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class ReaderTestSuite : public ::testing::Test {
    protected:
    std::vector<std::string> files = {"data/AvailableBook.txt", "data/BorrowedBook.txt", "data/NotAvailableBook.txt", "data/NotAvailableBookTemp.txt", "data/UnBorrowedBook.txt", "data/BorrowedBookTemp.txt"};
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

TEST_F(ReaderTestSuite, ShouldBorrowBookIfAvailable) {
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/AvailableBook.txt";
    std::string borrowedPath = "data/UnBorrowedBook.txt";

    std::ofstream clearFile(borrowedPath, std::ios::trunc);
    clearFile.close();

    Logger logger;
    Reader reader;

    std::ifstream libraryFileBefore(libraryPath);
    std::string libraryContentBefore((std::istreambuf_iterator<char>(libraryFileBefore)), std::istreambuf_iterator<char>());
    libraryFileBefore.close();
    std::cout << "Library Content BEFORE borrowing:\n" << libraryContentBefore << "\n" << std::endl;
    
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
//
    std::string expectedLibraryContent = "Przedwiosnie, Stefan Zeromski, 1924,not available\n";
    std::string expectedBorrowedContent = logger.getUsername() + ", Przedwiosnie, 2025-04-06\n";

    std::cout << "Library Content:\n" << libraryContent << std::endl;
    std::cout << "Borrowed Content:\n" << borrowedContent << std::endl;

    ASSERT_EQ(libraryContent, expectedLibraryContent);
    ASSERT_EQ(borrowedContent,expectedBorrowedContent);
}


TEST_F(ReaderTestSuite, ShouldNotBorrowBookIfNotAvailable) {
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/NotAvailableBook.txt";
    std::string borrowedPath = "data/BorrowedBook.txt";

    Logger logger;
    Reader reader;

    EXPECT_THROW(reader.BorrowBook(BookName, logger, libraryPath, borrowedPath), std::runtime_error);

    std::ifstream libraryFile(libraryPath);
    std::ifstream borrowedFile(borrowedPath);
    
    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    std::string borrowedContent((std::istreambuf_iterator<char>(borrowedFile)), std::istreambuf_iterator<char>());

    libraryFile.close();
    borrowedFile.close();

    std::string expectedLibraryContent = "Przedwiosnie, Stefan Zeromski, 1924, not available";
    std::string expectedBorrowedContent = "";

    ASSERT_EQ(libraryContent, expectedLibraryContent);
    ASSERT_EQ(borrowedContent,expectedBorrowedContent);
}


TEST_F(ReaderTestSuite, ShouldNotBorrowWhenWrongName) {
    std::string BookName = "Przedw"; //incorrect bookname
    std::string libraryPath = "data/AvailableBook.txt";
    std::string borrowedPath = "data/BorrowedBook.txt";

    Logger logger;
    Reader reader;

    //opening files
    std::ifstream libraryFileBefore(libraryPath);
    std::string libraryContentBefore((std::istreambuf_iterator<char>(libraryFileBefore)), std::istreambuf_iterator<char>());
    libraryFileBefore.close();

    std::ifstream borrowedFileBefore(borrowedPath);
    std::string borrowedContentBefore((std::istreambuf_iterator<char>(borrowedFileBefore)), std::istreambuf_iterator<char>());
    borrowedFileBefore.close();

    std::cout << "Library Content BEFORE:\n" << libraryContentBefore << "\n" << std::endl;
    std::cout << "Borrowed Content BEFORE:\n" << borrowedContentBefore << "\n" << std::endl;

    EXPECT_NO_THROW(reader.BorrowBook(BookName, logger, libraryPath, borrowedPath));

    //Reading file contents after a borrowing attempt.
    std::ifstream libraryFileAFTER(libraryPath);
    std::string libraryContentAFTER((std::istreambuf_iterator<char>(libraryFileAFTER)), std::istreambuf_iterator<char>());
    libraryFileAFTER.close();

    std::ifstream borrowedFileAFTER(borrowedPath);
    std::string borrowedContentAFTER((std::istreambuf_iterator<char>(borrowedFileAFTER)), std::istreambuf_iterator<char>());
    borrowedFileAFTER.close();

    std::cout << "Library Content AFTER:\n" << libraryContentAFTER << "\n" << std::endl;
    std::cout << "Borrowed Content AFTER:\n" << borrowedContentAFTER << "\n" << std::endl;

    ASSERT_EQ(libraryContentBefore, libraryContentAFTER);
    ASSERT_EQ(borrowedContentBefore, borrowedContentAFTER);
}

TEST_F(ReaderTestSuite, ShouldFindABook) {
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/AvailableBook.txt";

    Reader reader;

    std::ifstream libraryFile(libraryPath);
    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    libraryFile.close();

    reader.SearchBook(BookName, libraryPath);
}

TEST_F(ReaderTestSuite, ShouldNotFindABook) {
    std::string BookName = "Przed";
    std::string libraryPath = "data/AvailableBook.txt";

    Reader reader;

    std::ifstream libraryFile(libraryPath);
    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    libraryFile.close();

    EXPECT_THROW(reader.SearchBook(BookName, libraryPath), std::runtime_error);
}


TEST_F(ReaderTestSuite, ShouldShowBooks) {
    std::string libraryPath = "data/AvailableBook.txt";

    Reader reader;

    std::ifstream libraryFile(libraryPath);
    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    libraryFile.close();

    reader.ShowBooks(libraryPath);
}

TEST_F(ReaderTestSuite, ShouldReturnABook){
    std::string BookName = "Przedwiosnie";
    std::string borrowedPath = "data/BorrowedBook.txt";
    std::string borrowedPathTemp = "data/BorrowedBookTemp.txt";
    std::string libraryPath = "data/NotAvailableBook.txt";
    std::string libraryPathTemp = "data/NotAvailableBookTemp.txt";
    

    Logger logger;
    Reader reader;

    std::ifstream libraryFileBefore(libraryPath);
    std::string libraryContentBefore((std::istreambuf_iterator<char>(libraryFileBefore)), std::istreambuf_iterator<char>());
    libraryFileBefore.close();
    std::cout << "Library Content BEFORE returning:\n" << libraryContentBefore << std::endl;
    
    std::ifstream borrowedFileBefore(borrowedPath);
    std::string borrowedContentBefore((std::istreambuf_iterator<char>(borrowedFileBefore)), std::istreambuf_iterator<char>());
    borrowedFileBefore.close();
    std::cout << "Borrowed Content BEFORE returning:\n" << borrowedContentBefore << std::endl;

    EXPECT_NO_THROW(reader.ReturnBook(BookName, logger, borrowedPath, borrowedPathTemp, libraryPath, libraryPathTemp));
    
    std::ifstream libraryFileAfter(libraryPath);
    std::string libraryContentAfter((std::istreambuf_iterator<char>(libraryFileAfter)), std::istreambuf_iterator<char>());
    libraryFileAfter.close();
    std::cout << "Library Content AFTER returning:\n" << libraryContentAfter << std::endl;

    std::ifstream borrowedFileAfter(borrowedPath);
    std::string borrowedContentAfter((std::istreambuf_iterator<char>(borrowedFileAfter)), std::istreambuf_iterator<char>());
    borrowedFileAfter.close();
    std::cout << "Borrowed Content AFTER returning:\n" << borrowedContentAfter << std::endl;
    ASSERT_EQ(libraryContentBefore, libraryContentAfter);
    ASSERT_EQ(borrowedContentBefore, borrowedContentAfter);
}

//should not return

