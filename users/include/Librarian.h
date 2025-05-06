#pragma once
#include "User.h"


class Librarian : public User{
public:
    void ListOfBorrowedBooks(const std::string &borrowedPath = "borrowedBooks.txt");
    void ListOfOverdueBooks(const std::string &borrowedPath = "borrowedBooks.txt");
};
