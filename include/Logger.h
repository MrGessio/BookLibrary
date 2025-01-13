#pragma once

#include <string>

class Logger{


public:
    void logIn();
    std::string getUsername();
    std::string getPassword();

    
private:
    std::string username, password;
};