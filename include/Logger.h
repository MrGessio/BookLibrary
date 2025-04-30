#pragma once

#include <string>

class Logger{


public:
    Logger() : username("default") {}
    Logger(const std::string &name) : username(name){}
    
    void LogIn(const std::string &u, const std::string &p);
    std::string getUsername();
    std::string getPassword();
    bool IsValidUser(const std::string& userfile);

    
private:
    std::string username, password;
    std:: string loggedInUser;
};
