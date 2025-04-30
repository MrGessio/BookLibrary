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


TEST_F(ReaderTestSuite, ShouldShowBooks) {
    std::string libraryPath = "data/Library.txt";

    Reader reader;

    std::ifstream libraryFile(libraryPath);
    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    libraryFile.close();

    reader.ShowBooks(libraryPath);
}

TEST_F(ReaderTestSuite, ShouldBorrowBookIfAvailable) {
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/Library.txt";
    std::string borrowedPath = "data/BorrowedBooks.txt";

    if (fs::exists(borrowedPath)) {
        fs::remove(borrowedPath);
    }

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

    std::ifstream libraryFile(libraryPath);
    std::ifstream borrowedFile(borrowedPath);

    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    std::string borrowedContent((std::istreambuf_iterator<char>(borrowedFile)), std::istreambuf_iterator<char>());

    libraryFile.close();
    borrowedFile.close();

    std::string expectedBorrowedContent = logger.getUsername() + ", Przedwiosnie, 2025-04-18\n";

    std::cout << "Library Content AFTER:\n" << libraryContent << std::endl;
    std::cout << "Borrowed Content AFTER:\n" << borrowedContent << std::endl;

    std::string expectedContent = 
    "Przedwiosnie, Stefan Zeromski, 1924, not available\n"
    "Lalka, Boleslaw Prus, 1890, available\n"
    "Ferdydurke, Witold Gombrowicz, 1937, available\n"
    "Pan Tadeusz, Adam Mickiewicz, 1834, available\n"
    "Kamienie na szaniec, Aleksander Kaminski, 1943, available\n";

    ASSERT_EQ(libraryContent, expectedContent); 
    ASSERT_EQ(borrowedContent,expectedBorrowedContent);
}


TEST_F(ReaderTestSuite, ShouldNotBorrowBookIfNotAvailable) {
    
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/Library.txt";
    std::string borrowedPath = "data/BorrowedBooks.txt";

    if (fs::exists(borrowedPath)) {
        fs::remove(borrowedPath);
    }

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

    std::string expectedBorrowedContent = logger.getUsername() + ", Przedwiosnie, 2025-04-18\n";

    std::cout << "Library Content AFTER borrowing:\n" << libraryContent << std::endl;
    std::cout << "Borrowed Content AFTER borrowing:\n" << borrowedContent << std::endl;


    std::cout << "startin test BORROWING N0T AVAILABLE BOOK\n" << std::endl;

    EXPECT_THROW(reader.BorrowBook(BookName, logger, libraryPath, borrowedPath), std::runtime_error);

    std::ifstream libraryFileNA(libraryPath);
    std::ifstream borrowedFileNA(borrowedPath);
    
    std::string libraryContentNA((std::istreambuf_iterator<char>(libraryFileNA)), std::istreambuf_iterator<char>());
    std::string borrowedContentNA((std::istreambuf_iterator<char>(borrowedFileNA)), std::istreambuf_iterator<char>());

    libraryFileNA.close();
    borrowedFileNA.close();

    std::string expectedLibraryContentNA = "Przedwiosnie, Stefan Zeromski, 1924, not available\n"
                                      "Lalka, Boleslaw Prus, 1890, available\n"
                                      "Ferdydurke, Witold Gombrowicz, 1937, available\n"
                                      "Pan Tadeusz, Adam Mickiewicz, 1834, available\n"
                                      "Kamienie na szaniec, Aleksander Kaminski, 1943, available\n";
;
    std::string expectedBorrowedContentNA = "default, Przedwiosnie, 2025-04-18\n";

    ASSERT_EQ(libraryContentNA, expectedLibraryContentNA);
    ASSERT_EQ(borrowedContentNA,expectedBorrowedContentNA);
}


TEST_F(ReaderTestSuite, ShouldNotBorrowWhenWrongName) {
    std::string BookName = "Przedw"; //incorrect bookname
    std::string libraryPath = "data/Library.txt";
    std::string borrowedPath = "data/BorrowedBooks.txt";


    if (fs::exists(borrowedPath)) {
        fs::remove(borrowedPath);
    }

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

    EXPECT_NO_THROW(reader.BorrowBook(BookName, logger, libraryPath, borrowedPath));


    std::ifstream libraryFile(libraryPath);
    std::ifstream borrowedFile(borrowedPath);

    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    std::string borrowedContent((std::istreambuf_iterator<char>(borrowedFile)), std::istreambuf_iterator<char>());

    libraryFile.close();
    borrowedFile.close();

    std::string expectedBorrowedContent = logger.getUsername() + ", Przedwiosnie, 2025-04-18\n";

    std::cout << "Library Content AFTER:\n" << libraryContent << std::endl;
    std::cout << "Borrowed Content AFTER:\n" << borrowedContent << std::endl;

    ASSERT_EQ(libraryContentBefore, libraryContent);
    ASSERT_EQ(borrowedContentBefore, borrowedContent);
}

TEST_F(ReaderTestSuite, ShouldFindABook) {
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/Library.txt";

    Reader reader;

    std::ifstream libraryFile(libraryPath);
    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    libraryFile.close();

    reader.SearchBook(BookName, libraryPath);
}


TEST_F(ReaderTestSuite, ShouldNotFindABook) {
    std::string BookName = "Przed";
    std::string libraryPath = "data/Library.txt";

    Reader reader;

    std::ifstream libraryFile(libraryPath);
    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    libraryFile.close();

    EXPECT_THROW(reader.SearchBook(BookName, libraryPath), std::runtime_error);
}

TEST_F(ReaderTestSuite, ShouldReturnABook){
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/Library.txt";
    std::string libraryPathTemp = "data/LibraryTemp.txt";
    std::string borrowedPath = "data/BorrowedBooks.txt";
    std::string borrowedPathTemp = "data/BorrowedBooksTemp.txt";


    if (fs::exists(borrowedPath)) {
        fs::remove(borrowedPath);
    }

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

    std::ifstream libraryFile(libraryPath);
    std::ifstream borrowedFile(borrowedPath);

    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    std::string borrowedContent((std::istreambuf_iterator<char>(borrowedFile)), std::istreambuf_iterator<char>());

    libraryFile.close();
    borrowedFile.close();
    std::cout << "\n" << std::endl;
    std::string expectedBorrowedContent = logger.getUsername() + ", Przedwiosnie, 2025-04-18\n";

    std::cout << "Library Content AFTER:\n" << libraryContent << std::endl;
    std::cout << "Borrowed Content AFTER:\n" << borrowedContent << std::endl;

/////
    EXPECT_NO_THROW(reader.ReturnBook(BookName, logger, libraryPath, borrowedPath, libraryPathTemp, borrowedPathTemp));
    
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

TEST_F(ReaderTestSuite, ShouldNotReturnABookWhenWrongTitle){
    std::string BookName = "Przedwiosnie";
    std::string BookNameReturn = "Przed";
    std::string libraryPath = "data/Library.txt";
    std::string libraryPathTemp = "data/LibraryTemp.txt";
    std::string borrowedPath = "data/BorrowedBooks.txt";
    std::string borrowedPathTemp = "data/BorrowedBooksTemp.txt";


    if (fs::exists(borrowedPath)) {
        fs::remove(borrowedPath);
    }

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

    std::ifstream libraryFile(libraryPath);
    std::ifstream borrowedFile(borrowedPath);

    std::string libraryContent((std::istreambuf_iterator<char>(libraryFile)), std::istreambuf_iterator<char>());
    std::string borrowedContent((std::istreambuf_iterator<char>(borrowedFile)), std::istreambuf_iterator<char>());

    libraryFile.close();
    borrowedFile.close();
    std::cout << "\n" << std::endl;
    std::string expectedBorrowedContent = logger.getUsername() + ", Przedwiosnie, 2025-04-18\n";

    std::cout << "Library Content AFTER:\n" << libraryContent << std::endl;
    std::cout << "Borrowed Content AFTER:\n" << borrowedContent << std::endl;

/////
    EXPECT_THROW(reader.ReturnBook(BookNameReturn, logger, libraryPath, borrowedPath, libraryPathTemp, borrowedPathTemp), std::runtime_error);
    
    std::ifstream libraryFileAfter(libraryPath);
    std::string libraryContentAfter((std::istreambuf_iterator<char>(libraryFileAfter)), std::istreambuf_iterator<char>());
    libraryFileAfter.close(); 
    std::cout << "Library Content AFTER returning:\n" << libraryContentAfter << std::endl;

    std::ifstream borrowedFileAfter(borrowedPath);
    std::string borrowedContentAfter((std::istreambuf_iterator<char>(borrowedFileAfter)), std::istreambuf_iterator<char>());
    borrowedFileAfter.close();
    std::cout << "Borrowed Content AFTER returning:\n" << borrowedContentAfter << std::endl;

    std::string expectedLibraryContentWT = "Przedwiosnie, Stefan Zeromski, 1924, not available\n"
                                      "Lalka, Boleslaw Prus, 1890, available\n"
                                      "Ferdydurke, Witold Gombrowicz, 1937, available\n"
                                      "Pan Tadeusz, Adam Mickiewicz, 1834, available\n"
                                      "Kamienie na szaniec, Aleksander Kaminski, 1943, available\n";
    std::string expectedBorrowedContentWT = logger.getUsername() + ", Przedwiosnie, 2025-04-18\n";

    ASSERT_EQ(libraryContentAfter, expectedLibraryContentWT);
    ASSERT_EQ(borrowedContentAfter, expectedBorrowedContentWT);
}


TEST_F(ReaderTestSuite, ShouldNotReturnABookWhenNotBorrowed){
   
    std::string BookName = "Przedwiosnie";
    std::string libraryPath = "data/Library.txt";
    std::string libraryPathTemp = "data/LibraryTemp.txt";
    std::string borrowedPath = "data/BorrowedBooks.txt";
    std::string borrowedPathTemp = "data/BorrowedBooksTemp.txt";


    if (fs::exists(borrowedPath)) {
        fs::remove(borrowedPath);
    }
    
    std::ofstream createEmpty(borrowedPath, std::ios::trunc);
    createEmpty.close();

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

  
    EXPECT_THROW(reader.ReturnBook(BookName, logger, libraryPath, borrowedPath, libraryPathTemp, borrowedPathTemp), std::runtime_error);
    
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

