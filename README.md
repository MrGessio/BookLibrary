# BookLibrary

A C++ library management system built with object-oriented design principles, file-based persistence, and unit-tested with Google Test.

## Overview

BookLibrary simulates a real library system with role-based access control. Different user types (Reader, Librarian, Admin) have different permissions, implemented through class inheritance and a pure virtual interface. All data is persisted to text files.

## Features

- **Borrow & return books** with date tracking and overdue detection
- **Search books** by title
- **User authentication** via login/password validation
- **Role-based access:**
  - `Reader` - browse, search, borrow, return books
  - `Librarian` - view borrowed books, detect overdue loans (14-day limit)
  - `Admin` - add, delete, update books in the library
- **User management** - add, delete, display users (Admin)
- **File persistence** - all data stored in `.txt` files (library, borrowed books, users)

## Architecture

```
IBookManager (pure virtual interface)
    └── Reader (implements: borrow, return, search, show)

User
    └── Librarian (list borrowed, list overdue)
            └── Admin (add, delete, update books)

Logger      - authentication, login/password validation
Book        - data model with getters/setters
UsersData   - user data model
```

## Tech Stack

- **C++17**
- **CMake** build system
- **Google Test (GTest)** - unit testing
- **File I/O** - `std::fstream`, `std::ifstream`, `std::ofstream`
- **OOP** - inheritance, polymorphism, pure virtual interface (`IBookManager`)
- **STL** - `std::vector`, `std::find_if`, lambdas, `std::istringstream`

## Test Suites

| Suite | What is tested |
|-------|----------------|
| `BookTestSuite` | Book constructor, getters, setters, validation |
| `LoggerTestSuite` | Login, user validation against file |
| `ReaderTestSuite` | BorrowBook, ReturnBook, SearchBook, ShowBooks |
| `LibrarianTestSuite` | ListOfBorrowedBooks, ListOfOverdueBooks |
| `AdminTestSuite` | AddBook, DeleteBook, UpdateBook |
| `UserTestSuite` | AddUser, DeleteUser, IsUsernameTaken, DisplayUsers |
| `UsersDataTestSuite` | UsersData getters |

## Build & Run

```bash
# Clone the repository
git clone https://github.com/MrGessio/BookLibrary.git
cd BookLibrary

# Build
mkdir build && cd build
cmake ..
make

# Run the application
./BookLibrary

# Run tests
./tests/BookLibraryTests
```

## Requirements

- C++17 or newer
- CMake 3.10+
- Google Test (fetched automatically via CMake if not installed)

## Author

MrGessio - Mechatronics Engineer with experience in C++, CMake, and test-driven development.
