#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "../../include/Logger.h"
#include "../../include/IBookManager.h"

class Reader : public IBookManager {
public:
    void searchBook() override;
    void showBooks() override;
    void BorrowBook(const std::string &bookTitle, Logger &log) override;
    void ReturnBook(Logger &log) override;

protected:
    std::fstream libraryDoc;

};