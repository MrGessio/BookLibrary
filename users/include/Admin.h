#pragma once
#include "Book.h"
#include "Librarian.h"
#include <fstream>
#include <iostream>

class Admin: public Librarian{
public:
    void addBook();
    void deleteBook();
    void UpdateBook();
    int GetValidYear();
};