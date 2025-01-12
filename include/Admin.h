#define ADMIN_H

#include "User.h"
#include "Book.h"
#include <fstream>
#include <iostream>

class Admin : public User {
public:
    void addBook();
    void deleteBook();
};