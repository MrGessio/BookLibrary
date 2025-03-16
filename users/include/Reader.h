#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Logger.h"
#include "IBookManager.h"

class Reader : public IBookManager {
public:
    void SearchBook() override;
    void ShowBooks() override;
    void BorrowBook(const std::string &bookTitle, Logger &log) override;
    void ReturnBook(Logger &log) override;

protected:
    std::fstream libraryDoc;

};
