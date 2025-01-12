#define READER_H

#include "User.h"

class Reader : public User {
public:
    void borrowBook();
    void returnBook();
};