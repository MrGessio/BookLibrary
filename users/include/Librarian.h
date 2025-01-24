#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include "User.h"
#include "Admin.h"


struct UserInfo{
    std::string username;
    std::string password;
    std::string firstname;
    std::string lastname;
};

class Librarian : public Admin{
public:
    void UpdateBook();
    void AllowBookBorrowing(); //access to borrow after making the availability
    void CheckBookAvailability(const std::string &title);
    void AddUser(const std::string &username, const std::string &password, const std::string &firstname, const std::string &lastname);
    void DisplayUsers();
    void DeleteUser(const std::string &username);
    void ListOfBorrowedBooks();
    void ListOfOverdueBooks();
private:
    std::vector<UserInfo> users; //list of the users
    void LoadUsers(); //load the users from txt to vector
    void SaveUsers(); //save from vector to txt

};