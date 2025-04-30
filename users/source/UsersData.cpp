#include "UsersData.h"

 UsersData::UsersData(const std::string &firstName, const std::string &lastName, const std::string &userName, const std::string &userPassword)
        : firstName(firstName), lastName(lastName), userName(userName), userPassword(userPassword) {}
        
std::string UsersData::getFirstName() const {
    return firstName;
}

std::string UsersData::getLastName() const {
    return lastName;
}

std::string UsersData::getUserName() const {
    return userName;
}

std::string UsersData::getUserPassword() const {
    return userPassword;
}

