#pragma once
#include <string>
#include "Logger.h"

class IBookManager{
public:
    virtual void SearchBook() = 0;
    virtual void ShowBooks() = 0;
    virtual void BorrowBook(const std::string &bookTitle, Logger &log) = 0;
    virtual void ReturnBook(Logger &log) = 0;

    virtual ~IBookManager() = default;
};
