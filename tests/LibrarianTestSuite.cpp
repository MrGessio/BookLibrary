#include <gtest/gtest.h>
#include "Admin.h"
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class LibrarianTestSuite : public ::testing::Test {
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

        std::ofstream borrowFileTemp("data/BorrowedBooksTemp.txt", std::ios::trunc);
        //filling up a txt with books
        std::ofstream borrowyFile("data/BorrowedBooks.txt", std::ios::trunc);
        if (borrowyFile.is_open()) {
            borrowyFile << "default, Przedwiosnie, 2025-03-25\n";
            borrowyFile << "default, Lalka, 2025-02-25\n";
            borrowyFile << "default, Ferdydurke, 2025-03-30\n";
            borrowyFile << "default, Kamienie na szaniec, 2025-04-19\n";
            borrowyFile.close();
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

TEST_F(LibrarianTestSuite, ShouldShowListOfBorrowedBooks) {
    std::string borrowedPath = "data/BorrowedBooks.txt";

    Librarian librarian;

    std::ifstream borrowyFile(borrowedPath);
    std::string borrowContentBefore((std::istreambuf_iterator<char>(borrowyFile)), std::istreambuf_iterator<char>());
    borrowyFile.close();
    std::cout << "borrow content BEFORE:\n'" << borrowContentBefore << "\n" << std::endl;

    librarian.ListOfBorrowedBooks(borrowedPath);

    
    std::string expectedContent = 
    "default, Przedwiosnie, 2025-03-25\n"
    "default, Lalka, 2025-02-25\n"
    "default, Ferdydurke, 2025-03-30\n"
    "default, Kamienie na szaniec, 2025-04-19\n";

    ASSERT_EQ(borrowContentBefore, expectedContent); 
}


TEST_F(LibrarianTestSuite, ShouldShowLListOfOverdueBooks) {
    std::string borrowedPath = "data/BorrowedBooks.txt";

    Librarian librarian;

    librarian.ListOfOverdueBooks(borrowedPath);

    
    std::string expectedContent = 
    "- Przedwiosnie (borrowed by: default on 2025-03-25)\n"
    "- Lalka (borrowed by: default on 2025-02-25)\n"
    "- Ferdydurke (borrowed by: default on 2025-03-30)\n";

    ASSERT_EQ(expectedContent, expectedContent); 
}
