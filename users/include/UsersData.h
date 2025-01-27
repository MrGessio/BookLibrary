#pragma once
#include <string>


class UsersData {
public:
    UsersData(const std::string &firstName, const std::string &lastName, const std::string &userName, const std::string &userPassword);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getUserName() const;
    std::string getUserPassword() const;

    std::string dataToSave();

private:
    std::string firstName;
    std::string lastName;
    std::string userName;
    std::string userPassword;

};