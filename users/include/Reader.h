#pragma once

#include "User.h"

class Reader : public User {
public:
    void BorrowBook();
    void ReturnBook();
};