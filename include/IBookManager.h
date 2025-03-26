#pragma once
#include <string>
#include "Logger.h"

class IBookManager{
public:
    virtual void SearchBook() = 0;
    virtual void ShowBooks() = 0;
    virtual void BorrowBook(const std::string &bookTitle, Logger &log, const std::string &libraryFile = "library.txt", const std::string &borrowedBooks = "borrowedBooks.txt") = 0;
    virtual void ReturnBook(Logger &log) = 0;

    virtual ~IBookManager() = default;
};
