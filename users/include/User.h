#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Logger.h"

class User {
public:
    void searchBook();
    void showBooks();
    void BorrowBook(const std::string &bookTitle, Logger &log);
    void ReturnBook(Logger &log);

protected:
    std::fstream libraryDoc;
};