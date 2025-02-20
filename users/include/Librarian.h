#pragma once
#include "User.h"


class Librarian : public User{
public:
    void ListOfBorrowedBooks();
    void ListOfOverdueBooks();
};