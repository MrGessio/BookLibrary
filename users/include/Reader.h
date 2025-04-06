#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Logger.h"
#include "IBookManager.h"

class Reader : public IBookManager {
public:
    void SearchBook(const std::string &titleToSearch, const std::string &libraryPath = "library.txt") override;
    void ShowBooks(const std::string &libraryPath = "library.txt") override;
    void BorrowBook(const std::string &bookTitle, Logger &log, const std::string &libraryPath = "library.txt", const std::string &borrowedBooks = "borrowedBooks.txt") override;
    void ReturnBook(const std::string &returnTitle, Logger &log, const std::string &libraryPath = "library.txt", const std::string &borrowedBooks = "borrowedBooks.txt", const std::string &libraryPathTemp = "libraryTemp.txt", const std::string &borrowedBooksTemp = "borrowedBooksTemp.txt") override;

protected:
    std::fstream libraryDoc;

};
