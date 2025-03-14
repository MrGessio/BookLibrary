#pragma once
#include "Book.h"
#include "Librarian.h"
#include <fstream>
#include <iostream>

class Admin: public Librarian{
public:
    void AddBook();
    void DeleteBook();
    void UpdateBook();
    int GetValidYear();
};
