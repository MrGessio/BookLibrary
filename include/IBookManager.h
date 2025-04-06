#pragma once
#include <string>
#include "Logger.h"

class IBookManager{
public:
    virtual void SearchBook(const std::string &titleToSearch, const std::string &libraryPath = "library.txt") = 0;
    virtual void ShowBooks(const std::string &libraryFile = "library.txt") = 0;
    virtual void BorrowBook(const std::string &bookTitle, Logger &log, const std::string &libraryFile = "library.txt", const std::string &borrowedBooks = "borrowedBooks.txt") = 0;
    virtual void ReturnBook(const std::string &returnTitle, Logger &log, const std::string &libraryPath = "library.txt", const std::string &borrowedBooks = "borrowedBooks.txt", const std::string &libraryPathTemp = "libraryTemp.txt", const std::string &borrowedBooksTemp = "borrowedBooksTemp.txt") = 0;

    virtual ~IBookManager() = default;
};
