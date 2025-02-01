#pragma once

#include <string>

class Logger{


public:
    void logIn();
    std::string getUsername();
    std::string getPassword();
    bool IsValidUser(const std::string& userfile);

    
private:
    std::string username, password;
    std:: string loggedInUser;
};