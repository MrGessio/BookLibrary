#pragma once
#include "Book.h"
#include "Librarian.h"
#include <fstream>
#include <iostream>

class Admin: public Librarian{
public:
    void AddBook(const std::string &title, const std::string &author, int year, const std::string &status, const std::string &libraryPath = "library.txt");
    void DeleteBook(const std::string &bookToDelete, const std::string &libraryPath = "library.txt", const std::string &libraryPathTemp = "libraryTemp.txt");
    int UpdateBook(const std::string &bookToBeChanged, const std::string &libraryPath = "library.txt", const std::string &libraryPathTemp = "libraryTemp.txt");
    int GetValidYear();
};
