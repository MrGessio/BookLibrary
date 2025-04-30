#pragma once
#include "Book.h"
#include "Librarian.h"
#include <fstream>
#include <iostream>

class Admin: public Librarian{
public:
    void AddBook(const std::string &title, const std::string &author, int year, const std::string &status, const std::string &libraryPath);
    void DeleteBook(const std::string &bookToDelete, const std::string &libraryPath, const std::string &libraryPathTemp);
    void UpdateBook(const std::string &bookToBeChanged, const std::string &libraryPath, const std::string &libraryPathTemp);
    int GetValidYear();
};
