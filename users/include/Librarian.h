#pragma once
#include "User.h"


class Librarian : public User{
public:
    void ListOfBorrowedBooks(const std::string &borrowedPath);
    void ListOfOverdueBooks(const std::string &borrowedPath);
};
